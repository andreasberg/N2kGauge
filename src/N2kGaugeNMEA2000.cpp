#include "N2kGaugeNMEA2000.h"
#include <N2kMsg.h>
#include <NMEA2000.h>
#include "cocoos.h"
#include "BoatData.h"

const bool debug_n2k = false;


tNMEA2000Handler NMEA2000Handlers[]={
  {129026L,&N2kCOGSOG,{0,0,0,0,0,false,false,false}},
  {129029L,&N2kGNSS,{0,0,0,0,0,false,false,false}},
  {127489L,&N2kEngineDynamic,{0,0,0,0,0,false,false,false}},
  {0,0,{0,0,0,0,0,false,false,false}}
};

const uint8_t N2K_HANDLERS_TOTAL = sizeof(NMEA2000Handlers)/sizeof(tNMEA2000Handler);
uint32_t N2kRXPGN = 0L;




//*****************************************************************************
void N2kEngineDynamic(const tN2kMsg &N2kMsg) {
    unsigned char EngineInstance;
    double EngineOilPress;
    double EngineOilTemp;
    double EngineCoolantTemp;
    double AltenatorVoltage;
    double FuelRate;
    double EngineHours;
    double EngineCoolantPress;
    double EngineFuelPress; 
    int8_t EngineLoad;
    int8_t EngineTorque;
    //char unit[5] = "l/nm";
    int idx = findN2kMsgStatIndex(N2kMsg.PGN);

    N2kRXPGN = 127489L;
    if (ParseN2kEngineDynamicParam(N2kMsg,EngineInstance,EngineOilPress,EngineOilTemp,EngineCoolantTemp,
                                   AltenatorVoltage,FuelRate,EngineHours,
                                   EngineCoolantPress,EngineFuelPress,
                                   EngineLoad,EngineTorque) ) {
      updateN2kMsgStat(idx,N2K_RX_SUCCESS);
      BoatData->EngineDynamic.FuelRate = (double)FuelRate;
      BoatData->EngineDynamic.EngineHours = (double)EngineHours;
      BoatData->Timestmp = BoatData->EngineDynamic.ts = millis();

      if (debug_n2k) {  
        Serial.print("FuelRate : ");Serial.print(BoatData->EngineDynamic.FuelRate);
        Serial.print(" EngineHours : ");Serial.print(BoatData->EngineDynamic.EngineHours);Serial.println("");
      }
      // dataPoints[1].value = (double)FuelRate;
      // dataPoints[1].localMillis = millis();
      
    } else {
      // unsuccessful parse
      // sprintf(logbuffer[lognextrow],"E_D|%2d|Parse error",N2kMsg.Source);
      // displayLog();
      // lognextidx();
      if (debug_n2k) {  
        Serial.println("COGSOG Parse Error");
      }
      updateN2kMsgStat(idx,N2K_RX_PARSE_ERROR);

    }
}


//*****************************************************************************
void N2kCOGSOG(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    tN2kHeadingReference HeadingReference;
    double COG;
    double SOG;
    int idx = findN2kMsgStatIndex(N2kMsg.PGN);

    N2kRXPGN = 129026L;
   
    if (ParseN2kCOGSOGRapid(N2kMsg,SID,HeadingReference,COG,SOG) ) {
      // successful parse
      updateN2kMsgStat(idx,N2K_RX_SUCCESS);
      BoatData->Course.SOG = (double)SOG;
      BoatData->Course.COG = (double)COG;
      BoatData->Timestmp = BoatData->Course.ts = millis();
      if (debug_n2k) {  
        Serial.print("SOG : ");Serial.print(BoatData->Course.SOG);Serial.print(" COG : ");Serial.print(BoatData->Course.COG);Serial.println("");
      }
//      sprintf(logbuffer[lognextrow],"CS|%2d|%.0f m/s",N2kMsg.Source,SOG);
      // dataPoints[0].value = (double)SOG;
      // dataPoints[0].localMillis = millis();
      //for (int i=0; dataPoints[i].PGN!=0 && !(N2kMsg.PGN==dataPoints[i].PGN); i++) {
      //  if (dataPoints[i].fieldNum == 4) {
      //    dataPoints[i].value = (double)SOG;
      //    dataPoints[i].localMillis = millis();
      //  }
      //}

    } else {
      // unsuccessful parse
      if (debug_n2k) {  
        Serial.println("COGSOG Parse Error");
      }
      updateN2kMsgStat(idx,N2K_RX_PARSE_ERROR);
    }
    // display empty ico
    // display.drawBitmap(20, 50,  ico_empty_bmp, 16, 15, 1);
    // display.display();
//    displayLog();
//    lognextidx();
}

