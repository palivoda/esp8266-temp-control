#include <Arduino.h>
#include <Timer.h>
#include "NtcMf52at10k.h"

#ifndef HardwareControllerPoC1_hpp
#define HardwareControllerPoC1_hpp

#define PIN_MOTOR D0
#define PIN_VALVE_OPEN D5
#define PIN_VALVE_CLOSE D6
#define PIN_AMPS D7
#define PIN_TEMP_FEED 1
#define PIN_TEMP_RETURN 2

enum VALVE_STATE {
  VALVE_OPENING,
  VALVE_CLOSING,
  VALVE_STOPPED
};

class HardwareControllerPoC1 {

  private:

    bool motorActive;
    VALVE_STATE valveAction = VALVE_STOPPED;
    long ValveState = 0;
    NtcMf52at10k feedTemp = NtcMf52at10k(PIN_TEMP_FEED);
    NtcMf52at10k returnTemp = NtcMf52at10k(PIN_TEMP_RETURN);
    Timer valveTimer;
    Timer motorTimer;
    float _ACS712(byte pin);

   public:

     void init();
     void loop();

     long ValveConfig = 120000;
     void openValve(long ms);
     void closeValve(long ms);
     static void stopValve();
     VALVE_STATE readValveAction();

     void startMotor(long ms);
     static void stopMotor();
     bool readMotor();
     float readMotorAmps();

     float readFeedTemp();
     float readReturnTemp();
};

#endif
