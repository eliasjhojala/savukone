int valueFromDMX = 0;
int receiveDMX(int ch) {
  // Determine time elapsed since last received DMX packet
  unsigned long lastPacket = DMXSerial.noDataSince();
  
  if (lastPacket < 800) {
    // read recent DMX values and set pwm levels
    valueFromDMX = DMXSerial.read(ch);
    return valueFromDMX;
  }
  else {
    // After a certain amount of time without any received DMX signal, force the fog off
    return 0;
  }
}

// Returns true if DMX value received is over 50%.
boolean fogFromDMX() {
  return receiveDMX(DMXChannel) > 127;
}
