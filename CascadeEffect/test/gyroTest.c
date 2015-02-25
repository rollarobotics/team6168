#pragma config(Sensor, S1,     gyro,           sensorI2CHiTechnicGyro)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-gyro.h"

task main()
{
	  int heading = 0, y, x, interval;
		HTGYROstartCal(gyro);
		while(1)
		{
			y = nPgmTime;
			nxtDisplayTextLine(1, "y: %d", y);
			x = HTGYROreadRot(gyro);
		  nxtDisplayTextLine(3, "%d", x);
		  wait10Msec(100);
		  interval = nPgmTime - y;
		  nxtDisplayTextLine(4, "time: %d", nPgmTime);
		  nxtDisplayTextLine(5, "Time-y: %f", interval);
		  wait10Msec(100);
	  }
}
