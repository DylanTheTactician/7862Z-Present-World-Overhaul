
void setArmL1( int iSpeed ) {
	armL1Motor = iSpeed;
}
// Set Right Arm Motor
void setArmR1( int iSpeed ) {
	armR1Motor = iSpeed;
}

void setArmL2( int iSpeed ) {
	armL2Motor = iSpeed;
}
// Set Right Arm Motor
void setArmR2( int iSpeed ) {
	armR2Motor = iSpeed;
}

void setArm1(int iSpeed){
	setArmL1(iSpeed);
	setArmR1(iSpeed);
}

void setArm2(int iSpeed){
	setArmL2(iSpeed);
	setArmR2(iSpeed);
}

// Get Left First Arm Potentiometer Value
int iGetArmL1() {
	return -(SensorValue[iLeftArm1] + iLeft1Offset);
}

// Get Right First Arm Potentiometer Value
int iGetArmR1() {
	return -(SensorValue[iRightArm1] + iRight1Offset);
}

// Get Left Second Arm Potentiometer Value
int iGetArmL2() {
	return (SensorValue[iLeftArm2] + iLeft2Offset);
}

// Get Right Second Arm Potentiometer Value
int iGetArmR2() {
	return (SensorValue[iRightArm2] + iRight2Offset);
}

bool bArmL1IsAtPos( int iDes ) { // Check if left first arm lift is at the desired position
  return abs(iDes - iGetArmL1()) < 40 ? true : false; // Return true if so, false if not
}

bool bArmR1IsAtPos( int iDes ) { // Check if right first arm lift is at the desired position
  return abs(iDes - iGetArmR1()) < 40 ? true : false; // Return true if so, false if not
}

bool bArmL2IsAtPos( int iDes ) { // Check if left second arm lift is at the desired position
  return abs(iDes - iGetArmL2()) < 35 ? true : false; // Return true if so, false if not
}

bool bArmR2IsAtPos( int iDes ) { // Check if right second arm lift is at the desired position
  return abs(iDes - iGetArmR2()) < 35 ? true : false; // Return true if so, false if not
}

void lockArmL1(int pos){
	iArmL1LockPos = pos;
	bLockLeftArm1 = true;
}


void lockArmR1(int pos){
	iArmR1LockPos = pos;
	bLockRightArm1 = true;
}


void lockArm1(int pos){
	lockArmL1(pos);
	lockArmR1(pos);
}

void unlockArmL1(){
	bLockLeftArm1 = false;
	iArmL1LockPos = 0;
}

void unlockArmR1(){
	bLockRightArm1 = false;
	iArmR1LockPos = 0;
}

void unlockArm1(){
	unlockArmL1();
	unlockArmR1();
}


void lockArmL2(int pos){
	iArmL2LockPos = pos;
	bLockLeftArm2 = true;
}


void lockArmR2(int pos){
	iArmR2LockPos = pos;
	bLockRightArm2 = true;
}


void lockArm2(int pos){
	lockArmL2(pos);
	lockArmR2(pos);
}

void unlockArmL2(){
	bLockLeftArm2 = false;
	iArmL2LockPos = 0;
}

void unlockArmR2(){
	bLockRightArm2 = false;
	iArmR2LockPos = 0;
}

void unlockArm2(){
	unlockArmL2();
	unlockArmR2();
}

pid sArmL1PID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iArmL1PID( int iDes ) {
	if(iDes > 0 || (bArmL1IsAtPos(0) == false)){
		const float kP = fArm1kP;
	 	const float kD = fArm1kD;
		sArmL1PID.current    = iGetArmL1();
		sArmL1PID.error      = iDes - sArmL1PID.current;
	  sArmL1PID.derivative = sArmL1PID.error - sArmL1PID.lastError; // Calculate Derivative
		taskDelay(5);
		sArmL1PID.lastError = sArmL1PID.error;
		return ( (sArmL1PID.error * kP) + (sArmL1PID.derivative * kD) );
	}
	else{
		calibrateArm1();
		return 0;
	}
}

pid sArmR1PID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iArmR1PID( int iDes ) {
	if(iDes > 0 || (bArmR1IsAtPos(0) == false)){
		const float kP = fArm1kP;
	 	const float kD = fArm1kD;
		sArmR1PID.current    = iGetArmL1();
		sArmR1PID.error      = iDes - sArmR1PID.current;
	  sArmR1PID.derivative = sArmR1PID.error - sArmR1PID.lastError; // Calculate Derivative
		taskDelay(5);
		sArmR1PID.lastError = sArmR1PID.error;
		return ( (sArmR1PID.error * kP) + (sArmR1PID.derivative * kD) );
	}
	else{
		calibrateArm1();
		return 0;
	}
}

pid sArmL2PID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iArmL2PID( int iDes ) {
	const float kP = fArm2kP;
 	const float kD = fArm2kD;
	sArmL2PID.current    = iGetArmL2();
	sArmL2PID.error      = iDes - sArmL2PID.current;
  sArmL2PID.derivative = sArmL2PID.error - sArmL2PID.lastError; // Calculate Derivative
	taskDelay(5);
	sArmL2PID.lastError = sArmL2PID.error;
	return ( (sArmL2PID.error * kP) + (sArmL2PID.derivative * kD) );
}

pid sArmR2PID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iArmR2PID( int iDes ) {
	const float kP = fArm2kP;
 	const float kD = fArm2kD;
	sArmR2PID.current    = iGetArmR2();
	sArmR2PID.error      = iDes - sArmR2PID.current;
  sArmR2PID.derivative = sArmR2PID.error - sArmR2PID.lastError; // Calculate Derivative
	taskDelay(5);
	sArmR2PID.lastError = sArmR2PID.error;
	return ( (sArmR2PID.error * kP) + (sArmR2PID.derivative * kD) );
}

void setRoller(int power){
	rollerMotor = power;
}
