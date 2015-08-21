/*
Tällä ohjelmalla ohjataan Olarin koulun ja lukion Stairvillen savukonetta

  {
    Thermocouplen: raja-arvot: 35, 120
    Kytkentä: punainen johto - red
              vihreä johto - yellow
              
              vahvistimen vin: 5v
              vahvistimen gnd: gnd
  }


*/

//#include <DMXSerial.h> //Include DMXSerial library to receive DMX

int DMXChannel = 1; //Variable to store DMXchannel (this will change from dipswitch)

int lim_lo = 170; //Lowest temperature where we can fog
int lim_hi = 220; //Highest temperature which resistor is allowed to be
int lim_dangerous = 280;

int rawValue; //Measured value from thermocouple amplifier
int temperature; //Measured temperature

int temperatures[3];

const int resistorPin = 2; //Where the warmUp resistor is plugged
const int fogPin = 3; //Where the pumps are plugged

const int thermocouplePin = A1; //Where the thermocouple (actually amplifier output pin) is plugged

const int fogButtonPin = A4; //Where the manual fog button is plugged

const int dipSwitchPinStart = 4; //First dipSwitch pin
const int dipSwitchPinAmount = 10; //Number of "bits" in dipSwitch
