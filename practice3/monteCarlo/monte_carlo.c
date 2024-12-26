#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "rand_between.h"

#define NUM_MAX 100000
int count[4] = {0, 0, 0, 0};

void* simulateMonteCarlo(void* quadrant){   
    float x[NUM_MAX], y[NUM_MAX];
    int quad=*(int*) quadrant;
    //make random x and y
    generateRandBetween(-1,1,NUM_MAX,x);
    generateRandBetween(-1,1,NUM_MAX,y);
    for(int i=0; i<NUM_MAX; i++){
        if(((x[i]*x[i])+(y[i]*y[i]))<=1) count[quad-1]++;
    }
    pthread_exit(NULL);
}

int main(void)
{   
    int i;
    pthread_t threads[4];
    int quadrantNumer[4] = {1, 2, 3, 4};
    int sum = 0;
    double pi;
    int threadReturn;

    //thread 생성
    for(i = 0; i < 4; i++)
    {   //new thread's ID, stack size...etc, function thread runs, argument of function
        //thread n counts quad n
        pthread_create(&threads[i], NULL, simulateMonteCarlo, &quadrantNumer[i]);
    }
    //worker thread가 work 이후에 exit하면 master에서 합쳐... 
    for (i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
    //count: in circle
    sum = count[0] + count[1] + count[2] + count[3];
    pi = (double) sum / (NUM_MAX);

    printf("Counts: %d %d %d %d\n", count[0], count[1], count[2], count[3]);
    printf("Sum of counts: %d\n", sum);
    printf("The value of PI is %f\n", pi);

    return 0;
}