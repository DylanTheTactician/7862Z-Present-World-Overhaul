task motorController(){
    while(true){
        motorSet(chassis_l, (bLockLeftChassis  ? iLeftChassisPID(iLeftChassisLockPos)   : chassisLMotor));
        motorSet(chassis_r, (bLockRightChassis ? iRightChassisPID(iRightChassisLockPos) : chassisRMotor));
        motorSet(mogo_l        , (bLockLeftMogo     ? iMogoLPID(iLeftMogoLockPos)            : mogoLMotor));
        motorSet(mogo_r        , (bLockRightMogo    ? iMogoRPID(iRightMogoLockPos)           : mogoRMotor));
        motorSet(arm_l1        , ((bLockLeftArm1  && bIsJoystickAt(iJ2Ch2, 0)) ? iArmL1PID(iArmL1LockPos) : (armL1Motor + (iJ2Ch2 * 0.6))));
        motorSet(arm_r1        , ((bLockRightArm1 && bIsJoystickAt(iJ2Ch2, 0)) ? iArmR1PID(iArmR1LockPos) : (armR1Motor + (iJ2Ch2 * 0.6))));
        motorSet(arm_l2        , (bLockLeftArm2     ? iArmL2PID(iArmL2LockPos)               : armL2Motor));
        motorSet(arm_r2        , (bLockRightArm2    ? iArmR2PID(iArmR2LockPos)               : armR2Motor));
        motorSet(roller        , rollerMotor);
    }
}

task coneCountManager(){
    while(true){
    	/*
        if(bMatchLoadBtn){
        	while(bMatchLoadBtn){ // Waits for the button to be released to start the task to prevent repeated task start
    				delay( 20 ); //Don't hog the CPU!
    			}
    			startTask(matchLoads);
    		}*/
    		if(bSTOPBtn){
    			stopTask(matchLoads);
    			stopTask(fieldCones);
    			setArm1(0);
    			setArm2(0);
    			while(bSTOPBtn){ // Waits for the button to be released to start the task to prevent repeated task start
    				delay( 20 ); //Don't hog the CPU!
    			}
    		}
    		else if(bFieldConeBtn){
    			startTask(fieldCones);
        	while(bFieldConeBtn){ // Waits for the button to be released to start the task to prevent repeated task start
    				delay( 20 ); //Don't hog the CPU!
    			}
    		}

			if(bIsAConeTaskRunning == false){
	    	if(bResetConeBtn){
	    	    while(bResetConeBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    		}
	    		iConeStack = 0;
	    	}
	    	else if(bSubtractConeBtn){
	    	    while(bSubtractConeBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    		}
	    		iConeStack--;
	    	}
	    	else if(bAddConeBtn){
	    	    while(bAddConeBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    		}
	    		iConeStack++;
	    	}
    	}
			if(bMogoIsInBtn){
				bMogoIsIn	= true;
	    	while(bMogoIsInBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    	}

	    	}

	    if(bMogoTypeBtn){
				bMogoType	= false;
	    	while(bMogoTypeBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    	}

	    	}

	    	/*if(bStatBtn){
	    	    while(bStatBtn){ // Waits for the button to be released to start the task to prevent repeated task start
	    		delay( 20 ); //Don't hog the CPU!
	    		}
	    		startTask(statGoal);
	    	}*/

	    if(bMogoType == false){
	    	stopTask(MogoControl);
	    }
    }
}

task dumbControl(){
    unlockArm1();
    unlockArm2();
    while(true){
    // TRASH MANUAL CODE
		setArmL1((iJ2Ch2 * .7)+5);
		setArmR1((iJ2Ch2 * .7)+5);
		setArmL2(iJ2Ch3 * .6);
		setArmR2(iJ2Ch3 * .6);
		if(bJ25U){
			motor[roller] = 127;
		}
		else if(bJ25D){
			motor[roller] = -65;
		}
		else{
			motor[roller] = -20;
		}
		taskDelay(20);
    }
}
