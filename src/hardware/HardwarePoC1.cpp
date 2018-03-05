#include "HardwarePoC1.h"
#include <acs712.h>
#include <ntcMf52at.h>

void HardwarePoC1::init() {
  pinMode(PIN_MOTOR, OUTPUT);
  digitalWrite(PIN_MOTOR, LOW);
  pinMode(PIN_VALVE_OPEN, OUTPUT);
  digitalWrite(PIN_VALVE_OPEN, LOW);
  pinMode(PIN_VALVE_CLOSE, OUTPUT);
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  pinMode(PIN_TEMP_FEED, INPUT);
  pinMode(PIN_TEMP_RETURN, INPUT);
}

void HardwarePoC1::loop() {
  valveTimer.update();
  motorTimer.update();
}

void HardwarePoC1::openValve(long ms) {
  if (valveTimer.after(ms, &stopValve) == -1) {
    Serial.print("OpenValve timer setup failed");
  }
  else {
    digitalWrite(PIN_VALVE_OPEN, HIGH);
    digitalWrite(PIN_VALVE_CLOSE, LOW);
    valveAction = VALVE_OPENING;
    valvePosition += ms;
  }
}

void HardwarePoC1::closeValve(long ms) {
  if (valveTimer.after(ms, &stopValve) == -1) {
    Serial.print("OpenValve timer setup failed");
  }
  else {
    digitalWrite(PIN_VALVE_OPEN, LOW);
    digitalWrite(PIN_VALVE_CLOSE, HIGH);
    valveAction = VALVE_CLOSING;
    valvePosition -= ms;
  }
}

void HardwarePoC1::stopValve() {
  digitalWrite(PIN_VALVE_OPEN, LOW);
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  HW.valveAction = VALVE_STOPPED;
}

VALVE_STATE HardwarePoC1::readValveAction() {
  return valveAction;
}

long HardwarePoC1::readValvePosition() {
  return valvePosition;
}

void HardwarePoC1::startMotor() {
  digitalWrite(PIN_MOTOR, HIGH);
  motorActive = true;
}

void HardwarePoC1::startMotor(long ms) {
  if (valveTimer.after(ms, &stopMotor) == -1) {
    Serial.print("Start Motor timer setup failed");
  }
  else {
    digitalWrite(PIN_MOTOR, HIGH);
    motorActive = true;
  }
}

void HardwarePoC1::stopMotor() {
  HW.motorActive = false;
  digitalWrite(PIN_MOTOR, LOW);
}

bool HardwarePoC1::readMotor() {
    return motorActive;
}

double HardwarePoC1::readMotorAmps() {
    return ACS712(PIN_AMPS);
}

double HardwarePoC1::readFeedTemp()
{
  return NTCMF52AT(PIN_TEMP_FEED);
}

double HardwarePoC1::readReturnTemp()
{
  return NTCMF52AT(PIN_TEMP_RETURN);
}
