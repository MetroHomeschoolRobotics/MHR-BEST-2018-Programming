#pragma config(Motor,  port2,           driftmtr,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           ClawServo,           tmotorServoContinuousRotation, openLoop)

task main{
startTask(controller);
startTask(drift);
startTask(mani)
}
task controller{
while(on){
	read left x
  read right x
  read right y
}
}
task drift {
	while(on) {
		driftmtr=leftx;
}
}
task mani{
	while(on){
		mani rotate= right x;
		mani elevate = right y;
}
}

task closeclaw{
	ClawServo = -127;
}

task openclaw {
	ClawServo = 127;
}

if (rightDownBtn.Pressed);}
 startTask[openclaw];}
{else}
	startTask[openclaw];




