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
  controlFog(); //Control fog output
}

void controlFog() {
  if(fogFromDMX()) {
    analogWrite(13, 255);
  } else { analogWrite(13, 0); }
}

