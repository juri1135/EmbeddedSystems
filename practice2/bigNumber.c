#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char num[513];
} BigNum;
void convertStringToBigNumber(char string[], BigNum* bigNumber){
    int i=0;
    for(i=0; i<strlen(string);i++){
        bigNumber->num[i]=string[i];
    }
    bigNumber->num[i]='\0';
}
void printBigNumber(BigNum *bigNumber){
    // for(int i=0; i<strlen(bigNumber->num);i++){
    //     printf("%c",bigNumber->num[i]);
    // }
    printf("%s",bigNumber->num);
}
void addPositiveBigNumber(BigNum *first, BigNum *second, BigNum *result){
    int idx1=strlen(first->num);
    int idx2=strlen(second->num);
    for(int i=0; i<idx1/2; i++){
        char temp=first->num[i];
        first->num[i]=first->num[idx1-1-i];
        first->num[idx1-1-i]=temp;
    }
    
    for(int i=0; i<idx2/2; i++){
        char temp=second->num[i];
        second->num[i]=second->num[idx2-1-i];
        second->num[idx2-1-i]=temp;
    }
    
    int max=idx1>idx2?idx1:idx2;
    int carry=0;
    int i=0;
    for(i=0; i<max; i++){
        int f = (i < idx1) ? first->num[i] - '0' : 0; 
        int s = (i < idx2) ? second->num[i] - '0' : 0;
        
        int sum=f+s+carry; //(i-1)th carry
        // printf("carry: %d, sum: %d\n",carry,sum);
        if(sum>=10){
            carry=sum%10;
            if(sum==10) carry=1;
        }
        else{
            carry=0;
        }
        result->num[i]=(sum%10)+'0';

    }
    if(carry>0){
        result->num[i]=carry;
        i++;
    }
    // printf("%s\n",result->num);
    // result->num[i] = '\0';
    for(int i=0; i<max/2; i++){
        char temp=result->num[i];
        result->num[i]=result->num[idx1-i];
        result->num[idx1-i]=temp;
    }
}
int main(){
    BigNum first;
    BigNum second;
    BigNum result = {{0}};
    char firstinpu[513];
    char secondinpu[513];
    printf("Enter the first big integer = ");
    scanf("%s",firstinpu);
    convertStringToBigNumber(firstinpu,&first);

    printf("Enter the second big integer = ");
    scanf("%s",secondinpu);
    convertStringToBigNumber(secondinpu,&second);
    
    printBigNumber(&first); printf(" + "); printBigNumber(&second); printf(" = ");    
    addPositiveBigNumber(&first,&second,&result);
    printBigNumber(&result);
    printf("\n");
}