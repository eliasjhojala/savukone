void setup() {
  DMXSerial.init(DMXReceiver);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  for(int i = 4; i <= 13; i++) {
    pinMode(i, INPUT);
  }
}


long serialLast = 0;
void loop() {
  setDmxChannelFromDips();
  readMachineTemperature();
  controlHeating(); //Turn resistor on/off according to temperature
  controlFog(); //Control fog output
}

void controlFog() {
  if(fogButtonPressed() || fogFromDMX()) {
    fogNow();
  } else { stopFog(); }
}

