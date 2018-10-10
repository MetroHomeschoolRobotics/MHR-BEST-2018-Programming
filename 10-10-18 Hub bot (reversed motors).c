
task main()
{



#pragma config(Motor,  port2,           driftmtr,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           maniphorizontal,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           manipvertical,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawServo,           tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           armExtension,        tmotorServoContinuousRotation, openLoop)


//*!!Code automatically generatd by the configuration wizard

// leftX stands for the X axis of the left joystick on the controller
int leftX = 0;

// leftY stands for the Y axis of the left joystick on the controller
int leftY = 0;

//rightX stands for the X axis of the right joystick on the controller
int rightX = 0;

//rightY stands for the Y axis of the right joystick on the controller
int rightY = 0;

/*thresh stands for the variable that the joystick
has to be greater has to be greater than in order to move the motor*/
int thresh = 6;

/* This is a boolean value, which means the variable is either true or false,
in this case we made one that is true*/
const bool on = true;


/* This task closes the claw*/
// clawServo is port 2
task closeClaw()
{
	motor[clawServo] = -127;
}

/* This task opens the claw*/
task openClaw()
{
	motor[clawServo] = 127;
}

/* This task checks input from the controller to set variables for the controller*/
task controller()
{


	/* Remember the "on" variable was set earlier as a boolean set to true, so it is always on,
	therefor always checking for input from the controller*/
	while(on)
	{

		/* This prevents motor jittering by using a threshhold,
		which we set as a variable of 6 on line 18 */
		leftX = vexRT(Ch4);
		if(abs(leftX)<thresh)
		{
			leftX = 0;

		}

		leftY = vexRT(Ch3);
		if(abs(leftY)<thresh)
		{
			leftY = 0;

		}
		rightX = vexRT(Ch1);
		if(abs(rightX)<thresh)
		{
			rightX = 0;

		}
		rightY = vexRT(Ch2);
		if(abs(rightY)<thresh)
		{
			rightY = 0;

		}

		//If there is input from the controller, start the closeClaw task
		if (vexRT[Btn6U]){
			startTask(closeClaw);
		}
		//If there isnt any input, start the task to open the claw
		else{
			startTask(openClaw);
		}
	}
}


// This task is what makes the robot go up and down the current
task drift()
{
	while(on) {
		motor[driftmtr] = -leftX;
	}
}



//This task controls the manipulator(s)
task manip()
{
	while(on){
		motor[maniphorizontal]=rightX;
		motor[manipvertical]=leftY;
		motor[armExtension]=rightY;
	}
}



//This task is the main task, this is what starts the robot
task main()
{
	startTask(controller);
	startTask(drift);
	startTask(manip);
	while(on){
	}
}
