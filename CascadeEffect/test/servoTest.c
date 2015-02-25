#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    tail,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    drawBridge,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    rampDrop,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    rampLease,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

task main()
{

	while(true)
	{
		servo[tail] = 100;
		servo[rampLease] = 100;
		servo[rampDrop] = 200;
		servo[drawBridge] = 255;
		wait10Msec(100);
		servo[tail] = 200;
		servo[rampLease] = 200;
		servo[rampDrop] = 100;
		servo[drawBridge] = 0;

	}
}
