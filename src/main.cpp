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
  
  // Avoid floating pin input by setting default to digital low
  inputPin.mode(PullDown);

  while (1) {
    pc.printf("ConnectedPin has value: %d \n", inputPin.read());
    // turn on/off led to match pin signal
    inputIndicatorLED = inputPin; 
    wait(0.25);
  }
}