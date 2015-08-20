void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  readTemp(); //Read temperature
  controlHeating(); //Turn resistor on/off according to temperature

  // fogPlease is set to true if any input demands fog
  boolean fogPlease = false;
  if(fogButtonPressed()) { fogPlease = true; }
  if(fogFromDMX()) { fogPlease = true; }
  
  // If fogPlease is on, call fogNow()
  if(fogPlease) { fogNowWithoutAnyCheck(); }
  else { stopFog(); }
}
