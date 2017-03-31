#ifndef _INCLUDE_N2kGaugeActionSensor_H_
#define _INCLUDE_N2kGaugeActionSensor_H_

#include "ADC.h"
#include "Average.h"

// ActionSensor / Photosensor setup 
#define SAMPLE_RATE    20    // record sample for average every SAMPLE_RATE:th loop
// Action detection settings
#define THRESHOLD      10	 // delta to be consider action
#define TICKLIMIT      8     // amount of actionticks to record anomality before signaling event (LOOP_SLEEP_TICKS*TICKLIMIT milliseconds, e.g. 250*12= 3secs)
#define LOOP_SLEEP_TICKS     250    // e.g. sampling freq 4Hz -> delay 250ms, frequency of ADC loop
// Moving average of ADC readings
#define AVG_BUCKETS    10
#define AVG_RESET      120   // Reset avg every AVG_RESET*LOOP_SLEEP_TICKS milliseconds, e.g. 250 * 120 = 30 secs
#define DAYLIGHT_LIMIT 5
#define THRESHOLD_DAYLIGHT 2 

class N2kGaugeActionSensor {
public:
  ADC *adc;
  int photoSensorPin;
  float curravg;
  float currvalue; 
  int actionticks;
  uint8_t samplecounter;
  Average<float> *ave;
  Average<float> *actionave;
  int ticks_since_last_action;

public:
  N2kGaugeActionSensor();
  void Setup();
  bool Read();

};

#endif // _INCLUDE_N2kGaugeActionSensor_H_