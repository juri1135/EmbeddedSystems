#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define PIN 18
#define PWM_CLOCK_DIVISOR 384   // This will generate 50,000 Hz from 19.2 MHz clock source
#define PWM_RANGE 1024          // The total number of clock ticks during a period
                                // This is equivalent to a period of 20 ms

void moveMotor(int degree)
{
    float dutyCycle;        // the unit is %
    int pulseWidth;         

    /////////////////////////////////////////////////////////////////////
    // Insert your code here
    pinMode(PIN,PWM_OUTPUT);
    // Insert your code here
    dutyCycle=5.0+((float)degree/180)*5;
    float mul=PWM_RANGE/100;
    pulseWidth=(int)(mul*dutyCycle);
    pwmWrite(PIN,pulseWidth);
    printf("dutyCycle = %.1f%%\n",dutyCycle);
    printf("pulseWidth = %d\n\n",pulseWidth);
    /////////////////////////////////////////////////////////////////////
}

int main(void) 
{
    int inputValue;

    wiringPiSetupGpio();

    /////////////////////////////////////////////////////////////////////
    // Insert your code here
    // Your code should initialize PWM by using the following functions
    // --> pinMode(), pwmSetMode(), pwmSetClock(), pwmSetRange()
    pinMode(PIN,PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(PWM_CLOCK_DIVISOR);
    pwmSetRange(PWM_RANGE);
    /////////////////////////////////////////////////////////////////////
        
    while(1) 
    {
        printf("Enter value: ");
        scanf("%d", &inputValue);
        
        moveMotor(inputValue);
        
        delay(600);
    }    
    
    return 0;
}
