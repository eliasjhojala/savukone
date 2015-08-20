int receiveDMX(int ch) {
  //Return value from specific channel or zero if it hasn't been updated in last 800ms
  if (DMXSerial.noDataSince() < 800) return DMXSerial.read(ch);
  else return 0;
}

// Returns true if DMX value received is over 50%.
boolean fogFromDMX() {
  return receiveDMX(DMXChannel) > 127;
}
