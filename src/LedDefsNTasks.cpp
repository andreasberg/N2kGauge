#include "LedDefsNTasks.h"
#include "LedLib.h"
#include "cocoos.h"

void Task_BlinkLED1() {

  task_open();

  for (;;) {
    event_wait(led1BlinkEvent);
    ledOn(led[1],LED_COLOR_GREEN);
    task_wait(100);
    ledOff(led[1]);
  }

  task_close();
}

void Task_BlinkLED2() {

  task_open();

  for (;;) {
    event_wait(led2BlinkEvent);
    ledOn(led[2],LED_COLOR_GREEN);
    task_wait(100);
    ledOff(led[2]);
  }

  task_close();
}