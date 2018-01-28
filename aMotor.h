/* file: motor.h */
#pragma systemfile
// Create a reusable list of variables used in all PID controllers.
typedef struct {
	float current;
	float kP;
	float kI;
	float kD;
	float target;
	float error;
	float integral;
	float derivative;
	float lastError;
	float threshold;
	int   lastTime;
} pid;

pid sPID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iPID( int iDes , int iSensorInput, const float kP, const float kI, const float kD, const float kILimit) {
	sPID.current    = iSensorInput;
	sPID.error      = iDes - sPID.current;
	sPID.integral;
  if( kI != 0 ) // integral - if Ki is not 0
      { // If we are inside controlable window then integrate the error
      if( abs(sPID.error) < kILimit )
          sPID.integral = sPID.integral + sPID.error;
      else
          sPID.integral = 0;
      }
  else // Otherwise set integral to 0
      sPID.integral = 0;
  sPID.derivative = sPID.error - sPID.lastError; // Calculate Derivative
	wait1Msec(5);
	sPID.lastError = sPID.error;
	return ( (sPID.error * kP) + (sPID.integral * kI) + (sPID.derivative * kD) );
}

// Initialize an array for Truespeed Drive control. !!! NEEDS RE-TUNING !!!
int MC29[ 128 ] = {
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0, 14, 14, 15, 15, 15, 16, 16,
	17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
	21, 22, 23, 24, 25, 25, 25, 25, 25, 26,
	26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
	32, 33, 34, 35, 35, 35, 36, 36, 36, 37,
	37, 38, 38, 39, 39, 40, 40, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 50, 50,
	51, 52, 53, 54, 55, 55, 55, 56, 57, 58,
	59, 60, 60, 60, 61, 62, 63, 64, 65, 65,
	66, 67, 68, 69, 70, 70, 71, 71, 72, 72,
	73, 73, 74, 74, 74, 75, 75, 75, 76, 76,
	77, 77, 78, 78, 79, 79, 80, 83, 84, 127,
};

void	// Self-Explanatory
testAllMotors( ) {
	clearLCDLines( );
	for( int i = 0; i < 10; i++ ) {
		displayLCDNumber(0, 0, i + 1);
		motor[ i ] = 30;
		delay( 5000 );
		motor[ i ] = 0;
		clearLCDLines( );
		delay( 1000 );
	}
}


void	// Enable Slew-Rate Control on a motor.
slewMotor( int motorVar, int iSpeedDes ) {
	int iReturn = iSpeedDes-motorVar;
	motorVar = sgn(iReturn) * MC29[abs(clipNum(iReturn, 127))];
	delay( 2 );
}
