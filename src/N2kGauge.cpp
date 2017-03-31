#include "Arduino.h"
#include <cocoos.h>
#include <Time.h>
#include "ADC.h"
#include <Average.h>

#include "LedDefsNTasks.h"

#include <N2kMsg.h>
#include <NMEA2000_teensy.h>

#include "BoatData.h"

#include "N2kGauge.h"
#include "N2kGaugeNMEA2000.h"
#include "N2kGaugeActionSensor.h"
#include "N2kGaugeDisplay.h"

const bool debug = false;

IntervalTimer theTimer;
// Sem_t mySemaphore;
Evt_t sensorActionEvent,n2kReceiveEvent,n2kReceiveCogSogEvent,n2kReceiveEngineDynamicEvent;
Evt_t led1BlinkEvent,led2BlinkEvent,buzzEvent,refreshDisplayEvent;
//Evt_t blinkEngineIconEvent,blinkSpeedIconEvent;

tBoatData *BoatData;

tDisplayData DisplayData[] = {
  {DISPLAY_DATA_FLOATUNIT,0,"",NULL,0},
  {DISPLAY_DATA_FLOATUNIT,0,"",NULL,0}
};

tDisplayHandler DisplayHandlers[]={
  {250,&display_rate},          // 
  {5000,&display_enginehours},  // update frequeqy every 30 sec.
  {0,0}
};

uint8_t current_display = 1;  // index of display currently shown
uint8_t display_count = 2;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Log row
char row[255];

// Photosensor triggering light action event
N2kGaugeActionSensor actionSensor;

// Buzzer
const int buzzpin = 5;

// N2K
tNMEA2000_teensy NMEA2000;
tN2kMsg N2kMsg;

// Function declarations for tasks
void Task_CheckForPhotoSensorAction();
void Task_DisplayManager();
void Task_ParseN2kMsgs();
void Task_Buzz();
void Task_Heartbeat();
void Task_RunOnceAtStartup();


void tasks_init() {

  led1BlinkEvent    = event_create();
  led2BlinkEvent    = event_create();
  buzzEvent         = event_create();
  sensorActionEvent = event_create();
  n2kReceiveEvent   = event_create();
  n2kReceiveCogSogEvent        = event_create();
  n2kReceiveEngineDynamicEvent = event_create();
  refreshDisplayEvent          = event_create();

  /* Create kernel objects */
  task_create( Task_BlinkLED1, 1, NULL, 0, 0 );
  task_create( Task_BlinkLED2, 2, NULL, 0, 0 );
  task_create( Task_Buzz, 3, NULL, 0, 0 );
  task_create( task_display_icon_speed, 5, NULL, 0, 0);
  task_create( task_display_icon_engine, 6, NULL, 0, 0);
  task_create( Task_DisplayManager, 7, NULL, 0, 0 );
  task_create( Task_CheckForPhotoSensorAction, 8, NULL, 0, 0 );
  task_create( Task_RunOnceAtStartup,10, NULL, 0, 0 );
  task_create( Task_ParseN2kMsgs, 20, NULL, 0, 0 );
  task_create( NMEAReceiveEvent, 15, NULL, 0, 0);
  //task_create( Task_Heartbeat, 50, NULL, 0, 0 );
  //mySem = sem_bin_create( 1 );
}

void system_init() {
  theTimer.begin(os_tick, 1000);    //  1000 provides 1 msec resolution
}

void setup_buzzer(){
  // Setup buzzer
  pinMode(buzzpin, OUTPUT); 
}

void app_init() {
  // various setups
  // setup LEDs
  uint8_t l;
  for (l=0;l<sizeof(led)/sizeof(tLed);l++)
    setupLed(led[l],false);

  // Setup display
  setup_display();
  display_splash();

  // Photosensor setup
  actionSensor.Setup();

  // Buzzersetup
  setup_buzzer();

  // Setup NMEA 2000
  N2kSetup();

  // Setup BoatData
  BoatData = new tBoatData();

  // Logging to serial
  Serial.begin(115200);
  
  delay(500);
}

void Task_ParseN2kMsgs() {
  task_open();
  for (;;) {
    NMEA2000.ParseMessages();
    
    task_wait(10); // needs some 'sleep' otherwise this task will block other tasks 
  }

  task_close();
}



