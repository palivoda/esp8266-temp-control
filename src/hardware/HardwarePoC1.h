#include <Arduino.h>
#include <Timer.h>

#ifndef HardwarePoC1_hpp
#define HardwarePoC1_hpp

#define PIN_VALVE_OPEN D1
#define PIN_VALVE_CLOSE D2
#define PIN_MOTOR D3
#define PIN_AMPS D4
#define PIN_TEMP_FEED D8
#define PIN_TEMP_RETURN D7

enum VALVE_STATE {
  VALVE_OPENING,
  VALVE_CLOSING,
  VALVE_STOPPED
};

class HardwarePoC1 {

  private:

    bool motorActive;
    VALVE_STATE valveAction = VALVE_STOPPED;
    int valvePosition = 0;
    Timer valveTimer;
    Timer motorTimer;

   public:

     void init();
     void loop();

     long ValveConfig = 120000;
     void openValve(long ms);
     void closeValve(long ms);
     static void stopValve();
     VALVE_STATE readValveAction();
     int readValvePosition();

     void startMotor(long ms);
     static void stopMotor();
     bool readMotor();
     float readMotorAmps();

     float readFeedTemp();
     float readReturnTemp();
};

#endif
