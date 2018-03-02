
#include "HardwareControllerPoC1.h"

static HardwareControllerPoC1 HW;

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

void HardwareControllerPoC1::openValve(long ms) {
  if (valveTimer.after(ms, &stopValve) == -1) {
    Serial.print("OpenValve timer setup failed");
  }
  else {
    digitalWrite(PIN_VALVE_OPEN, HIGH);
    digitalWrite(PIN_VALVE_CLOSE, LOW);
    valveAction = VALVE_OPENING;
    ValveState += ms;
  }
}

void HardwareControllerPoC1::closeValve(long ms) {
  if (valveTimer.after(ms, &stopValve) == -1) {
    Serial.print("OpenValve timer setup failed");
  }
  else {
    digitalWrite(PIN_VALVE_OPEN, LOW);
    digitalWrite(PIN_VALVE_CLOSE, HIGH);
    valveAction = VALVE_CLOSING;
    ValveState -= ms;
  }
}

void HardwareControllerPoC1::stopValve() {
  digitalWrite(PIN_VALVE_OPEN, LOW);
  digitalWrite(PIN_VALVE_CLOSE, LOW);
  HW.valveAction = VALVE_STOPPED;
}

VALVE_STATE HardwareControllerPoC1::readValveAction() {
  return valveAction;
}

void HardwareControllerPoC1::startMotor(long ms) {
  if (valveTimer.after(ms, &stopValve) == -1) {
    Serial.print("Start Motor timer setup failed");
  }
  else {
    digitalWrite(PIN_MOTOR, HIGH);
    motorActive = true;
  }
}

void HardwareControllerPoC1::stopMotor() {
  HW.motorActive = false;
  digitalWrite(PIN_MOTOR, LOW);
}

bool HardwareControllerPoC1::readMotor() {
    return motorActive;
}

float HardwareControllerPoC1::readMotorAmps() {
    return _ACS712(PIN_AMPS);
}

float HardwareControllerPoC1::readFeedTemp()
{
  return feedTemp.getTemp();
}

float HardwareControllerPoC1::readReturnTemp()
{
  return returnTemp.getTemp();
}

/*
  Returns  current consumption reading from ACS712 sensor.
  Motor max I (amps) = U (volts) / R (ohms), where U=12V and R is resistance of motor coil.
  Feeder - 10A max
  Fan 4mA - max
 */
float HardwareControllerPoC1::_ACS712(byte pin) {
  const byte mVperAmp = 66; // use 185 for 10A, 100 for 20A Module and 66 for 30A Module
  const short ACSoffset = 2485; //milivolts

  short rawVal = analogRead(pin);
  float mVolts = ((rawVal+1) / 1024.0) * 5000;
  float amps = ((mVolts - ACSoffset) / mVperAmp);

  //if (amps > 4) Serial.println(">>>>>>>>>>> HIGH!!!!");
  //Serial.println(String("ACS712 ") + pin + "=" + rawVal + " => " + mVolts + "mV, " + amps  + "A");
  return amps;
}
