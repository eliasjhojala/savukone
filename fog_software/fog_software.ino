#include <DMXSerial.h> // Include DMXSerial library to receive DMX

int DMXChannel = 0; // Variable to store DMXchannel (this will change from dipswitch)

const int lim_lo = 190; // Lowest temperature where we can fog
const int lim_hi = 240; // Highest temperature which resistor is allowed to be
const int lim_dangerous = 270;

int rawValue; // Measured value from thermocouple amplifier
int temperature; // Measured temperature

int temperatures[3];

const int resistorPin = 2; // Where the warmUp resistor is plugged
const int fogPin = 3; // Where the pumps are plugged

const int thermocouplePin = A0; // Where the thermocouple (actually amplifier output pin) is plugged

const int fogButtonPin = A4; // Where the manual fog button is plugged

const int dipSwitchPinStart = 4; // First dipSwitch pin
const int dipSwitchPinAmount = 10; // Number of "bits" in dipSwitch
