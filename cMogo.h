
void setMogoL( int iSpeed ) {
	mogoLMotor = iSpeed;
}
// Set Right Mobile Goal Lift Motor
void setMogoR( int iSpeed ) {
	mogoRMotor = iSpeed;
}

// Get Left Mobile Goal Lift Potentiometer Value
int iGetMogoL() {
	return SensorValue[iLeftMogo];
}
// Get Right Mobile Goal Lift Potentiometer Value
int iGetMogoR() {
	return SensorValue[iRightMogo];
}

bool bMogoLIsAtPos( int iDes ) { // Check if left mobile goal lift is at the desired position
  return abs(iDes - iGetMogoL()) < 12 ? true : false; // Return true if so, false if not
}

bool bMogoRIsAtPos( int iDes ) { // Check if right mobile goal lift is at the desired position
  return abs(iDes - iGetMogoR()) < 12 ? true : false; // Return true if so, false if not
}

pid sMogoLPID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iMogoLPID( int iDes ) {
	const float kP = fMogokP;
 	const float kD = fMogokD;
	sMogoLPID.current    = iGetMogoL();
	sMogoLPID.error      = iDes - sMogoLPID.current;
  sMogoLPID.derivative = sMogoLPID.error - sMogoLPID.lastError; // Calculate Derivative
	taskDelay(5);
	sMogoLPID.lastError = sMogoLPID.error;
	return ( (sMogoLPID.error * kP) + (sMogoLPID.derivative * kD) );
}

pid sMogoRPID;
  // Cookie-Cutter PID loop for intelligently reaching a desired destination.
int iMogoRPID( int iDes ) {
	const float kP = fMogokP;
 	const float kD = fMogokD;
	sMogoRPID.current    = iGetMogoR();
	sMogoRPID.error      = iDes - sMogoRPID.current;
  sMogoRPID.derivative = sMogoRPID.error - sMogoRPID.lastError; // Calculate Derivative
	taskDelay(5);
	sMogoRPID.lastError = sMogoRPID.error;
	return ( (sMogoRPID.error * kP) + (sMogoRPID.derivative * kD) );
}

	bool bMogoIsIn	= false;

task MogoControl(){
	bMogoIsIn	= false;
	int  iMogoTime 	= 0;
	int	 iDownButtonTime = 0;

	if(bDidAutonRun == true){
	 	bMogoIsIn = true;
	}
	else{
		SensorValue[ iLeftMogo  ] = 0;
		SensorValue[ iRightMogo ] = 0;
	}


	while( !( bMogoLIsAtPos( -1070 ) && bMogoRIsAtPos( 1070 ) ) ){
		setMogoL(-iMogoLPID(-1070));
		setMogoR( iMogoRPID( 1070));
		taskDelay(20);
	}

	while(true){

		while (((iUltrasonicGet(mogoSonar) >= 4) && bMogoIsIn == false) && bMogoUpBtn == false){
			taskDelay(50);
		}

		if(((iUltrasonicGet(mogoSonar) <= 5 || (152 > iUltrasonicGet(mogoSonar) > 148) || (620 > iUltrasonicGet(mogoSonar) > 610)) && bMogoIsIn == false) || bMogoUpBtn == true){
			taskDelay(100);
			setMogoL(50);
			setMogoR(50);
			taskDelay(250);
			while((digitalRead(mogoButton) ==  false) && !(iMogoTime == iMogoTimeout)){
				setMogoL(-iMogoLPID( -120 ));
				setMogoR( iMogoRPID(  120	));
				taskDelay(20);
				iMogoTime++;
			}
			if(bMogoIsIn == true){
				iMogoTimeout = 0;
			}
			setMogoL(0);
			setMogoR(0);
			bMogoIsIn = true;
		}

		if(iMogoTime == iMogoTimeout){		// Oops we dropped the mogo
				bMogoIsIn = false;
				iMogoTime = 0;
				while( !( bMogoLIsAtPos( -1070 ) && bMogoRIsAtPos( 1070 ) ) ){
					setMogoL(-iMogoLPID(-1070));
					setMogoR( iMogoRPID( 1070));
				}
			}

		if (bMogoIsIn == true){
			if(bMogoDwnBtn){
				setMogoL(100);
				setMogoR(100);
				iDownButtonTime++;
				taskDelay(20);
			}
			else if(bMogoUpBtn){
				setMogoL(-100);
				setMogoR(-100);
				iDownButtonTime = 0;
				taskDelay(20);
			}
			else{
				setMogoL(0);
				setMogoR(0);
				iDownButtonTime = 0;
				taskDelay(20);
			}
			if(iDownButtonTime == iMogoDropTimeout){
				while(bMogoIsIn == true){
					setMogoL(0);
					setMogoR(0);
					iDownButtonTime = 0;
					if( 850 <= (-iGetMogoL() || iGetMogoR()) <= 920 ){
						taskDelay(1500);
						while( !( bMogoLIsAtPos( -1070 ) && bMogoRIsAtPos( 1070 ) ) ){
							setMogoL(-iMogoLPID(-1075));
							setMogoR( iMogoRPID( 1075));
						}
					}
					bMogoIsIn			  = false;
				}
			}
		}

	} // while(true)
} // Task
