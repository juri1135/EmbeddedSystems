#include <stdio.h>
#include <stdlib.h>

int computeGCD(int x, int y){
    int max=x>y?x:y;
    int min=x<y?x:y;
    int remain=2;
    while(min!=0){
        remain=max%min;
        max=min;
        min=remain;
    }
    return max;
}
long computeLCM(int x, int y){
    return (long)(x*y)/computeGCD(x,y);
}
int first,second,result,savefirst,savesecond;
long max=1;
int main(){
    int i,m,b,a,c,k;
    
    for(i=1; i<=6; i++){
        for(m=1; m<=6; m++){
            if(i==m) continue;
            for(b=1; b<=6; b++){
                if(i==b||m==b) continue;
                for(a=1; a<=6; a++){
                    if(i==a||m==a||b==a) continue;
                    for(c=1; c<=6; c++){
                        if(i==c||m==c||b==c||b==c||a==c) continue;
                        for(k=1; k<=6; k++){
                            if(i==k||m==k||b==k||a==k||c==k) continue;
                            long lcm=computeLCM(a,k);
                            int edit=1;
                            if(m!=lcm) edit=lcm/m;
                            if((((lcm/a)*b+(lcm/k)*c)==i*edit)&&(m*edit==lcm)){
                                // printf("lcm: %ld, edit: %d, lcm/b: %ld, lcm/c: %ld\n",lcm, edit, lcm/b,lcm/c);
                                printf("%d%d,%d%d%d%d\n",i,m,b,a,c,k);
                                // printf("%f %f %f\n",(double)i/m, (double)b/a, (double)c/k);
                                first=i*10+m;
                                second=b*1000+a*100+c*10+k;
                                if(max<computeLCM(first,second)){
                                    max=computeLCM(first,second);
                                    savefirst=first;
                                    savesecond=second;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("LCM(%d,%d) = %ld\n",savefirst,savesecond,max);
    return 0;
}