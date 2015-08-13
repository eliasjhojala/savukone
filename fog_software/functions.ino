
// Reads average temperature of the fog chamber over a period of time to cancel
// out any instabilities in the readings.
int timesRead = 0;
int readTempI1, readTempI2, readTempTemperature; // I = index
long readTempMillis, readTempToWait;
const int timesToReadFast = 100;
const int timesToReadSlow = 10;
const int shortTimeToWait = 1;
const int longTimeToWait = 1000;

void readTemp() {
 temperature = round(map(readThermocouple(), 0, 1023, -250, 750));
} //Endof: void readTemp()

// Returns raw value from thermocouple.
int readThermocouple() {
  return analogRead(thermocouplePin);
}

// Returns true when the fog chamber is heated properly
boolean suitableTemperature() {
  return !tooCold() && !dangerousHot();
}

// Temperature comparison functions
boolean singleDangerousHot(int val) { return val > lim_hi+(limitRange()/2); }
boolean singleTooHot(int val) { return val > lim_hi; }
boolean singleTooCold(int val) { return val < lim_lo; }
boolean shouldHeatUp() { return temperature < (lim_lo+(limitRange()/2)); }
boolean shouldStopHeating() { return tooHot(); }

// Returns true if the fog chamber is starting to get too hot. (Still operatable)
boolean tooHot() {
  /*
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleTooHot(temperatures[i])) {
      toReturn = true;
    }
  }
  */
  return singleTooHot(temperature);
}

// Returns true if the fog chamber is starting to get too cold.
boolean tooCold() {
  /*
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleTooCold(temperatures[i])) {
      toReturn = true;
    }
  }
  */
  return singleTooCold(temperature);
}

// Returns true if the fog chamber is starting to get dangerously hot. (Do not operate)
boolean dangerousHot() {
  /*
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleDangerousHot(temperatures[i])) {
      toReturn = true;
    }
  }
  */
  return singleDangerousHot(temperature);
}

// Returns the difference between the temperature lower and upper limits.
int limitRange() {
  return lim_hi-lim_lo;
}

void controlHeating() {
  if(shouldHeatUp()) { startHeating(); } // Start heating if temp is too low
  if(shouldStopHeating()) { stopHeating(); } // Stop heating if temp is enough high
}

void startHeating() { analogWrite(resistorPin, 255); } // Start heating by turnin resistor pin on
void stopHeating() { analogWrite(resistorPin, 0); } // Stop heating by turning resistor pin off

void fogNow() {
  if(suitableTemperature()) { fogNowWithoutAnyCheck(); }
  else { stopFog(); }
}

void fogNowWithoutAnyCheck() { analogWrite(fogPin, 255); } // Fog now without checking temperatures by turning fog pin on
void stopFog() { analogWrite(fogPin, 0); } // Stop fog

// Checks if physical fog button is depressed.
boolean fogButtonPressed() {
  return digitalRead(fogButtonPin);
}

// Read all but last dip-switch and decode the binary output
int readDipSwitch() {
  int toReturn = 0;
  // Works as long as dipSwitchPinAmount 15 or less (int is 16bit, sign bit included)
  // dipSwitchPinAmount should be 10 or over for full DMX channel range (last
  //  switch is the additional boolean)
  for(int i = 0; i < dipSwitchPinAmount-1; i++) {
    toReturn += digitalRead(dipSwitchPinStart + i) << i;
  }
  return toReturn;
}

// Read last dip-switch for an additional boolean
boolean readDipSwitchLast() {
  return digitalRead(dipSwitchPinStart + dipSwitchPinAmount-1) == HIGH;
}
