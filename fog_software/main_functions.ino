void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  readTemp(); //Read temperature
  controlHeating(); //Turn resistor on/off according to temperature

  if(fogButtonPressed() || fogFromDMX()) { fogNow(); }
  else { stopFog(); }
}
