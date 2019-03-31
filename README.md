# Square Wave Frequency Project
An introductory STM Microcontrollers experiment

## Created by 
[Dayna Anderson](dayna.anderson@csu.fullerton.edu)


## Interrupts Solution Pseudocode

```
  Initialize input interrupt
  Create frequency buffer
  Connect to serial
  Create Timer
  Inialize firstWave boolean to 1
  Initialize change counter to 0
  
  main:
      attach the calculateCylce function to the interrupt's rising edge.
      while(true):
    
    
  
  calculateCycle():
      if (it is the first wave recorded):
          start the timer
          update the firstwave boolean to zero.
      else: 
          stop the timer
          calculate the frequency of the cycle and add it to the buffer
          reset the timer
          start the timer for the next cycle
                
          if (incremented count is equal to the buffer size):
              print the average of the frequencies in the buffer
              reset the rising edge counter to zero.
      set the last state equal to the current state.
```
