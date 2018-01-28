// Math
#pragma systemfile

int tickConvertInch (float inch)
{
    int ticks = inch*fTicksToInch;
    return ticks;
}

int tickConvertCentimeter (float cm)
{
    int ticks = cm*fTicksToCm;
    return ticks;
}

int iFilterUltrasonic(int ultrasonic)	// Ultrasonic Filter
{
	const int clipperValue  = 25;	  // Outlier threshold
	int iLastValue		= ultrasonic;	// Set last value as the ultrasonic read
	wait1Msec(10);									// Wait ten milliseconds
	int iCurrentValue	= ultrasonic;	// Set the new value as the ultrasonic read
	if(abs(iCurrentValue) > iLastValue + clipperValue || abs(iCurrentValue) < iLastValue)
	 {iCurrentValue = iLastValue;}	// filter outlier data out if the above statement is true
	return iCurrentValue;	// Return the (filtered) Ultrasonic value
}
