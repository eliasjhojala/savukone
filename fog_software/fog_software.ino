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

const int raw_lim_lo = 440;
const int raw_lim_hi = 520;

const int lim_lo = 180;
const int lim_hi = 260;

int rawValue;
int temperature;

int temperatures[3];

const int resistorPin = 2;
const int fogPin = 3;

const int thermocouplePin = A2;

const int fogButtonPin = 4;
