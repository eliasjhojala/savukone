void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  readTemp();
  controlHeating();
  
  // fogPlease is set to true if any input demands fog
  boolean fogPlease = false;
  if(fogButtonPressed()) { fogPlease = true; }
  if(fogFromDMX()) { fogPlease = true; }
  
  // If fogPlease is on, call fogNow()
  if(fogPlease) { fogNow(); }
  else { stopFog(); }
}
