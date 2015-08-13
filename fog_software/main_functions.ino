void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  analogWrite(A5, 255);
  analogWrite(A0, 0);
  analogWrite(A2, 0);
  analogWrite(A3, 255);
  readTemp();
  controlHeating();

  // fogPlease is set to true if any input demands fog
  boolean fogPlease = false;
  if(fogButtonPressed()) { fogPlease = true; }
  if(fogFromDMX()) { fogPlease = true; }
  
  // If fogPlease is on, call fogNow()
  if(fogPlease) { fogNowWithoutAnyCheck(); }
  else { stopFog(); }
}
