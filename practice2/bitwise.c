#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char binaryList[100]="";
int getNthBitFromLSB(int number,int nthBit){
    return binaryList[strlen(binaryList)-1-nthBit]=='0'?0:1;
}
void setNthBitFromLSB(int* number, int nthBit){
    binaryList[strlen(binaryList)-1-nthBit]='1';
    int chg=0;
    int idx=1;
    if(binaryList[strlen(binaryList)-1]=='1') chg=1;
    for(int i=strlen(binaryList)-2;  i>=0; i--){
        if(binaryList[i]=='1') chg+=idx*2;
        idx*=2;
    }
    *number=chg;
}
void clearNthBitFromLSB(int* number, int nthBit){
    binaryList[strlen(binaryList)-1-nthBit]='0';
    int chg=0;
    int idx=1;
    if(binaryList[strlen(binaryList)-1]=='1') chg=1;
    for(int i=strlen(binaryList)-2;  i>=0; i--){
        if(binaryList[i]=='1') chg+=idx*2;
        idx*=2;
    }
    *number=chg;
}
int countOne(int number){
    int count=0;
    for(int i=0; i<strlen(binaryList); i++){
        if(binaryList[i]=='1') count++;
    }
    return count;
}
void printBinary(int number, int nbitsToPrint){
    printf("%d (in decimal)         ",number);
    int idx=0;
    for(int i=nbitsToPrint-1; i>=0; i--){
        int num=(number>>i)&1;
        binaryList[idx]=num==0?'0':'1';
        printf("%d",num);
        if((idx+1)%4==0) printf(" ");
        idx++;
    }
    printf("    (in binary)\n");
}
int main(){
    int val,save;
    printf("Enter an int number: ");
    scanf("%d",&val);
    save=val;
    printBinary(val,32);
    printf("The number of '1's is %d\n\n",countOne(val));
    int nth;
    printf("Enter a bit position to experiment with (from LSB): ");
    scanf("%d",&nth);
    setNthBitFromLSB(&val,nth);
    printf("After setting %dth bit:     ",nth);
    printBinary(save,32);
    printf("The %dth bit is %d\n",nth,getNthBitFromLSB(save,nth));
    clearNthBitFromLSB(&val,nth);
    printf("After clearing %dth bit:    ",nth);
    printBinary(val,32);
    printf("The %dth bit is %d\n",nth,getNthBitFromLSB(val,nth));
    return 0;
}