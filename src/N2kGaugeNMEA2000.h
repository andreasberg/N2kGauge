#ifndef _INCLUDE_N2kGaugeNMEA2000_
#define _INCLUDE_N2kGaugeNMEA2000_

#include "N2kGaugeNMEA2000.h"
#include <N2kMsg.h>
#include <NMEA2000_teensy.h>
#include <NMEA2000.h>
#include <N2kMessages.h>
#include "cocoos.h"
#include "BoatData.h"

extern tN2kMsg N2kMsg;
extern tNMEA2000_teensy NMEA2000;
extern tBoatData *BoatData;
extern Evt_t n2kReceiveEvent,n2kReceiveCogSogEvent,n2kReceiveEngineDynamicEvent;

#define N2K_RX_SUCCESS     10
#define N2K_RX_PARSE_ERROR 11
#define N2K_RX_OTHER_ERROR 12
#define N2K_TX_SUCCESS     20
#define N2K_TX_OTHER_ERROR 21

// ---  Example of using PROGMEM to hold Product ID.  However, doing this will prevent any updating of
//      these details outside of recompiling the program.
const tProductInformation N2kGaugeProductInformation PROGMEM={
                                       1300,                        // N2kVersion
                                       100,                         // Manufacturer's product code
                                       "N2K GAUGE",                 // Manufacturer's Model ID
                                       "1.0.0.0 (2017-03-13)",      // Manufacturer's Software version code
                                       "1.0.0.0 (2017-03-13)",      // Manufacturer's Model version
                                       "00000001",                  // Manufacturer's Model serial code
                                       0,                           // CertificationLevel
                                       1                            // LoadEquivalency
                                      };                                      

// ---  Example of using PROGMEM to hold Configuration information.  However, doing this will prevent any updating of
//      these details outside of recompiling the program.
const tNMEA2000::tProgmemConfigurationInformation N2kGaugeConfigurationInformation PROGMEM={
                                       "Manufacturer", // Manufacturer information
                                       "000", // Installation description1
                                       "000"  // Installation description2
                                      };


typedef struct  {
  uint16_t minTxDelay;
  uint32_t lastTx;
  uint32_t lastRx;
  uint32_t cnt;
  uint32_t errCnt;
  bool 	   flagRx;
  bool 	   flagTx;
  bool 	   flagErr;
} tN2kMsgStat;

typedef struct {
  unsigned long PGN;
  void (*Handler)(const tN2kMsg &N2kMsg); 
  tN2kMsgStat N2kMsgStat;
} tNMEA2000Handler;

void N2kSetup();
void HandleNMEA2000Msg(const tN2kMsg &N2kMsg);

void N2kCOGSOG(const tN2kMsg &N2kMsg);
void N2kGNSS(const tN2kMsg &N2kMsg);
void N2kEngineDynamic(const tN2kMsg &N2kMsg);

int findN2kMsgStatIndex(uint32_t PGN);
bool updateN2kMsgStat(int idx, int status);
bool rxIsFlagged();
void resetRxFlags();

void NMEAReceiveEvent();

#endif // _INCLUDE_N2kGaugeNMEA2000_