void setup() {
  Serial.begin(9600);
}
int numberOfBits = 10;
int bits[10];
void loop() {
  int val = 0;
  for(int i = 0; i < numberOfBits; i++) {
    val += digitalRead(i+4)*(round(pow(2, i)));
  }
  Serial.println(val);
}
