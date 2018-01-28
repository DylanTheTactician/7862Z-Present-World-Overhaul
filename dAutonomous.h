
int iConeStack = 0;
int iTime = 0;
int iConeOffset;


void arm1GoTo(int Height){

	if(bArmL1IsAtPos(Height) == false){
		unlockArmL1();
	}
	if(bArmR1IsAtPos(Height) == false){
		unlockArmR1();
	}

	while(((bArmL1IsAtPos(Height) || bArmR1IsAtPos(Height)) == false) && iTime < iTimeout){
		if(bArmL1IsAtPos(Height) == false){
			setArmL1((Height > iGetArmL1()) ? 86 : -86);
		}
		else{
			if(iArmL1LockPos == 0){
				lockArmL1(Height);
			}
		}
		if(bArmR1IsAtPos(Height) == false){
			setArmR1((Height > iGetArmR1()) ? 86 : -86);
		}
		else{
			if(iArmR1LockPos == 0){
				lockArmR1(Height);
			}
		}
		taskDelay(20);
		iTime++;
	}
	lockArm1(Height);
	iTime = 0;
}


void arm2GoTo(int Height){

	if(bArmL2IsAtPos(Height) == false){
		unlockArmL2();
	}
	if(bArmR2IsAtPos(Height) == false){
		unlockArmR2();
	}

	while(((bArmL2IsAtPos(Height) || bArmR2IsAtPos(Height)) == false) && iTime < iTimeout){
		if(bArmL2IsAtPos(Height) == false){
			setArmL2(iArmL2PID(Height));
		}
		else{
			lockArmL2(Height);
		}
		if(bArmR2IsAtPos(Height) == false){
			setArmR2(iArmR2PID(Height));
		}
		else{
			lockArmR2(Height);
		}
	taskDelay(20);
	iTime++;
	}
lockArm2(Height);
iTime = 0;
}


void stackMatchLoad(int height1, int height2, bool order){
	bIsAConeTaskRunning = true;
		if(order == true){
			setRoller(-45);
			arm1GoTo(650); // 650 is the Auto loader height for the DR4
			taskDelay(200);
			arm2GoTo(2300);
			taskDelay(200);
		}
		else{
			setRoller(-45);
			arm2GoTo(2300);
			taskDelay(200);
			arm1GoTo(650);
			taskDelay(200);
		}
		arm1GoTo(height1 + 250);
		taskDelay(200);
		arm2GoTo(height2);
		taskDelay(200);
		if(iConeStack > 0){
			arm1GoTo(height1 - 150);
			taskDelay(200);
			setRoller(80);
			taskDelay(200);
			arm1GoTo(height1 + 350);
		}
		else{
			arm1GoTo(200);
			setRoller(80);
		}
		taskDelay(500);
		setRoller(-45);
		bIsAConeTaskRunning = false;
		iConeStack++;
}

task matchLoads ( ) {
	while(iConeStack < 12){
		switch(iConeStack){

			case 0:
				stackMatchLoad( 319, 165, 1 );
				break;

			case 1:
				stackMatchLoad( 334, 165, 1 );
				break;

			case 2:
				stackMatchLoad( 481, 165, 1 );
				break;

			case 3:
				stackMatchLoad( 623, 165, 0 );
				break;

			case 4:
				stackMatchLoad( 769, 165, 0 );
				break;

			case 5:
				stackMatchLoad( 905, 165, 0 );
				break;

			case 6:
				stackMatchLoad( 1054, 165, 0 );
				break;

			case 7:
				stackMatchLoad( 1181, 165, 0 );
				break;

			case 8:
				stackMatchLoad( 1289, 165, 0 );
				break;

			case 9:
				stackMatchLoad( 1396, 200, 0 );
				break;

			case 10:
				stackMatchLoad( 1500, 220, 0 );
				break;

			case 11:
				stackMatchLoad( 1625, 240, 0 );
				stopTask(matchLoads);
				break;
		}
	}
}

void stackCone(int height1, int height2, bool order){
	bIsAConeTaskRunning = true;
		if(order == true){
			setRoller(-45);
			arm1GoTo(0); // 650 is the Auto loader height for the DR4
			taskDelay(200);
			arm2GoTo(2300);
			taskDelay(200);
		}
		else{
			setRoller(-45);
			arm2GoTo(2300);
			taskDelay(200);
			arm1GoTo(0);
			taskDelay(200);
		}
		arm1GoTo(height1 + 250);
		taskDelay(200);
		arm2GoTo(height2);
		taskDelay(200);
		if(iConeStack > 0){
			arm1GoTo(height1 - 150);
			taskDelay(200);
			setRoller(80);
			taskDelay(200);
			arm1GoTo(height1 + 350);
		}
		else{
			arm1GoTo(0);
			setRoller(80);
		}
		taskDelay(500);
		setRoller(-45);
		bIsAConeTaskRunning = false;
		iConeStack++;
}


task fieldCones ( ) {

	switch(iConeStack){

	case 0:
			stackCone( 319, 140, 1 );
			break;

		case 1:
			stackCone( 334, 140, 1 );
			break;

		case 2:
			stackCone( 481, 140, 0 ); // 147
			break;

		case 3:
			stackCone( 623, 120, 0 ); // 142
			break;

		case 4:
			stackCone( 769, 120, 0 ); // 146
			break;

		case 5:
			stackCone( 905, 120, 0 ); // 136
			break;

		case 6:
			stackCone( 1054, 120, 0 ); // 149
			break;

		case 7:
			stackCone( 1200, 110, 0 );
			break;

		case 8:
	    stackCone( 1344, 100, 0 );
			break;

		case 9:
			//stackCone((350 + iConeOffset), Arm2HeightMatchLoads, false);
			break;

		case 10:
			//stackCone((350 + iConeOffset), Arm2HeightMatchLoads, false);
			break;

		case 11:
			//stackCone((350 + iConeOffset), Arm2HeightMatchLoads, false);
			stopTask(matchLoads);
			break;

		case 12:
	 		//stackCone((350 + iConeOffset), Arm2HeightMatchLoads, false);
			break;
	}
	stopTask(fieldCones);
}


task statGoal(){
	 stackCone( 953, 1234, 0 );
	 iConeStack--;
	 stopTask(statGoal);
}
/*void autonomous1 ( ) {		// stupid order of includes
	startTask(motorController);
	calibrateArm();
	arm1GoTo(775);
	startTask(MogoControl);
	tankWithoutTrueSpeed(50, 50);
	taskDelay(4000);
	tankWithoutTrueSpeed(0, 0);
	bDidAutonRun = true;
}*/
