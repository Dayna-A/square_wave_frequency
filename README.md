# Square Wave Frequency Project
An introductory STM Microcontrollers experiment

## Created by 
[Dayna Anderson](dayna.anderson@csu.fullerton.edu)


## Solution Pseudocode

```
  Connect to input pin
  Create frequency buffer
  Connect to serial
  
  main:
    Check whether the pin is available.
    Set pin mode to default to a digital low.
    
    Initialize timer
    Initialize rising edge counter
    Initialize booleans to track the current and 
    last state of the wave and whether it is the first wave recorded.
    
    while(true):
        Read current status of the input pin.
        
        if (the status has changed from 0 to 1 [i.e. is a rising edge]):
            if (it is the first wave recorded):
                start the timer
                update the firstwave boolean to zero.
            else: 
                stop the timer
                calculate the frequency of the cycle and add it to the buffer
                reset the timer
                start the timer for the next cycle
                
                if(incremented count is equal to the buffer size):
                    print the average of the frequencies in the buffer
                    reset the rising edge counter to zero.
        set the last state equal to the current state.
    
```
