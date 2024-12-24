#include <stdio.h>
#include <stdlib.h>

typedef union {
    float f;
    unsigned u;
    struct {
        unsigned mantissa : 23;
        unsigned exponent : 8;
        unsigned sign: 1;
    } raw;
} ufloat;

void breakDown(float input){
    ufloat newFloat;
    newFloat.f=input;
    printf("    %u      ", newFloat.raw.sign);
    int idx=1;
    for(int i=7; i>=0; i--){
        printf("%d",newFloat.raw.exponent>>i&1);
        if(idx%4==0) printf(" ");
        idx++;
        
    }
    idx=1;
    printf("    ");
    for(int i=22; i>=0; i--){
        printf("%d",newFloat.raw.mantissa>>i&1);
        if(idx==3){
            printf(" ");
        }
        else if((idx-3)%4==0){
            printf(" ");
        }
        idx++;
    }
    printf("\n\n");
    printf("Sign: %u\n", newFloat.raw.sign);
    printf("Exponent: ");
    idx=1;
     for(int i=7; i>=0; i--){
        printf("%d",newFloat.raw.exponent>>i&1);
        if(idx%4==0) printf(" ");
        idx++;
        
    }
    printf("\nMantissa: ");
    for(int i=22; i>=0; i--){
        printf("%d",newFloat.raw.mantissa>>i&1);
        if(idx==3){
            printf(" ");
        }
        else if((idx-3)%4==0){
            printf(" ");
        }
        idx++;
    }
}
int main(){
    float inpu;
    printf("Enter a float number: ");
    scanf("%f",&inpu);
    printf("Breakdown of %f: ",inpu);
    breakDown(inpu);
    printf("\n");
}