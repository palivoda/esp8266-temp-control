#ifndef BasePidCtrl_h
#define BasePidCtrl_h

#include "PID_v1.h"
#include "ICtrlListener.h"
//#include "Timer.h"

class BasePidCtrl
{
  double feedTempPrev = 0;
  double feedTemp = 0;
  double setTemp = 0;
  double valveAction = 0;
  PID pidValve;
  //Timer timerMotor;
  ICtrlListener* listener;

  double returnTemp = 0;

public:

  void setup(ICtrlListener*);
  void control();
};

#endif
