#include "BasePidCtrl.h"
#include "..\hardware\HardwarePoC1.h"
#include "..\config\Config.h"

void BasePidCtrl::setup(ICtrlListener* l) {

  pidValve = PID(&feedTemp, &valveAction, &setTemp, 1, 4, 3, DIRECT);
  pidValve.SetSampleTime(1000);
  listener = l;

}

void BasePidCtrl::control() {

  setTemp = CONFIG.SetTemp;
  feedTemp = HW.readFeedTemp();
  returnTemp = HW.readReturnTemp();

  //temp events
  if (feedTempPrev - feedTemp > CONFIG.TempHisteresis || feedTempPrev - feedTemp < CONFIG.TempHisteresis) {
    feedTempPrev = feedTemp;
    listener->onFeedTempChange(feedTemp);
  }

  //PID valve regulation
  pidValve.SetOutputLimits(HW.readValvePosition() - CONFIG.ValveDuration, CONFIG.ValveDuration - HW.readValvePosition());
  pidValve.Compute();
  if (valveAction >= 1){
    HW.openValve(valveAction);
    listener->onValveChange(HW.readValvePosition());
  }
  else if (valveAction <= 1) {
    HW.closeValve(valveAction);
    listener->onValveChange(HW.readValvePosition());
  }

  //Motor operation
  if (HW.readFeedTemp() <= CONFIG.SetTemp) {
      HW.startMotor();
      listener->onMotorChange(true);
  }
  else {
    HW.stopMotor();
    listener->onMotorChange(false);
  }

}
