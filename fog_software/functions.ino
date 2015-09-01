
// Reads average temperature of the fog chamber over a period of time to cancel
// out any instabilities in the readings.

unsigned long temperatureSum = 0;
int counter = 0;
unsigned long lastMillis = 0;

void readMachineTemperature() {
if(millis() >= lastMillis + 1) {                // delay without pausing the whole software
    counter++;                                  // delay....
    lastMillis = millis();                      // delay....

    temperatureSum += readThermocouple(); 
    if(counter > 500 || (counter > 100 && temperature == 0)) { // take 500 points for avg, or 100 points if first time to get value fast

      temperature = int(temperatureSum / counter); // count avg value
      temperature = round(map(temperature, 0, 1023, -250, 750)); // map raw value to temperature as celsius degrees
      
      //sanitizing variables
      counter = 0;
      temperatureSum = 0;
    }
  } // Endof: delay 
} //Endof: readMachineTemperature()


// Returns raw value from thermocouple.
int readThermocouple() {
  return analogRead(thermocouplePin);
}

// Returns true when the fog chamber is heated properly
boolean suitableTemperature() {
  return !tooCold() && !dangerousHot();
}

// Temperature comparison functions
boolean singleDangerousHot(int val) { return val > lim_dangerous; }
boolean singleTooHot(int val) { return val > lim_hi-20; }
boolean singleTooCold(int val) { return val < lim_lo; }
boolean shouldHeatUp() { return temperature < (lim_lo+(limitRange()/2)); }
boolean shouldStopHeating() { return tooHot(); }


// Returns true if the fog chamber is starting to get too hot. (Still operatable)
boolean tooHot() {
  return singleTooHot(temperature);
}

// Returns true if the fog chamber is starting to get too cold.
boolean tooCold() {
  return singleTooCold(temperature);
}

// Returns true if the fog chamber is starting to get dangerously hot. (Do not operate)
boolean dangerousHot() {
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


