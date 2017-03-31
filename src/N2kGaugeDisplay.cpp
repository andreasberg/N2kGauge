#include "N2kGaugeDisplay.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
//#include <font3x6.h>
#include "cocoos.h"
#include "stdarg.h"

const bool debug_display = false;

void setup_display() {
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, the buffer need to be cleared first.
  display.clearDisplay();
  // Show cleared display 
  display.display();
}

void display_splash() {
  display.clearDisplay();
  display.drawBitmap(0, 0,  splash_hajen_bmp, 128, 64, 1);
  display.display();
}

void clear_display() {
  display.clearDisplay();
  display.display();
}

void task_display_icon_speed() {
  task_open();
  for (;;) {
  	event_wait(n2kReceiveCogSogEvent);
  	// display s ico in predefined position on screen 
    display.drawBitmap(20, 50,  ico_s_bmp, 16, 15, 0);  // black(clear)
    display.display();
  	task_wait(10);
	display.drawBitmap(20, 50,  ico_s_bmp, 16, 15, 1);	// white(show)
  	display.display();
  	task_wait(20);
  	// draw empty icon top to hide
	display.drawBitmap(20, 50,  ico_s_bmp, 16, 15, 0); // black(clear)
  	display.display();
  }
  task_close();
}

void task_display_icon_engine() {
  task_open();
  for (;;) {
  	event_wait(n2kReceiveEngineDynamicEvent);
  	// display s ico in predefined position on screen 
    display.drawBitmap(2, 50,  ico_e_bmp, 16, 15, 0);  // black(clear)
    display.display();
  	task_wait(10);
	display.drawBitmap(2, 50,  ico_e_bmp, 16, 15, 1);	// white(show)
  	display.display();
  	task_wait(20);
  	// draw empty icon top to hide
	display.drawBitmap(2, 50,  ico_e_bmp, 16, 15, 0); // black(clear)
  	display.display();
  }
  task_close();
}

void display_log(tDisplayData *DisplayData) {
	// TODO: implement rolling log display
}

void display_enginehours(tDisplayData *DisplayData) {
  display.clearDisplay();
  if (DisplayData->value>=0) {  // only display if value >=0 
	  display.setTextColor(WHITE);
	  display.setFont(&FreeSans9pt7b);
	  display.setCursor(0,12);
	  display.print("Engine hours");

	  display.setCursor(114,64);
	  display.print(DisplayData->unit);

	  display.setFont(&FreeSans18pt7b);
	  if (DisplayData->value < 10) {
	    display.setCursor(61,44);
	  } else if (DisplayData->value < 100) {
	    display.setCursor(42,44);
	  } else {
	    display.setCursor(23,44);
	  }
	  if (DisplayData->value>=0) 
	    display.print(DisplayData->value);
}
  display.display();
}


void display_rate(tDisplayData *DisplayData) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(86,64);
  display.print(DisplayData->unit);
  display.setFont(&FreeSans24pt7b);
  if (DisplayData->value < 10) {
    display.setCursor(31,44);
  } else if (DisplayData->value < 100) {
    display.setCursor(5,44);
  } else {
    display.setCursor(5,44);
  }
  if (DisplayData->value>=0) 
    display.print(DisplayData->value);
  display.display();
}
