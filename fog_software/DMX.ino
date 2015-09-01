int receiveDMX(int ch) {
  //Return value from specific channel or zero if it hasn't been updated in last 800ms
 if (DMXSerial.noDataSince() < 800) return DMXSerial.read(ch);
 return 0;
}

// Returns true if DMX value received is over 50%.
boolean fogFromDMX() {
  if(useDmx()) return receiveDMX(DMXChannel) > 127;
  return false;
}

boolean useDmx() {
  return DMXChannel > 0 && DMXChannel <= 512;
}


int dmxChannel()  {
  return readDipSwitch()*int(readDipSwitchLast());
}

long DMXChannelLastSet;

void setDmxChannelFromDips() {
  if(millis() + 100 > DMXChannelLastSet) {
    DMXChannel = dmxChannel();
    DMXChannelLastSet = millis();
  }
}