void Task_DisplayManager() {
  task_open();
  for (;;) {
    //event_wait_multiple(0,n2kReceiveEvent,n2kReceiveEngineDynamicEvent,n2kReceiveCogSogEvent);
    //event_wait(n2kReceiveEngineDynamicEvent);

    //Serial.print("Got Dyna ts:");Serial.print(millis());Serial.print(" dyn_ts:");Serial.print(BoatData->EngineDynamic.ts);Serial.print(" sog_ts:");Serial.println(BoatData->Course.ts);
    switch (current_display) {
      case 0: // fuelrate
        if (millis()-BoatData->EngineDynamic.ts < 2000) {  // show max 2 seconds old data for fuelrate
          if(BoatData->Course.SOG > 0 && max(BoatData->Course.ts,BoatData->EngineDynamic.ts)-min(BoatData->Course.ts,BoatData->EngineDynamic.ts) < 1000) { 
            // show fuelrate/distance only if diff in timestamps less than 1sec
            if (debug) {
              Serial.print("l/nm :");Serial.println(BoatData->EngineDynamic.FuelRate/(BoatData->Course.SOG*1.94384449));
            }
            DisplayData[0].value = (float)BoatData->EngineDynamic.FuelRate/(BoatData->Course.SOG*1.94384449);
            strcpy(DisplayData[0].unit,"l/nm");
          } else {
            DisplayData[0].value = (float)BoatData->EngineDynamic.FuelRate;
            strcpy(DisplayData[0].unit,"l/h");
          }
        } else { 
          DisplayData[0].value = -1.0;  // negative value doesn't show
          strcpy(DisplayData[0].unit,"");
        }
        break;
      case 1: // engine hours
          if (BoatData->EngineDynamic.ts > 0 && millis()-BoatData->EngineDynamic.ts < 30000) {
            DisplayData[1].value = (float) BoatData->EngineDynamic.EngineHours;
            strcpy(DisplayData[1].unit,"h");
          } else {
            DisplayData[1].value = -1.0; // negative value doesn't show
            strcpy(DisplayData[1].unit,"");
          }
        break;
    }

    DisplayHandlers[current_display].Handler(&DisplayData[current_display]);
    event_wait_timeout(refreshDisplayEvent, DisplayHandlers[current_display].RefreshDelay);   // wait for either refreshDisplayEvent or timeout after RefreshDelay
//    task_wait(500);

    //event_signal(buzzEvent);
    
    // if (rxIsFlagged()) 
    // {
    //   event_signal(n2kReceiveEvent);
    //   event_signal(buzzEvent);
    //   resetRxFlags();
    // }
    //event_wait_timeout(n2kReceiveEvent,10);


  }

  task_close();
}


void Task_CheckForPhotoSensorAction() {
  task_open();
  for (;;) {
  	// Serial.println("Reading actionsensor");
    if (actionSensor.Read()) 
    {
       //event_signal(sensorActionEvent);
      (current_display + 1 < display_count) ? current_display += 1 : current_display = 0;
      event_signal(refreshDisplayEvent);
    }
    task_wait(LOOP_SLEEP_TICKS);
  }

  task_close();
}

void Task_Buzz() {

  task_open();

  for (;;) {
    event_wait_multiple(0,buzzEvent,refreshDisplayEvent);  // 0 = listen for any of the events 
    tone(buzzpin,1000);
    task_wait(50);
    tone(buzzpin,1500);
    task_wait(50);
    tone(buzzpin,2000);
    task_wait(100);
    noTone(buzzpin);
  }

  task_close();
}

void Task_Heartbeat() {
  task_open();

  for (;;) {
    //Serial.println("Got action event");
    event_signal(led1BlinkEvent);
    event_signal(led2BlinkEvent);
    event_signal(sensorActionEvent);
    event_signal(n2kReceiveEvent);
    task_wait(10000);
  }

  task_close();

}

void Task_RunOnceAtStartup() {
  task_open();
  event_signal(led1BlinkEvent);
  event_signal(led2BlinkEvent);
  event_signal(buzzEvent);
  // event_signal(sensorActionEvent);
  // event_signal(n2kReceiveEvent);
  task_wait(2000);
  clear_display();
  task_close();

}
 
int main(void)
{
  /* Setup ports, clock... */
  system_init();
  
  /* Initialize cocoOS */
  os_init();

  /* Other initializations */
  app_init();

  /* init multitasking */
  tasks_init();
  
  /* start multitasking */
  os_start();
  
  /* Will never end up here */
  return 0;
}