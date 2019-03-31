#include <mbed.h>

DigitalIn inputPin(PC_0); 
Serial pc(USBTX, USBRX, "debug", 9600); //TX,RX

int main() {
  // verify pin availability
  if (!inputPin.is_connected()) {
    pc.printf("Error opening I/O for use.");
    return 1;
  }

  Timer t;
  // Avoid floating pin input by setting default to digital low
  inputPin.mode(PullDown);
  bool currentState;
  // lastState is used to detect a change in input state
  bool lastState=0;
  bool firstWave=1;

  while (1) {
    currentState=inputPin.read();
    // start/stop the timer on rising edge
    // on first state change start timer
    // on all subsquent state changes stop the timer,
    // reset and restart it to measure the next wave.
    if(currentState!=lastState && currentState==1) {
      if(firstWave){
      t.start();
      firstWave=0;
      }else{
      t.stop();
      pc.printf("Frequency: %.4f\n", 1/t.read());
      t.reset();
      t.start();
      }
    }
    lastState=currentState;
  }
}