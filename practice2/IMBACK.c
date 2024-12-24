#include <stdio.h>
#include <stdlib.h>

int computeGCD(int x, int y){
    int max=x>y?x:y;
    int min=x<y?x:y;
    while(min!=0){
        int remain=max%min;
        max=min;
        min=remain;
        remain=max%min;
    }
    return remain;
}
long computeLCM(int x, int y){
    return (x*y)/computeGCD(x,y);
}
int main(){
    int I,m,b,a,c,k;
    for(int i=1; i<=6; i++){
        I=i, m=i, b=i, a=i, c=i, k=i;
        
    }
    return 0;
}