#include "N2kGaugeActionSensor.h"

#include "ADC.h"
#include "Average.h"


const bool debug_actionsensor = true;

//*****************************************************************************
N2kGaugeActionSensor::N2kGaugeActionSensor() {

  photoSensorPin = A14;  //ADC_0
  adc = new ADC();
  curravg = 0;
  currvalue = 0; 
  actionticks = 0;
  samplecounter = 0;
  ticks_since_last_action = 0;

  ave = new Average<float>(AVG_BUCKETS);
  actionave = new Average<float>(AVG_BUCKETS); 
}

void N2kGaugeActionSensor::Setup() {
  pinMode(photoSensorPin, INPUT);

  ///// ADC0 ////
  // reference can be ADC_REFERENCE::REF_3V3, ADC_REFERENCE::REF_1V2 (not for Teensy LC) or ADC_REFERENCE::REF_EXT.
  adc->setReference(ADC_REFERENCE::REF_1V2, ADC_0); // change all 3.3 to 1.2 if you change the reference to 1V2

  adc->setAveraging(16); // set number of averages
  adc->setResolution(16); // set bits of resolution

  // it can be any of the ADC_CONVERSION_SPEED enum: VERY_LOW_SPEED, LOW_SPEED, MED_SPEED, HIGH_SPEED_16BITS, HIGH_SPEED or VERY_HIGH_SPEED
  // see the documentation for more information
  // additionally the conversion speed can also be ADACK_2_4, ADACK_4_0, ADACK_5_2 and ADACK_6_2,
  // where the numbers are the frequency of the ADC clock in MHz and are independent on the bus speed.
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED); // change the conversion speed
  // it can be any of the ADC_MED_SPEED enum: VERY_LOW_SPEED, LOW_SPEED, MED_SPEED, HIGH_SPEED or VERY_HIGH_SPEED
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed

  // always call the compare functions after changing the resolution!
  //adc->enableCompare(1.0/3.3*adc->getMaxValue(ADC_0), 0, ADC_0); // measurement will be ready if value < 1.0V
  //adc->enableCompareRange(1.0*adc->getMaxValue(ADC_0)/3.3, 2.0*adc->getMaxValue(ADC_0)/3.3, 0, 1, ADC_0); // ready if value lies out of [1.0,2.0] V

  // If you enable interrupts, notice that the isr will read the result, so that isComplete() will return false (most of the time)
  //adc->enableInterrupts(ADC_0);
}

bool N2kGaugeActionSensor::Read() {
    bool res = false;
    int value = adc->adc0->analogRead(photoSensorPin); // read a new value, will return ADC_ERROR_VALUE if the comparison is false.
    currvalue = value*1000*3.3/adc->getMaxValue(ADC_0);

    // TODO: Implemented low-light sensor logic

    if (curravg == 0) {
      ave->push(currvalue);
      curravg = ave->mean();
    }
    ticks_since_last_action++;

    if (curravg > DAYLIGHT_LIMIT && currvalue < THRESHOLD_DAYLIGHT && ticks_since_last_action > 2*TICKLIMIT) {
      actionticks = TICKLIMIT;
    }
    if (actionticks > 0) {
      actionave->push(currvalue);
      if (actionave->getCount() == AVG_BUCKETS && actionave->mean() < THRESHOLD_DAYLIGHT) {
        if (debug_actionsensor) {
          Serial.println("ACTION!!");
        }
        res = true;
        ticks_since_last_action = 0;
        actionave->clear();
        actionticks=0; 
      } else {
        actionticks --;
      }

    } else {
      actionticks = 0;
      actionave->clear();
      if (samplecounter == 0) {
        ave->push(currvalue);
        curravg = ave->mean();
      }
      samplecounter = (samplecounter + 1 < SAMPLE_RATE) ? samplecounter+1 : 0;
    }

    if (debug_actionsensor) {
      Serial.print("Value: ");Serial.print(currvalue,DEC);Serial.print(", avg: ");Serial.print(curravg,DEC);
      // Serial.print(", delta: ");Serial.print(currdelta,DEC);
      Serial.print(", actioncount: ");Serial.print(actionave->getCount(),DEC);
      Serial.print(", actionmean: ");Serial.print(actionave->mean(),DEC);
      // Serial.print(", delta: ");Serial.print(currdelta,DEC);

      Serial.print(", ticks_since_last_action: ");Serial.print(ticks_since_last_action,DEC);
      Serial.print(", actionticks: ");Serial.println(actionticks,DEC);
    }

    /* fail_flag contains all possible errors,
        They are defined in  ADC_Module.h as

        ADC_ERROR_OTHER
        ADC_ERROR_CALIB
        ADC_ERROR_WRONG_PIN
        ADC_ERROR_ANALOG_READ
        ADC_ERROR_COMPARISON
        ADC_ERROR_ANALOG_DIFF_READ
        ADC_ERROR_CONT
        ADC_ERROR_CONT_DIFF
        ADC_ERROR_WRONG_ADC
        ADC_ERROR_SYNCH

        You can compare the value of the flag with those masks to know what's the error.
    */

    if(adc->adc0->fail_flag) {
        Serial.print("ADC0 error flags: 0x");
        Serial.println(adc->adc0->fail_flag, HEX);
    }

    //delay(1000/LOOP_FREQ);
    return res;
}

