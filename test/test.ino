int temperature;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  readTemp();
  Serial.println(temperature);
  for(int i = 0; i < 100; i++) {
    digitalWrite(2, digitalRead(4));
    digitalWrite(3, digitalRead(5));
    delay(10);
  }
}

void readTemp() {
 temperature = round(map(readThermocouple(), 0, 1023, -250, 750));
} //Endof: void readTemp()


int readThermocouple() {
  return analogRead(A1);
}
