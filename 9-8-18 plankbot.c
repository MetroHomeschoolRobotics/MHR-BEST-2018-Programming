#pragma config(Motor,  port1,           driftmtr,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           clawServo,           tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           maniphorizontal,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           manipvertical,        tmotorServoContinuousRotation, openLoop)

int leftX = 0;

int rightX = 0;

int rightY = 0;

int thresh = 6;

const bool on = true;


task closeClaw()
{
	motor[clawServo] = -127;
}


task openClaw()
{
	motor[clawServo] = 127;
}


task controller()
{


	while(on)
	{

		leftX = vexRT(Ch1);
		if(abs(leftX)<thresh)
		{
			leftX = 0;

		}
		rightX = vexRT(Ch1);
		if(abs(rightX)<thresh)
		{
			rightX = 0;

		}
		rightY = vexRT(Ch1);
		if(abs(rightY)<thresh)
		{
			rightY = 0;

		}

		if (vexRT[Btn8D]){
			startTask(closeClaw);
		}
		else{
			startTask(openClaw);
		}
	}
}



task drift()
{
	while(on) {
		motor[driftmtr] = leftX;
	}
}




task manip()
{
	while(on){
		motor[maniphorizontal]=rightX;
		motor[manipvertical]=rightY;
	}
}




task main()
{
	startTask(controller);
	startTask(drift);
	startTask(manip);
}
