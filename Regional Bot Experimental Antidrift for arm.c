#pragma config(Motor,  port8,           driftmtr,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           maniphorizontal,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           manipvertical,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           clawServo,           tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           armExtension,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           startServo,          tmotorServoStandard, openLoop)
#pragma config(Sensor, dgtl12,          LimitSwitch,         sensorTouch)
#pragma config(Motor,  port7,           scoopGateservo)


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

int counterweightThresh = 14;

/* This is a boolean value, which means the variable is either true or false,
in this case we made one that is true*/
const bool on = true;

/*Tells us if the arm is frozen or not*/
//bool isFrozen = false;

/*temp horiz antidrift int*/
//int temphoriz;

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

task startServodown()
{
	motor[startServo] = -127;
}

task startServoup()
{
	motor[startServo] = 127;
}

task scoopGateservoclosed()
{
	motor[scoopGateservo] = 127;
}

task scoopGateservoopen()
{
	motor[scoopGateservo] = -127;
}

/*task armAntidrifton()
{
  motor[maniphorizontal] = -16 ];
}*/

/*task armAntidriftoff()
{
	motor[maniphorizontal] = 0;
}*/

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

		// Apply Anti-Drift
		if (leftX==0){
			if( SensorValue[ LimitSwitch ] == 1 ) {
				leftX = -16;
			}
			else {
				leftX = 16;
			}
		}


		leftY = vexRT(Ch3);
		if(abs(leftY)<counterweightThresh)
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

		if (vexRT[Btn8U]){
			startTask(startServodown);
		}

		else{
			startTask(startServoup);


		if(vexRT[Btn8U]){
		  startTask(scoopGateservoopen);
		}

		else{
			startTask(scoopGateservoclosed);

			/*if(vexRT[Btn5U]){

				if (isFrozen == false) {
				isFrozen = true;
				} else {
				isFrozen = false;
				}
				temphoriz = vexRT(Ch1)
				while(isFrozen){
				//Set Motor to temphoriz
				}
        startTask(armAntidrifton);
   }
    else{
    	startTask(armAntidriftoff);
  */
      }
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
		motor[maniphorizontal]= rightX;
		motor[manipvertical] = leftY * .75;
		motor[armExtension]= rightY;
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
