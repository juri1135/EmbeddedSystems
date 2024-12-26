#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "rand_between.h"

void generateRandBetween(float a, float b, int number, float result[]){
    srand(123400);
    //rand()%3=> 0~2 (3으로 나눈 나머지니까...)
    //rand()%3+1 => 1~3 
    //rand()%(b+1) => 0~b
    //rand()%(b-a+1) =>0~b-a
    //rand()%(b-a+1)+a => a~b
    for(int i=0; i<number; i++){
        result[i]=((float)rand()/RAND_MAX)*(b-a)+a;
    }
}