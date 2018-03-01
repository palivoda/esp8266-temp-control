
#include "HardwareControllerPoC1.h"

void HardwareControllerPoC1::init() {
  pinMode(PIN_MOTOR, OUTPUT);
  digitalWrite(PIN_MOTOR, LOW);
  pinMode(PIN_VALVE_OPEN, OUTPUT);
  digitalWrite(PIN_VALVE_OPEN, LOW);
  pinMode(PIN_VALVE_CLOSE, OUTPUT);
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  pinMode(PIN_TEMP_FEED, INPUT);
  pinMode(PIN_TEMP_RETURN, INPUT);
}

void HardwareControllerPoC1::loop() {
  valveTimer.update();
  motorTimer.update();
}

void HardwareControllerPoC1::openValve(short s) {
  valveTimer.pulseImmediate(PIN_VALVE_OPEN, s, HIGH); //TODO: callback to change valve to stopped state
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  valve = VALVE_OPENING;
}

void HardwareControllerPoC1::closeValve(short s) {
  digitalWrite(PIN_VALVE_OPEN, LOW);
  valveTimer.pulseImmediate(PIN_VALVE_CLOSE, s, HIGH);  //TODO: callback to change valve to stopped state
  valve = VALVE_CLOSING;
}

void HardwareControllerPoC1::stopValve() {
  digitalWrite(PIN_VALVE_OPEN, LOW);
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  valve = VALVE_STOPPED;
}

VALVE_STATE HardwareControllerPoC1::readValve() {
  return valve;
}

void HardwareControllerPoC1::turnMotor(bool on) {  //TODO: add period, optional, use timer
  motor = on;
  digitalWrite(PIN_MOTOR, on ? HIGH : LOW);
}

bool HardwareControllerPoC1::readMotor() {
    return motor;
}

float HardwareControllerPoC1::readMotorCurrent() {
    return 0.0;
}

float HardwareControllerPoC1::readFeedTemp()
{
  return feedTemp.getTemp();
}

float HardwareControllerPoC1::readReturnTemp()
{
  return returnTemp.getTemp();
}
