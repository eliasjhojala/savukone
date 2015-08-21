void setup() {
//  DMXSerial.init(DMXReceiver);
Serial.begin(9600);
}
long serialLast = 0;
void loop() {
  pinMode(13, OUTPUT);
  readTemp(); //Read temperature
  controlHeating(); //Turn resistor on/off according to temperature
  controlFog(); //Control fog output

  if(dangerousHot()) { analogWrite(13, 255); }
  else { analogWrite(13, 0); }
  if(millis() > serialLast + 1000) {
    Serial.println("Temperature: " + String(temperature));
    Serial.println("tooCold(): " + String(tooCold()));
    Serial.println("dangerousHot(): " + String(dangerousHot()));
    Serial.println("tooHot(): " + String(tooHot()));
    Serial.println();
    serialLast = millis();
  }

  digitalWrite(3, digitalRead(4));
}

void controlFog() {
  if(fogButtonPressed() || fogFromDMX()) { fogNow(); }
  else { stopFog(); }
}

