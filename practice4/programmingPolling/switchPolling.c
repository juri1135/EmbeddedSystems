#include <stdio.h>
#include <wiringPi.h>

#define GPIO_LED 4
#define GPIO_SWITCH 13

// #define HIGH 1       // defined in "wiringPi.h"
// #define LOW 0        // defined in "wiringPi.h"

int main(void) 
{
    int switchState=LOW;
    int ledState = LOW;

    wiringPiSetupGpio();

    pinMode(GPIO_LED, OUTPUT);
    pinMode(GPIO_SWITCH, INPUT);
    
    int prev=1;
    while(1) 
    {   // push -> switch==high
        int curState=digitalRead(GPIO_SWITCH);
        if(curState==HIGH&&switchState==LOW){
            ledState=!ledState;
        }
        switchState=curState;
        digitalWrite(GPIO_LED,ledState);
       
    }
}
