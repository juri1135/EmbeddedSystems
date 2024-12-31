#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define PIN 18
#define PWM_RANGE 200

void moveMotor(int degree)
{
    float dutyCycle;        // the unit is %
    int pulseWidth;         
    pinMode(PIN,PWM_OUTPUT);
    // Insert your code here
    dutyCycle=5+((float)degree/180)*5;
    float mul=PWM_RANGE/100;
    pulseWidth=(int)(mul*dutyCycle);
    softPwmCreate(PIN, pulseWidth, PWM_RANGE);
    softPwmWrite(PIN,pulseWidth);
    printf("dutyCycle = %.1f%\n",dutyCycle);
    printf("pulseWidth = %d\n\n",pulseWidth);
}

int main() 
{
    int inputValue;         // the unit is degree
    
    wiringPiSetupGpio();
    pinMode(PIN, OUTPUT);

    // Set PWM range (= the total number of clock ticks during a period)
    softPwmCreate(PIN, 0, PWM_RANGE);

    while(1) 
    {     
        printf("Enter the position of motor (in degree): ");
        scanf("%d", &inputValue);
        
        moveMotor(inputValue);
        
        delay(600);
    }

    return 0;
}
