#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>

int main(){
    char *s="Plus[Times[Sin[13.4],3],2]";
    int ct=0;
    int *pos;
    *pos=15;
    while(('0'<=s[(*pos)+ct]&&s[(*pos)+ct]<='9')||s[(*pos)+ct]=='.'){
        ct++;
    }
    ct--;
    printf("%d\n",ct);
    char cuts[10];
    int i;
    for(i=0;i<=ct;i++){
        cuts[i]=s[(*pos)+i];
    }
    printf("%f\n",atof(cuts));



}