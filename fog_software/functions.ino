
// Reads average temperature of the fog chamber over a period of time to cancel
// out any instabilities in the readings.

unsigned long temperatureSum = 0;
int counter = 0;
unsigned long lastMillis = 0;

int lastTemperature = 0;
int temperatureDifference = 0;
unsigned long temperatureSaved = 0;
unsigned long lastTemperatureSaved = 0;
float temperatureDifferenceInMinute = 0;

unsigned long startedHeating = 0;
unsigned long stoppedHeating = 0;
boolean heatedTooLong = false;
boolean heatingOn = false;

void readMachineTemperature() {
  if (millis() >= lastMillis + 1) { // Measure at most once per ms
    counter++;
    lastMillis = millis();
    
    temperatureSum += readThermocouple();
    if (counter > 2000 || (counter > 200 && temperature == 0)) { // take 2000 points for avg, or 200 points if first time to get value fast
      
      lastTemperature = temperature;
      lastTemperatureSaved = temperatureSaved;
      
      temperature = temperatureSum / counter; // count avg value
      temperature = round(map(temperature, 0, 1023, -250, 750)); // map raw value to temperature as celsius degrees
      temperatureSaved = millis();
      temperatureDifference = abs(lastTemperature - temperature);
      temperatureDifferenceInMinute = float(temperatureDifference) / (temperatureSaved - lastTemperatureSaved) * 60*1000;
      
      // Reset variables
      counter = 0;
      temperatureSum = 0;
    }
  }
}


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
boolean singleTooHot(int val) { return val > lim_hi; }
boolean singleTooCold(int val) { return val < lim_lo; }

boolean singleTemperatureError(int val) {
  boolean error = false;
  
  error |= val < 0 || val > 400
  
  if (heatingOn && (millis() - startedHeating > 20*60*1000)) {
    heatedTooLong = true;
  }
  
  if (heatedTooLong && !heatingOn && (millis() - stoppedHeating > 20*60*1000)) {
    heatedTooLong = false;
  }
  
  error |= heatedTooLong;
  error |= temperatureDifferenceInMinute > 50;
  
  return error;
}

boolean shouldHeatUp() { return !shouldStopHeating() && temperature < (lim_hi-(limitRange()/3)); }
boolean shouldStopHeating() { return tooHot() || temperatureError(); }

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

// Returns true if there is some error with temperature measurment
boolean temperatureError() {
  return singleTemperatureError(temperature);
}

// Returns the difference between the temperature lower and upper limits.
int limitRange() {
  return lim_hi-lim_lo;
}

void controlHeating() {
  if (shouldHeatUp()) startHeating();     // Start heating if temp is too low
  if (shouldStopHeating()) stopHeating(); // Stop heating if temp is high enough
}

void startHeating() {
  analogWrite(resistorPin, 255); // Start heating by turnin resistor pin on
  if (!heatingOn) {
    startedHeating = millis();
    heatingOn = true;
  }
}

void stopHeating() {
  analogWrite(resistorPin, 0); // Stop heating by turning resistor pin off
  if (heatingOn) {
    stoppedHeating = millis();
    heatingOn = false;
  }
}

void fogNow() {
  if (suitableTemperature()) fogNowWithoutAnyCheck();
  else stopFog();
}

void fogNowWithoutAnyCheck() { analogWrite(fogPin, 255); } // Fog now without checking temperatures by turning fog pin on
void stopFog() { analogWrite(fogPin, 0); }

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
  for (int i = 0; i < dipSwitchPinAmount-1; i++) {
    toReturn |= digitalRead(dipSwitchPinStart + i) << i;
  }
  return toReturn;
}

// Read last dip-switch for an additional boolean
boolean readDipSwitchLast() {
  return digitalRead(dipSwitchPinStart + dipSwitchPinAmount-1);
}
