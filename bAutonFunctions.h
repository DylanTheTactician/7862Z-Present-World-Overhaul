#pragma systemfile

/* 		DRIVE CODE START		 */
/* 		DRIVE CODE START		 */
/* 		DRIVE CODE START		 */

void	// Directly sets drivetrain using two constants. Used in ReRun code.
tankWithoutTrueSpeed( int iSpeedL, int iSpeedR ) {
	chassisLMotor = iSpeedL;
	chassisRMotor = iSpeedR;
}

// Left Chassis PID
pid sLeftChassisPID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iLeftChassisPID( int iDes ) {
	const float kP = fLeftChassiskP;
 	const float kD = fLeftChassiskD;
	sLeftChassisPID.current    = SensorValue[iLeftEncoder];
	sLeftChassisPID.error      = iDes - sLeftChassisPID.current;
  sLeftChassisPID.derivative = sLeftChassisPID.error - sLeftChassisPID.lastError; // Calculate Derivative
	taskDelay(5);
	sLeftChassisPID.lastError = sLeftChassisPID.error;
	return ( (sLeftChassisPID.error * kP) + (sLeftChassisPID.derivative * kD) );
}

bool // Check if left chassis is at the desired position
bLeftChassisIsAtPos( int iDes ) {
  return abs(iDes - iGetLeftChassis()) < 50 ? true : false; // Return true if so, false if not
}

// Right Chassis PID
pid sRightChassisPID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iRightChassisPID( int iDes ) {
	const float kP = fRightChassiskP;
 	const float kD = fRightChassiskD;
	sRightChassisPID.current    = SensorValue[iRightEncoder];
	sRightChassisPID.error      = iDes - sRightChassisPID.current;
  sRightChassisPID.derivative = sRightChassisPID.error - sRightChassisPID.lastError; // Calculate Derivative
	taskDelay(5);
	sRightChassisPID.lastError = sRightChassisPID.error;
	return ( (sRightChassisPID.error * kP) + (sRightChassisPID.derivative * kD) );
}

bool // Check if right chassis is at the desired position
bRightChassisIsAtPos( int iDes ) {
  return abs(iDes - iGetRightChassis()) < 50 ? true : false; // Return true if so, false if not
}

/* 		DRIVE CODE END		 */
/* 		DRIVE CODE END		 */
/* 		DRIVE CODE END		 */
