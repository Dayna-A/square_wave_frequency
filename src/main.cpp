#include <mbed.h>

// Past a certain point (roughly 110 for my current test)
// increasing the buffer size ceases to increase the average
// by a significant value.
#define BUF_SIZE 1000
DigitalIn inputPin(PC_0);
CircularBuffer<float, BUF_SIZE> buf;
Serial pc(USBTX, USBRX, "debug", 9600); //TX,RX

void printAverage();
int main() {
  // Verify pin availability
  if (!inputPin.is_connected()) {
    pc.printf("Error opening I/O for use.");
    return 1;
  }

  Timer t;
  // Avoid floating pin input by setting default to digital low
  inputPin.mode(PullDown);
  bool currentState;
  // lastState is used to detect a change in input state
  bool lastState = 0;
  bool firstWave = 1;
  int count = 0;
  while (1) {
    currentState = inputPin.read();
    // Start/stop the timer on rising edge
    // on first state-change start timer
    // on all subsquent state-changes stop the timer,
    // store the cycle frequency in a circular buffer
    // reset and restart it to measure the next wave.
    if (currentState != lastState && currentState == 1) {
      if (firstWave) {
        t.start();
        firstWave = 0;
      } else {
        t.stop();
        buf.push(1 / t.read());
        t.reset();
        t.start();
        // Once the buffer is full, print buffer average.
        if (++count == BUF_SIZE) {
          printAverage();
          count = 0;
        }
      }
    }
    lastState = currentState;
  }
}

// Function to print buffer average.
void printAverage() {
  float sum = 0, val = 0;
  for (int i = 0; i < BUF_SIZE; i++) {
    buf.pop(val);
    sum += val;
  }
  pc.printf("Average frequency is %.4f\n", sum / BUF_SIZE);
}