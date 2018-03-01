#include <Arduino.h>
#include "NtcMf52at10k.h"

#ifndef HardwareControllerPoC1_hpp
#define HardwareControllerPoC1_hpp

#define PIN_MOTOR D0
#define PIN_VALVE_OPEN D5
#define PIN_VALVE_CLOSE D6
#define PIN_TEMP_FEED 1
#define PIN_TEMP_RETURN 2

enum VALVE_STATE {
  VALVE_OPENING,
  VALVE_CLOSING,
  VALVE_STOPPED
};

class HardwareControllerPoC1 {

  private:

    bool motor;
    VALVE_STATE valve;
    NtcMf52at10k feedTemp = NtcMf52at10k(PIN_TEMP_FEED);
    NtcMf52at10k returnTemp = NtcMf52at10k(PIN_TEMP_RETURN);

   public:

     void init();
     void loop();

     short Valve ;
     void openValve(short s);
     void closeValve(short s);
     void stopValve();
     VALVE_STATE readValve();

     void turnMotor(bool on);
     bool readMotor();
     float readMotorCurrent();

     float readFeedTemp();
     float readReturnTemp();
};

#endif
