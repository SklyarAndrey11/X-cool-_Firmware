#ifndef _PID_
#define _PID_
#include <stdbool.h>



// Methods - double
double compute(double input);

// Methods - void
void begin();
void tune(double _Kp, double _Ki, double _Kd);
void limit(double min, double max);
void setpoint(double newSetpoint);
void minimize(double newMinimize);

// Methods - double, getters
double getOutput();



#endif /*_PID_*/
