#ifndef Config_h
#define Config_h

#include <Arduino.h>
#include <EEPROM.h>

#define CONFG_VERSION 2
#define EEPROM_START_ADDRESS 1

class Config {
public:
      int ConfigVersion = CONFG_VERSION;
      double SetTemp = 23;
      double MinReturnTemp = 5;
      long ValveDuration = 12000;
      float TempHisteresis = 1;

      int reset();
      int read();
      int write();
};

static Config CONFIG;

#endif
