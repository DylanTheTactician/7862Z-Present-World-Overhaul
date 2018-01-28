// ROBOTC/PROS COMPATIBILITY LIBRARY
#pragma systemfile

int iIMEGet(unsigned char imeName){
	return SensorValue[imeName];
}

bool digitalRead(unsigned char digital){
	return SensorValue[digital];
}

int iGyroGet(unsigned char gyro){
	return SensorValue[gyro];
}

int iUltrasonicGet(unsigned char ultrasonic){
	return SensorValue[ultrasonic];
}

void taskDelay(int ms){
	wait1Msec(ms);
}

void motorSet( unsigned char channel, int speed){
	motor[channel] = speed;
}

void motorStop( unsigned char channel){
	motor[channel] = 0;
}
