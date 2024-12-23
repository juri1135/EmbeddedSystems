#include <stdio.h>
#include <stdlib.h>
#define n 100

int recursionData[n+1];
int loopData[n+1], loopNum[n+1];
int recursion=0;
long int fibonacci(int number){
    // all fibos divide fibo(0) and fibo(1). => recursion++ when call fibo(0) or fibo(1)
    if(number==0){
        recursionData[number]=0;
        recursion++;
    }
    else if(number==1){
        recursionData[number]=1;
        recursion++;
    }
    else{
        recursionData[number]=fibonacci(number-1)+fibonacci(number-2);
    }
    
     return recursionData[number];
}
int main(){
    printf("Enter a number up which Fibonacci series are computed: ");
    int num;
    scanf("%d",&num);
    
    int i=0;
    while(i!=num+1){
        if(i==0){
            loopData[i]=0;
        }
        else if(i==1){
            loopData[i]=1;
        }
        else{
            loopData[i]=loopData[i-1]+loopData[i-2];
        }
        loopNum[i]++;
        i++;
    }
    
    printf("Fibonacci series computed by recursion.\n");
    printf(" Fib        Value       # of Calls\n");
    for(int i=0; i<=num; i++){
        recursion=0;
        int value=fibonacci(i);
        printf("Fib(%d)         %d              %d\n",i,value,recursion);
    }
    printf("Fibonacci series computed by loop,\n");
    printf(" Fib        Value       # of Calls\n");
    for(int i=0; i<=num; i++){
        printf("Fib(%d)         %d              %d\n",i,loopData[i],loopNum[i]);
    }
    return 0;
}