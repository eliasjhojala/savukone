/*
DI --> GND
DE --> GND
RE --> GND
RO --> RX

GND --> DMX GND + Arduino GND
A --> DMX A
B --> DMX B
VCC --> Arduino 5V
*/


int receiveDMX(int ch) {
  // Return value from specific channel or zero if it hasn't been updated in last 800ms
  if (DMXSerial.noDataSince() < 800) return DMXSerial.read(ch);
  return 0;
}

// Returns true if DMX value received is over 50%.
boolean fogFromDMX() {
  return useDmx() && receiveDMX(DMXChannel) > 127;
}

boolean useDmx() {
  return DMXChannel > 0 && DMXChannel <= 512;
}

int dmxChannel() {
  return readDipSwitch() * readDipSwitchLast();
}

// Read DMX channel only every 100 ms
long DMXChannelLastUpdated = 0;
void setDmxChannelFromDips() {
  if(millis() > DMXChannelLastUpdated + 100) {
    DMXChannel = dmxChannel();
    DMXChannelLastUpdated = millis();
  }
}
