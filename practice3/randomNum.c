#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandBetween(float a, float b, int number, float result[]){
    srand(1234);
    //rand()%3=> 0~2 (3으로 나눈 나머지니까...)
    //rand()%3+1 => 1~3 
    //rand()%(b+1)+a => a~b+a
    //rand()%(b-a+1) =>0~b-a
    //rand()%(b-a+1)+a => a~b
    for(int i=0; i<number; i++){
        result[i]=((float)rand()/RAND_MAX)*(b-a+1)+a;
    }
}
int main(){
    int n;
    float a,b;
    
    printf("Enter a start value of range: ");
    scanf("%f",&a);
    printf("Enter a finish value of range: ");
    scanf("%f",&b);
    printf("Enter the total number of random values to generate: ");
    scanf("%d",&n);
    printf("\nRandom values in [%f, %f]\n",a,b);
    float result[n+1];
    generateRandBetween(a,b,n,result);
    float avg=0;
    for(int i=0; i<n; i++){
        printf("%f, ",result[i]);
        avg+=result[i];
    }
    printf("\nThe average of random values is %f\n",avg/n);
}