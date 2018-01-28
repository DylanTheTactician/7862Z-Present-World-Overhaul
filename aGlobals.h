// General
#define iLeftDriveStick  		iJ1Ch3
#define iRightDriveStick 		iJ1Ch2
#define bMogoDwnBtn			 		bJ15U
#define bMogoUpBtn					bJ15D
#define bFieldConeBtn       bJ16U
#define bSubtractConeBtn    bJ28D
#define bAddConeBtn         bJ28U
#define bResetConeBtn       bJ28L
#define bMatchLoadBtn       bJ28R
#define bPresetWriteBtn		  bJ18L
#define bSTOPBtn						bJ27D
#define bManualArmLockSwitch bJ25U
#define bMogoIsInBtn				bJ27U
#define bMogoTypeBtn				bJ17L
#define bStatBtn						bJ25D

int   iTimeout = 100;
float fTicksToInch = ( 360 / 10.210 );
float fTicksToCm	 = ( 360 / 25.933 );
bool 	bDidAutonRun = false;
bool	bIsAConeTaskRunning = false;


// MOTOR CONTROLLER VARIABLES

int chassisLMotor;
int chassisRMotor;
int mogoLMotor;
int mogoRMotor;
int armL1Motor;
int armR1Motor;
int armL2Motor;
int armR2Motor;
int rollerMotor;

// LOCK VARIABLES

bool bLockLeftChassis	 = false;
bool bLockRightChassis = false;
bool bLockLeftMogo 		 = false;
bool bLockRightMogo 	 = false;
bool bLockLeftArm1 		 = false;
bool bLockRightArm1 	 = false;
bool bLockLeftArm2		 = false;
bool bLockRightArm2 	 = false;

int iLeftChassisLockPos;
int iRightChassisLockPos;
int iLeftMogoLockPos;
int iRightMogoLockPos;
int iArmL1LockPos;
int iArmR1LockPos;
int iArmL2LockPos;
int iArmR2LockPos;

// Drive
float fLeftChassiskP = 0.70;
float fLeftChassiskD = 0.70;
float fRightChassiskP = 0.02;
float fRightChassiskD = 0.02;


// Mogo
float fMogokP = 0.50;
float fMogokD = 0.10;
int		iMogoTimeout = 115;
int		iMogoDropTimeout = 24;

// Arm

float fArm1kP = 0.10;
float fArm1kD = 0.021;
float fArm2kP = 0.275;
float fArm2kD = 0.021;

int iLeft1Offset;
int iLeft2Offset;
int iRight1Offset;
int iRight2Offset;

void calibrateArm1(){
	int iArml1Val = -SensorValue[iLeftArm1];
	int iArmr1Val = -SensorValue[iRightArm1];
	if(SensorValue[iLeftArm1] > 0){
		iLeft1Offset = iArml1Val;
	}
	else{
		iLeft1Offset = 0;
	}

	if(SensorValue[iRightArm1] > 0){
		iRight1Offset = iArmr1Val;
	}
	else{
		iRight1Offset = 0;
	}
}

void calibrateArm2(){
	int iArml2Val = -SensorValue[iLeftArm2];
	int iArmr2Val = -SensorValue[iRightArm2];
	if(SensorValue[iLeftArm2] > 0){
		iLeft2Offset = iArml2Val;
	}
	else{
		iLeft2Offset = 0;
	}

	if(SensorValue[iRightArm2] > 0){
		iRight2Offset = iArmr2Val;
	}
	else{
		iRight2Offset = 0;
	}
}

void calibrateArm(){
	calibrateArm1();
	calibrateArm2();
}
