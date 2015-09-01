void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  // DIP switches
  for(int i = 4; i <= 13; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  Serial.println(String(readMachineAvgTemperature()) + "   " + String(numberOfDipsOn())); 
  
}

int readMachineTemperature() {
  int rawValue = analogRead(A1);
  return round(map(rawValue, 0, 1023, -250, 750));
}

int readMachineAvgTemperature() {
  long val = 0;
  for(int i = 0; i <= 100; i++) {
    val += readMachineTemperature();
    delay(10);
  }
  return int(val/100);
}

void setFog(boolean doFog) {
  digitalWrite(3, doFog);
}

void setHeater(boolean doHeat) {
  digitalWrite(2, doHeat);
}

boolean readDIPSwitch(int n) {
  return digitalRead(n+3);
}

int numberOfDipsOn() {
  int toReturn = 0;
  for(int i = 0; i < 10; i++) {
    toReturn += readDIPSwitch(i);
  }
  return toReturn;
}

