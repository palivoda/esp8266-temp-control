#include "config.h"

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

  SetTemp = EEPROM.read(pos);
  pos += sizeof(SetTemp);
  #ifdef CONFIG_DEBUG
    Serial.print("SetTemp=");
    Serial.print(SetTemp);
  #endif

  MinReturnTemp = EEPROM.read(pos);
  pos += sizeof(MinReturnTemp);
  #ifdef CONFIG_DEBUG
    Serial.print("MinReturnTemp=");
    Serial.print(MinReturnTemp);
  #endif

  return pos;
}

int  Config::write() {
  #ifdef CONFIG_DEBUG
    Serial.print("Writing to EEPROM");
  #endif

  int pos = EEPROM_START_ADDRESS;

  EEPROM.write(pos, SetTemp);
  pos += sizeof(SetTemp);
  #ifdef CONFIG_DEBUG
    Serial.print("SetTemp=");
    Serial.print(SetTemp);
  #endif

  EEPROM.write(pos, MinReturnTemp);
  pos += sizeof(MinReturnTemp);
  #ifdef CONFIG_DEBUG
    Serial.print("MinReturnTemp=");
    Serial.print(MinReturnTemp);
  #endif

  EEPROM.commit();

  return pos;
}
