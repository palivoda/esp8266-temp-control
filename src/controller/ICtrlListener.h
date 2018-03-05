#ifndef ICtrlListener_h
#define ICtrlListener_h

class ICtrlListener
{
    public:
        virtual ~ICtrlListener() {}
        virtual void onFeedTempChange(double temp) = 0;
        virtual void onValveChange(int valvePosition) = 0;
        virtual void onMotorChange(bool motor) = 0;
};

#endif
