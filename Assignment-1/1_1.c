/*
Write a program that will have an integer variable and a pointer pointing to it.Also have a
pointer to pointer pointing to p.Take the value for the integer variable and print it using p,and pp.

Sampad De
002410501025
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void solve(){
int var;
printf("Enter an integer variable: ");
scanf("%d",&var);

int *p=&var;//pointer to the variable
int **pp=&p;//pointer to pointer
printf("Printing via pointer  then via pointer to pointer %d\n%d",*p,**pp);
}

int main(){
    int t;
    // scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}