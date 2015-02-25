#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     seeker,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rightFront,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftFront,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     rightBack,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     leftBack,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    rampDrop,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    rampLease,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    tail,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    drawBridge,           tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*programmer: Druetord	date started: 12-28-15  update: 12-28-14
Just a program for the rubber wheels; when the joysticks are pushed
beyond our deadzone 'of 10, the values of the joysticks are scaled
for the 128/127 joystick range into the 100 motor range and motors are
set to the resulting power*/

const int deadZone = 10;
const float scale = .7874015748; //  100/127

#include "joystickDriver.c"
#define butta joy2Btn(2)
#define buttb joy2Btn(3)
#define buttx joy2Btn(1)
#define butty joy2Btn(4)
#define start joy2Btn(10)

const int targ1 = 1120, targ2 = 1120 * 2, targ3 = 1120 * 3, targ4 = 1120 * 4, targ5 = 1120 * 5;
const int tailInitial = 20;
const int rampInitial = 127;
const int leaseInitial = 127;

void driveTrain(float y1, float y2)
{
	y1 *= scale;
	y2 *= scale;

	motor[leftFront] = y1;
	motor[leftBack] = y1;
	motor[rightFront] = y2;
	motor[rightBack] = y2;

}

void liftMove(float y1)
{
	y1 *= scale;

	motor[lift] = y1;

	int pos = 0;

	if (butta)
		pos =1;
	else if (buttb)
		pos=2;
	else if (buttx)
		pos=3;
	else if (butty)
		pos=4;
	else if (start)
		pos=5;

	switch (pos)
	{
	case 1:
		if(nMotorEncoder[lift] < targ1)
			motor[lift] = 100;
		else
		{
			motor[lift] = 0;
			pos = 0;
		}
		break;

	case 2:
		if(nMotorEncoder[lift] < targ2)
			motor[lift] = 100;
		else
		{
			motor[lift] = 0;
			pos = 0;
		}
		break;

	case 3:
		if(nMotorEncoder[lift] < targ3)
			motor[lift] = 100;
		else
		{
			motor[lift] = 0;
			pos = 0;
		}
		break;

	case 4:
		if(nMotorEncoder[lift] < targ4)
			motor[lift] = 100;
		else
		{
			motor[lift] = 0;
			pos = 0;
		}
		break;

	case 5:
		if(nMotorEncoder[lift] < targ5)
			motor[lift] = 100;
		else
		{
			motor[lift] = 0;
			pos = 0;
		}
		break;

	}
}

void conveyorbelt(bool butt1, bool butt2)  //function to operate the conveyor belt
{
	if(butt1 == true)
	{
		motor[conveyor] = 100;
	}

	if(butt2 == true)
	{
		motor[conveyor] = -100;
	}
}


void tailservo (bool butt1, bool butt2)
{
	static int servoCount = tailInitial;
	if(butt1)
	{
		servoCount--;
		wait10Msec(1);
		servo[tail] = servoCount;
	}
	if(butt2)
	{
		servoCount++;
		wait10Msec(1);
		servo[tail] = servoCount;
	}
}

void rampservo (bool butt1, bool butt2)
{
	static int servoCount = rampInitial;
	if(butt1)
	{
		servoCount++;
		wait10Msec(3);
		servo[rampDrop] = servoCount;
	}
	if(butt2)
	{
		servoCount--;
		wait10Msec(3);
		servo[rampDrop] = servoCount;
	}
}

void ramprelease(bool butt1, bool butt2)
{

	if(butt1)
	{
		servo[rampLease] = 255;
	}

	if(butt2)
	{
		servo[rampLease] = 127;
	}

}

void bridge (bool butt1, bool butt2)
{
	if(butt1)
	{
		servo[drawBridge] = 255;
	}
  if(butt2)
	{
		servo[drawBridge] = 0;
	}
}

task main()
{
  int x = nMotorEncoder[leftFront];
  servo[tail] = tailInitial;
	servo[rampDrop] = rampInitial;
	servo[rampLease] = leaseInitial;
	nMotorEncoder[lift] = 0;
	nMotorEncoder[leftFront] = 0;
  nMotorEncoder[rightFront] = 0;
  clearDebugStream();
	while(true)
	{
		x = nMotorEncoder[leftFront];
		writeDebugStreamLine("x: %d", x);
		getJoystickSettings(joystick);
		if((abs(joystick.joy1_y1) > deadZone) || (abs(joystick.joy1_y2) > deadZone))
		{
			nxtDisplayTextLine(6, "inside");
			driveTrain(joystick.joy1_y1, joystick.joy1_y2);
		}

		else
		{
			motor[leftFront] = 0;
			motor[leftBack] = 0;
			motor[rightFront] = 0;
			motor[rightBack] = 0;
		}

		if(joy1Btn(5) == true || joy1Btn(7) == true)   //if button one or two is pressed, run the motor accordingly
		{
			conveyorbelt(joy1Btn(5), joy1Btn(7));
		}
		else
			motor[conveyor] = 0;

		if(joy1Btn(6) == true || joy1Btn(8) == true)   //if button one or two is pressed, run the motor accordingly
		{
			tailservo(joy1Btn(6), joy1Btn(8));
		}

		liftMove(joystick.joy2_y1);

		if(joy2Btn(5) == true || joy2Btn(7) == true)   //if button one or two is pressed, run the motor accordingly
		{
			bridge(joy2Btn(5), joy2Btn(7));
		}
		else
			servo[drawBridge] = 127;

		if(joy2Btn(6) == true || joy2Btn(8) == true)   //if button one or two is pressed, run the motor accordingly
		{
			rampservo(joy2Btn(6), joy2Btn(8));
		}

		if(joy1Btn(1) == true || joy1Btn(2) == true)
		{
      ramprelease(joy1Btn(1), joy1Btn(2));
	  }

	}

}