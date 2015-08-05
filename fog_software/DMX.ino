int valueFromDMX = 0;
int receiveDMX(int ch) {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels 
    valueFromDMX = DMXSerial.read(ch);
    return valueFromDMX;
  }
  else {
    return 0;
  }
}

boolean fogFromDMX() {
  return receiveDMX(DMXChannel) > 127;
}
