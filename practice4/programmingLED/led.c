#include <wiringPi.h>
#include <stdio.h>
int main(){
    //wiringPi initialization
    wiringPiSetupGpio();
    pinMode(17,1);
    while (1)
    {   
        digitalWrite(17,1);
        delay(1000);
        digitalWrite(17,0);
        delay(1000);
    }
    return 0;
    
}