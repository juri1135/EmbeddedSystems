#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

//#include "lcd.h"

#define Trig    23
#define Echo    24

#define LED 17

float measureDistance(void) 
{   struct timeval tv1;
    struct timeval tv2;
    long time1;
    long time2;
    // 초음파 펄스 발신 
    digitalWrite(Trig,1);
    while(digitalRead(Echo)==0){
        gettimeofday(&tv1, NULL);
        time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
    }
    while(digitalRead(Echo)==1){
        gettimeofday(&tv2, NULL);
        time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;
    }
    return time2-time1;
    // echo가 high가 될 때까지 대기 (펄스가 완전히 전송될 때까지 시간 차이 존재)
    // 시각 측정
    // echo가 low가 될 때까지 대기 (반향되는 펄스를 수신할 때까지 시간 차이 존재)
    // 시각 측정
    // 시간 차이로부터 거리 계산
}

int main(void) 
{	
    float distance;

    struct timeval tv1;
    struct timeval tv2;
    long time1;
    long time2;
    wiringPiSetupGpio();
    
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
    pinMode(LED, OUTPUT);

    while(1) 
    {   
        distance = measureDistance();
        printf("%0.2f cm\n", distance);
        
        if (distance < 10.0)
            digitalWrite(LED, 1);
        else
            digitalWrite(LED, 0);
        
        delay(1000);
    }	
    
    return 0;
}