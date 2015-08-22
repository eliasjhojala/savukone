void setup() {
//  DMXSerial.init(DMXReceiver);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}


long serialLast = 0;
void loop() {
  readMachineTemperature();
  controlHeating(); //Turn resistor on/off according to temperature
//  controlFog(); //Control fog output

  if(millis() > serialLast + 1000) {
    Serial.print("Temperature: " + String(temperature));
    Serial.print("   tooCold(): " + String(tooCold()));
    Serial.print("   dangerousHot(): " + String(dangerousHot()));
    Serial.print("   tooHot(): " + String(tooHot()));
    Serial.print("   shouldHeatUp(): " + String(shouldHeatUp()));
    Serial.print("   shouldStopHeating(): " + String(shouldStopHeating()));
    
    Serial.println();
    serialLast = millis();
  }

  digitalWrite(3, digitalRead(4)); //Control fog
}

void controlFog() {
  if(fogButtonPressed() || fogFromDMX()) {
    fogNow();
  } else { stopFog(); }
}

