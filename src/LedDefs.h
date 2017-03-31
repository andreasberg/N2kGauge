#ifndef _INCLUDE_LedDefs_
#define _INCLUDE_LedDefs_

#include "LedLib.h"
 
const tLed led[] = {
  { false, {13}, {LED_COLOR_DEFAULT} },
  { true, {17,14}, {LED_COLOR_RED,LED_COLOR_GREEN} },
  { true, {15,16}, {LED_COLOR_RED,LED_COLOR_GREEN} },
};

#endif // _INCLUDE_LedDefs_
