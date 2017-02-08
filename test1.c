#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MT.h"
#include <time.h>

#define h 0.1 

double dxdt(double,double);
void euler(double(*f)(double,double),double x0,double t0,double tend);

int main(){
    euler(dxdt,1,0,10);
    return 0;
}

double dxdt(double x,double t){
    return x*(2-x);
}

void euler(double(*f)(double,double),double x0,double t0,double tend){
    printf("%f\t%f\n",t0,x0);
    double x=x0;
    double t=t0;
    while(t<tend){
        printf("%f\t%f\n",t,x);
        x=x+f(x,t)*h;
        t=t+h;
    }

}