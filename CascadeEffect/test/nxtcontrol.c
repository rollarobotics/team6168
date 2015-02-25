#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     spinner,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    tubeClamp,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    tubeDrop,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    rampDrop,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)


task main()
{
	int count = 0;
	while (true)
	{
		if(nNxtButtonPressed == 3)
			count++;
	  while(nNxtButtonPressed != -1);
		if(count >= 3)
			count = 0;
		switch(count)
		{
		case 0:
			nxtDisplayTextLine(6, "down lift up");
			if(nNxtButtonPressed == 2)
			{
				motor[lift] = -50;
			}
			else if(nNxtButtonPressed == 1)
			{
				motor[lift] = 50;
			}
			else
			{
				motor[lift] = 0;
			}
			break;

		case 1:
			nxtDisplayTextLine(6, "down tubeDrop up");
			if(nNxtButtonPressed == 2)
			{
				servo[tubeDrop] = 0;
			}
			else if(nNxtButtonPressed == 1)
			{
				servo[tubeDrop] = 255;
			}
			else
			{
				servo[tubeDrop] = 127;
			}
			break;



		case 2:
			nxtDisplayTextLine(6, "down tubeClamp up");
			if(nNxtButtonPressed == 2)
			{
				servo[tubeClamp] = 0;
			}
			else if(nNxtButtonPressed == 1)
			{
				servo[tubeClamp] = 255;
			}
			else
			{
				servo[tubeClamp] = 127;
			}
			break;
		}


	}

}
