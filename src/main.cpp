#include <mbed.h>

#define BUF_SIZE 2000

void calculateCycle();
void printAverage();

InterruptIn inputInterrupt(PC_0);
CircularBuffer<float, BUF_SIZE> buf;
Serial pc(USBTX, USBRX, "debug", 9600); //TX,RX
Timer t;
bool firstWave = 1;
int changeCount = 0;

int main() {
  // Attach the calculatecyle function to the rising 
  // edge of the interrupt.
  inputInterrupt.rise(&calculateCycle);
  while (1) {

  }
}

// Called by the interrupt on the rising edge to start 
// and stop the timer and record frequencies.
void calculateCycle() {
  // Start/stop the timer on rising edge
  // on first state-change start timer
  // on all subsquent state-changes stop the timer,
  // store the cycle frequency in a circular buffer
  // reset and restart it to measure the next wave.
  if (firstWave) {
    t.start();
    firstWave = 0;
  } else {
    t.stop();
    buf.push(1/t.read());
    t.reset();
    t.start();
    // Once the buffer is full, print buffer average.
    if (++changeCount == BUF_SIZE) {
      printAverage();
      changeCount = 0;
    }
  }
}
// Function to print buffer average.
void printAverage()
{
  float sum = 0, val = 0;
  for (int i = 0; i < BUF_SIZE; i++)
  {
    buf.pop(val);
    sum += val;
  }
  pc.printf("Average frequency is %.4f\n", sum / BUF_SIZE);
}