#include <mbed.h>

DigitalIn inputPin(USER_BUTTON); 
DigitalOut inputIndicatorLED(LED2);
Serial pc(USBTX, USBRX, "debug", 9600); //TX,RX

int main() {
  // verify pin availability
  if (!inputPin.is_connected() || !inputIndicatorLED.is_connected()) {
    pc.printf("Error opening I/O for use.");
    return 1;
  }
  // ensure LED starts in the off state
  inputIndicatorLED.write(0);
  Timer t;
  // Avoid floating pin input by setting default to digital low
  inputPin.mode(PullDown);
  bool currentState;
  // recentState is used to detect a change in input state
  bool recentState=0;
  while (1) {
    currentState=inputPin.read();
    if (currentState!=recentState){
      // start the timer on rising edge or
      // stop and reset timer on falling edge
      if(currentState) {
        t.start();
      }else{
        t.stop();
        pc.printf("Pin was on for %.4f seconds\n",t.read());
        t.reset();
      }
      recentState=currentState;
    }
    // turn on/off led to match pin signal
    inputIndicatorLED = inputPin; 
  }
}