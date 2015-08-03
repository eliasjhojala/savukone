void setup() {
}
void loop() {
  readTemp();
  controlHeating();
  
  boolean fogPlease = false;
  if(fogButtonPressed()) { fogPlease = true; }
  //DMX fog code here
  
  
  if(fogPlease) { fogNow(); }
  else { stopFog(); }
}
