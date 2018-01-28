/*------------------------------------------------*/
									/* Dictionary */

		// Define Main Controller
	// Analog Channels
#define iJ1Ch1	vexRT[Ch1]
#define iJ1Ch2	vexRT[Ch2]
#define iJ1Ch3	vexRT[Ch3]
#define iJ1Ch4	vexRT[Ch4]
	// Digital Channels
#define bJ15U		vexRT[Btn5U]
#define bJ15D		vexRT[Btn5D]
#define bJ16U		vexRT[Btn6U]
#define bJ16D		vexRT[Btn6D]
#define bJ17U		vexRT[Btn7U]
#define bJ17L		vexRT[Btn7L]
#define bJ17R		vexRT[Btn7R]
#define bJ17D		vexRT[Btn7D]
#define bJ18U		vexRT[Btn8U]
#define bJ18L		vexRT[Btn8L]
#define bJ18R		vexRT[Btn8R]
#define bJ18D		vexRT[Btn8D]

		// Define Partner Controller
	// Analog Channels
#define iJ2Ch1	vexRT[Ch1Xmtr2]
#define iJ2Ch2	vexRT[Ch2Xmtr2]
#define iJ2Ch3	vexRT[Ch3Xmtr2]
#define iJ2Ch4	vexRT[Ch4Xmtr2]
	// Digital Channels
#define bJ25U		vexRT[Btn5UXmtr2]
#define bJ25D		vexRT[Btn5DXmtr2]
#define bJ26U		vexRT[Btn6UXmtr2]
#define bJ26D		vexRT[Btn6DXmtr2]
#define bJ27U		vexRT[Btn7UXmtr2]
#define bJ27L		vexRT[Btn7LXmtr2]
#define bJ27R		vexRT[Btn7RXmtr2]
#define bJ27D		vexRT[Btn7DXmtr2]
#define bJ28U		vexRT[Btn8UXmtr2]
#define bJ28L		vexRT[Btn8LXmtr2]
#define bJ28R		vexRT[Btn8RXmtr2]
#define bJ28D		vexRT[Btn8DXmtr2]

/*------------------------------------------------*/

bool bIsJoystickAt(int channel, int value){
		return ((value - 10) < channel < (value + 10) ? true : false);
}