void N2kGNSS(const tN2kMsg &N2kMsg) {
  unsigned char SID; 
  uint16_t DaysSince1970;
  double SecondsSinceMidnight, Latitude, Longitude, Altitude;
  tN2kGNSStype GNSStype;
  tN2kGNSSmethod GNSSmethod;
  unsigned char nSatellites;
  double HDOP,PDOP,GeoidalSeparation;
  unsigned char nReferenceStations;
  tN2kGNSStype ReferenceStationType;
  uint16_t ReferenceStationID;
  double AgeOfCorrection;

  int idx = findN2kMsgStatIndex(N2kMsg.PGN);

  Serial.println("Got GNSS");
  if(ParseN2kGNSS(N2kMsg, SID, DaysSince1970, SecondsSinceMidnight, 
                     Latitude, Longitude, Altitude, 
                     GNSStype, GNSSmethod,
                     nSatellites, HDOP, PDOP, GeoidalSeparation,
                     nReferenceStations, ReferenceStationType, ReferenceStationID,
                     AgeOfCorrection)) 
  {
    Serial.println("Parsed GNSS");
    Serial.print("Updating idx : ");Serial.println(idx);
    Serial.print("Updating [idx].PGN : ");Serial.println(NMEA2000Handlers[idx].PGN);
    Serial.print("Updating [idx].N2kMsgStat.cnt : ");Serial.println(NMEA2000Handlers[idx].N2kMsgStat.cnt);
    
    updateN2kMsgStat(idx,N2K_RX_SUCCESS);
    Serial.print("After [idx].PGN : ");Serial.println(NMEA2000Handlers[idx].PGN);
    Serial.print("After [idx].N2kMsgStat.cnt : ");Serial.println(NMEA2000Handlers[idx].N2kMsgStat.cnt);
    // char MsgOutBuf[MAX_NMEA0183_MSG_LEN];
    // NMEA0183CreateGGA((char *)&MsgOutBuf, SecondsSinceMidnight, 
    //                  Latitude, Longitude, Altitude, 
    //                  GNSSmethod,
    //                  nSatellites, HDOP, GeoidalSeparation,
    //                  ReferenceStationID, AgeOfCorrection);
                     
//    tNMEA0183Msg NMEA0183Msg;
//    NMEA0183Msg.Clear();
//    if (NMEA0183Msg.SetMessage((char *)&MsgOutBuf)) {
//      NMEA0183Msg.Send(Serial);
//      //blinkLed(led1,cGreen,BLINK_SHORT);
//    } else {
//    // parsing prob
//      blinkLed(led1,cRed,BLINK_LONG);
//    }

      //NMEA0183Serial.println(MsgOutBuf);
//      NMEA0183Serial.println(fixedGGA);
    
//    if (NMEA0183.SendMessage(MsgOutBuf)) {
//      blinkLed(led1,cGreen,BLINK_SHORT);
//    } else {
//      blinkLed(led1,cRed,BLINK_LONG);
//    }      
  } else {
    updateN2kMsgStat(idx,N2K_RX_PARSE_ERROR);
  }
}


// EventHandlers, 'dummy' function registered as task polling for flag change and signalling event 
void NMEAReceiveEvent() {
  task_open();
  for (;;) {
    if (N2kRXPGN > 0) {
      if (N2kRXPGN == 127489L) {
        event_signal(n2kReceiveEngineDynamicEvent);
      } else if(N2kRXPGN == 129026L) {
        event_signal(n2kReceiveCogSogEvent);
      }
      N2kRXPGN = 0L;
    }
    task_wait(10);
  }
  task_close();
}


