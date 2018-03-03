#ifndef Config_h
#define Config_h

#include <EEPROM.h>

#define CONFG_VERSION 1
#define EEPROM_START_ADDRESS 0

class Config {
public:
      int ConfigVersion = CONFG_VERSION;
      int SetTemp = 23;
      int MinReturnTemp = 5;

      int reset();
      int read();
      int write();
};

#endif
