#include <stdio.h>
#include <wiringPi.h>

#define GPIO_LED 4
#define GPIO_SWITCH 13

int ledState=LOW;
// #define HIGH 1       // defined in "wiringPi.h"
// #define LOW 0        // defined in "wiringPi.h"
void toggle(){
    ledState=ledState==LOW?HIGH:LOW;
}
int main(void) 
{
    wiringPiSetupGpio();

    pinMode(GPIO_LED, OUTPUT);
    pinMode(GPIO_SWITCH, INPUT);
    
    wiringPiISR(GPIO_SWITCH,INT_EDGE_RISING,toggle);
    while(1){
        digitalWrite(GPIO_LED,ledState);
    }
}