// ******************************************************************************************************************************************************
// NMEA 2000 message handler
void HandleNMEA2000Msg(const tN2kMsg &N2kMsg) {
//void HandleNMEA2000Msg() {

  int iHandler;
  if (debug_n2k) {  
    Serial.print("Got new msg PGN :");Serial.println(N2kMsg.PGN);
  }
  // Find handler, loop whole list and find '0'=Unknown/unhandled msg if no match
  for (iHandler=0; NMEA2000Handlers[iHandler].PGN!=0 && !(N2kMsg.PGN==NMEA2000Handlers[iHandler].PGN); iHandler++);
  
  if (NMEA2000Handlers[iHandler].PGN!=0) {
    NMEA2000Handlers[iHandler].Handler(N2kMsg); 
  } else {
    // update stats for PGN=0
    NMEA2000Handlers[iHandler].N2kMsgStat.cnt++;
    NMEA2000Handlers[iHandler].N2kMsgStat.lastRx=millis();
    NMEA2000Handlers[iHandler].N2kMsgStat.flagRx=true;
  }
}

void N2kSetup() {
  // Setup NMEA2000 system

  // Set Product information
  NMEA2000.SetProductInformation(&N2kGaugeProductInformation );
  // Set Configuration information
  NMEA2000.SetProgmemConfigurationInformation(&N2kGaugeConfigurationInformation );
  // Set device information
  NMEA2000.SetDeviceInformation(31,      // Unique number. Use e.g. Serial number.
                                130,     // Device function=Display. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                120,     // Device class=Display . See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                1818    // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf                               
                               );
  // If you also want to see all traffic on the bus use N2km_ListenAndNode instead of N2km_NodeOnly below                               
  NMEA2000.SetForwardSystemMessages(true);
  NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode,22);
  NMEA2000.EnableForward(false);    // Disable all msg forwarding to USB (=Serial)
  NMEA2000.SetMsgHandler(HandleNMEA2000Msg);
  NMEA2000.SetN2kCANMsgBufSize(20);
  NMEA2000.Open();

}

int findN2kMsgStatIndex(uint32_t PGN) { 
  // Find our stats
  int i=0;
  for (; PGN!=0 && !(PGN==NMEA2000Handlers[i].PGN); i++);
  if (NMEA2000Handlers[i].PGN!=0) {
    return i;
  }
  return -1; // Not found
}

bool updateN2kMsgStat(int idx, int status) {
  if (idx >= 0 && idx < N2K_HANDLERS_TOTAL) {
    tN2kMsgStat *stat = &(NMEA2000Handlers[idx].N2kMsgStat);
    switch(status) {
      case N2K_RX_SUCCESS :
        stat->lastRx = millis(); 
        stat->flagRx = true;
        stat->cnt++; 
        return true;
      case N2K_RX_PARSE_ERROR :
        stat->lastRx = millis(); 
        stat->flagRx = true;
        stat->cnt++; 
        stat->errCnt++; 
        stat->flagErr=true; 
        return true;
      case N2K_RX_OTHER_ERROR :
        stat->cnt++; 
        stat->errCnt++; 
        stat->flagErr=true; 
        return true;
      case N2K_TX_SUCCESS :
        stat->flagTx = true;
        stat->lastTx = millis(); 
        stat->cnt++; 
        return true;
      case N2K_TX_OTHER_ERROR :
        stat->cnt++; 
        stat->errCnt++; 
        stat->flagErr=true; 
        return true;
    }
  }
  return false;
}

bool rxIsFlagged() {
  for(int i=0;i<N2K_HANDLERS_TOTAL;i++) 
    if (NMEA2000Handlers[i].N2kMsgStat.flagRx) return true;
  return false;
}

void resetRxFlags() {
  for(int i=0;i<N2K_HANDLERS_TOTAL;i++) {
    NMEA2000Handlers[i].N2kMsgStat.flagRx=false;
  }
}