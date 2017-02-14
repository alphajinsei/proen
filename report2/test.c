#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>

int main(){
<<<<<<< HEAD
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
=======
   
    printf("%f\n",sin(3.14));
    printf("%f\n",sin(1));
<<<<<<< HEAD
>>>>>>> 51af508f67fd02b91433e8c36e680efcbb4416d7

=======
    char s[]="3";
    double x=atof(s);
    printf("%s %f\n",s,x);
>>>>>>> 36123205b6dfdcb4adc547d1640f155cb34d0329


}