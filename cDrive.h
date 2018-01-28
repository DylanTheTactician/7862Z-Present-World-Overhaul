
float	//
logDrive (int iInput, float iMultiply) {
	return (pow(abs(iInput), iMultiply)) * sgn(iInput);
}

void	// Standard Tank Drive code with truespeed.
tank( int iSpeedL, int iSpeedR ) {
	chassisLMotor = sgn(iSpeedL) * MC29[abs(clipNum(iSpeedL, 127))];
	chassisRMotor = sgn(iSpeedR) * MC29[abs(clipNum(iSpeedR, 127))];
}

int // Returns integer of Left Chassis encoder
iGetLeftChassis() {
	return SensorValue[iLeftEncoder];
}

int	// Returns integer of Right Chassis encoder
iGetRightChassis() {
	return -SensorValue[iRightEncoder];
}
