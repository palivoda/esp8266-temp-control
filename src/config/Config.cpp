#include "config.h"

#define READ_EEPROM(CVAR)\
CVAR = EEPROM.read(pos);\
pos += sizeof(CVAR);\
Serial.print("CVAR=");\
Serial.print(CVAR);

#define WRITE_EEPROM(CVAR)\
EEPROM.write(pos, CVAR);\
pos += sizeof(CVAR);\
Serial.print("CVAR=");\
Serial.print(CVAR);

int Config::reset() {
  #ifdef CONFIG_DEBUG
    Serial.print("EEPROM reset");
  #endif

  int i = 0;
  for (; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  return i;
}

int Config::read() {
  #ifdef CONFIG_DEBUG
    Serial.print("Reading EEPROM");
  #endif

  int pos = EEPROM_START_ADDRESS;

  //if version does not match then reset
  ConfigVersion = EEPROM.read(pos);
  if (ConfigVersion != CONFG_VERSION) return reset();
  pos += sizeof(ConfigVersion);

  READ_EEPROM(SetTemp);
  READ_EEPROM(MinReturnTemp);
  READ_EEPROM(ValveDuration);
  READ_EEPROM(TempHisteresis);

  return pos;
}

int  Config::write() {
  #ifdef CONFIG_DEBUG
    Serial.print("Writing to EEPROM");
  #endif

  int pos = EEPROM_START_ADDRESS;

  WRITE_EEPROM(SetTemp);
  WRITE_EEPROM(MinReturnTemp);
  WRITE_EEPROM(ValveDuration);
  WRITE_EEPROM(TempHisteresis);

  EEPROM.commit();

  return pos;
}
