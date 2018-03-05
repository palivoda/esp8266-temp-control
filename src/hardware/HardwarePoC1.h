#include <Arduino.h>
#include <Timer.h>
#include <DS18B20.h>

#ifndef HardwarePoC1_hpp
#define HardwarePoC1_hpp

#define PIN_VALVE_OPEN D7
#define PIN_VALVE_CLOSE D6
#define PIN_MOTOR D8
#define PIN_AMPS D5
#define PIN_TEMP_FEED D2
#define PIN_TEMP_RETURN D1

enum VALVE_STATE {
  VALVE_OPENING,
  VALVE_CLOSING,
  VALVE_STOPPED
};

class HardwarePoC1 {

  private:

    bool motorActive;
    VALVE_STATE valveAction = VALVE_STOPPED;
    long valvePosition = 0;
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
     long readValvePosition();

     void startMotor();
     void startMotor(long ms);
     static void stopMotor();
     bool readMotor();
     double readMotorAmps();

     double readFeedTemp();
     double readReturnTemp();
};

static HardwarePoC1 HW;

#endif
