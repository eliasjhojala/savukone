int timesRead = 0;
void readTemp() {
  timesRead++;
  if(timesRead >= 3) { timesRead = 0; }
  int tempTemperature = readThermocouple();
  for(int j = 0; j < 10; j++) {
    for(int i = 0; i < 100; i++) {
      tempTemperature = (tempTemperature + readThermocouple()) / 2;
      delay(1);
    }
    delay(1000);
  }
  rawValue = tempTemperature;
  temperature = round(map(rawValue, 0, 1023, -250, 750));
  temperatures[timesRead] = temperature;
} //Endof: void readTemp()

int readThermocouple() {
  return analogRead(thermocouplePin);
}

boolean suitableTemperature() {
  return !tooCold() && !dangerousHot();
}
boolean singleDangerousHot(int val) { return val > lim_hi+limitRange()/2; }
boolean singleTooHot(int val) { return val > lim_hi; }
boolean singleTooCold(int val) { return val < lim_lo; }
boolean shouldHeatUp() { return temperature < lim_lo+limitRange()/2; }
boolean shouldStopHeating() { return tooHot(); }

boolean tooHot() {
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleTooHot(temperatures[i])) {
      toReturn = true;
    }
  }
}

boolean tooCold() {
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleTooCold(temperatures[i])) {
      toReturn = true;
    }
  }
}

boolean dangerousHot() {
  boolean toReturn = false;
  for(int i = 0; i < 3; i++) {
    if(singleDangerousHot(temperatures[i])) {
      toReturn = true;
    }
  }
}

int limitRange() {
  return lim_hi-lim_lo;
}

void controlHeating() {
  if(shouldHeatUp) { startHeating(); } //Start heating if temp is too low
  if(shouldStopHeating) { stopHeating(); } //Stop heating if temp is enough high
}

void startHeating() { analogWrite(resistorPin, 255); } //Start heating by turnin resistor pin on
void stopHeating() { analogWrite(resistorPin, 0); } //Stop heating by turning resistor pin off

void fogNow() {
  if(suitableTemperature()) { fogNowWithoutAnyCheck(); }
  else { stopFog(); }
}

void fogNowWithoutAnyCheck() { analogWrite(fogPin, 255); } //Fog now without checking temperatures by turning fog pin on 
void stopFog() { analogWrite(fogPin, 0); } //Stop fog

boolean fogButtonPressed() {
  return digitalRead(fogButtonPin);
}
