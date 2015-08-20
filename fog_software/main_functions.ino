void setup() {
  DMXSerial.init(DMXReceiver);
}
void loop() {
  readTemp(); //Read temperature
  controlHeating(); //Turn resistor on/off according to temperature
  controlFog(); //Control fog output
}

void controlFog() {
  if(fogButtonPressed() || fogFromDMX()) { fogNow(); }
  else { stopFog(); }
}

