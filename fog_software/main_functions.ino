void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  readTemp();
  controlHeating();
  
  boolean fogPlease = false;
  if(fogButtonPressed()) { fogPlease = true; }
  if(fogFromDMX()) { fogPlease = true; }
  
  
  if(fogPlease) { fogNow(); }
  else { stopFog(); }
}
