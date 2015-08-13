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

#include <DMXSerial.h>

int DMXChannel = 1;

int raw_lim_lo = 440;
int raw_lim_hi = 520;

int lim_lo = 180;
int lim_hi = 260;

int rawValue;
int temperature;

int temperatures[3];

const int resistorPin = 2;
const int fogPin = 3;

const int thermocouplePin = A1;

const int fogButtonPin = A4;

const int dipSwitchPinStart = 4;
const int dipSwitchPinAmount = 10;
