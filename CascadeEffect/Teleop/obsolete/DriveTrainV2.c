#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, openLoop)

/*Programmers: Connor       file: DriveTrainV1.c     Region: teleop    Year: cascade effect
creation date: 10-30-14                                    update: 10-30-14
summary: First version of our drivetrain software
*/


//global variables and includes:
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Includes\JoystickDriver.c"
const int deadZone = 10;
const float scale = .7874015748;


/*purpose: Our drive train. Pass in the x and y coordinates from main,
we determine our power P based off of the hypotenuse of the triangle
formed by x and y on the controller's grid, then depending on which
quadrant we're in we assign 2 motors to have a straight power passed
to them, and 2 of them have their power multiplied times the equation
(x^2-y^2)/(x^2 + y^2), which is the reduced form of cos(angle), where
angle is the angle formed by the triangle. The end result is that
two of the motors have their power varied by their degree, going from
power * -1, to 0, to power * 1. This reduction in magnitude of power
allows for true omnidirectional movement. Then we take our current
heading as given by a gyro, and use that to calculate what direction
the robot needs to move in, to allow us to have the robot move
according to our perspective instead of its. So, find power and quadrant
and then apply the formulas based on quadrant. Cardinal direction is case 5
of the switch case, as it requires different formulas.
input: x and y coordinate
output: robot moves
*/
void driveTrain(int x, int y, int rotate)
{
//	nxtDisplayTextLine(1, "x: %d", x);
//	nxtDisplayTextLine(2, "y: %d", y);
	rotate *=scale;
	y = -y;
	if(abs(x) < deadZone)  //Setting the deadzone
	{
		x = 0;
	}
	if (abs(y) < deadZone)
	{
		y = 0;
	}
	float power = sqrt((x*x) + (y*y)); //finding the power
	float angle;
	power *= scale;  //scaling it for the controller's 127 value axis. x *= c -> x = x *c

	int quad;  //here we define which quadrant the joystick is in based on x and y coordinate signs.
	//quadrant five is for cardinal directions. last case is the default for the controller being at zero.

	if (y<0 && x>0) //the controller values are skewed, so up on the y axis is negative, this is why y<0
	{
		quad = 1;
	}

	else if(y<0 && x<0)
	{
		quad = 2;
	}

	else if(y>0 && x<0)
	{
		quad = 3;
	}

	else if(y>0 && x>0)
	{
		quad = 4;
	}

	else if((x==0 && y!= 0) || (x!=0 && y==0))
	{
		quad = 5;
	}

	else
	{
		quad = 0; //joystick is at zero
	}

	//nxtDisplayTextLine(3, "quad: %d", quad);

	switch(quad)
	{
	case(1):
		angle = ((x*x - y*y)/(y*y + x*x));
		motor[frontLeft] = power + rotate;
		motor[frontRight] = -power * angle - rotate;
		motor[backRight] = -power * angle + rotate;
		motor[backLeft] = power - rotate;
		break;

	case(2):
		angle = ((x*x - y*y)/(y*y + x*x));
		motor[frontLeft] = -power * angle + rotate;
		motor[frontRight] = power - rotate;
		motor[backRight] = power + rotate;
		motor[backLeft] = -power * angle - rotate;
		break;

	case(3):
		angle = ((x*x - y*y)/(y*y + x*x));
		motor[frontLeft] = -power + rotate;
		motor[frontRight] = power * angle - rotate;
		motor[backRight] = power * angle + rotate;
		motor[backLeft] = -power - rotate;
		break;

	case(4):
		angle = ((x*x - y*y)/(y*y + x*x));
		motor[frontLeft] = power * angle + rotate;
		motor[frontRight] = -power - rotate;
		motor[backRight] = -power + rotate;
		motor[backLeft] = power * angle - rotate;
		break;

	case(5):
		if(x == 0 && y < 0) //straight up
		{
			motor[frontLeft] = power + rotate;
			motor[frontRight] = power - rotate;
			motor[backRight] = power + rotate;
			motor[backLeft] = power - rotate;
		}

		else if(x == 0 && y > 0) //straight down
		{
			motor[frontLeft] = -power + rotate;
			motor[frontRight] = -power - rotate;
			motor[backRight] = -power + rotate;
			motor[backLeft] = -power - rotate;
		}

		else if(y == 0 && x > 0) //straight right
		{
			motor[frontLeft] = power + rotate;
			motor[frontRight] = -power - rotate;
			motor[backRight] = -power + rotate;
			motor[backLeft] = power - rotate;
		}

		else if(y == 0 && x < 0) //straight left
		{
			motor[frontLeft] = -power + rotate;
			motor[frontRight] = power - rotate;
			motor[backRight] = power + rotate;
			motor[backLeft] = -power - rotate;
		}

		break;

	default:   //if joystick at 0
		motor[frontLeft] = 0 + rotate;
		motor[frontRight] = 0 - rotate;
		motor[backRight] = 0 + rotate;
		motor[backLeft] = 0 - rotate;
		break;

	}

}

task main()
{
	while(true)
	{
		eraseDisplay();
		getJoystickSettings(joystick);
		playSound(soundDownwardTones);
	//	if((abs(joystick.joy1_y1) > deadZone) || (abs(joystick.joy1_x1) > deadZone) || abs(joystick.joy1_x2) > deadZone)
	//	{
			if((abs(joystick.joy1_y1)))
			{
			//nxtDisplayTextLine(6, "inside");
			playSound(soundBeepBeep);
			driveTrain(joystick.joy1_x1, joystick.joy1_y1, joystick.joy1_x2);
		}
	}
}
