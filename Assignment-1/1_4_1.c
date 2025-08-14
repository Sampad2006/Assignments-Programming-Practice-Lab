/*
Implement the programs in Q2 (and Q3 in next part) by breaking it into functions for i)dimensions from user, ii)dynamic memory

Sampad De
002410501025
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// taking in dimensions
int dimension(){
printf("Enter the dimension of the array : ");
int n;
scanf("%d",&n);
return n;
}

// allocating memory for the array
int *array(int n){
int  *temp = (int*)malloc(sizeof(int)*n);
return temp;
}

//input 
void collector(int *arr,int n){
printf("Enter the array : \n");
for(int i=0;i<n;i++){
int temp;
scanf("%d",&temp);
arr[i] = temp;
}
}

//display
void print(int *arr,int n){
printf("The array is \n");
for(int i=0;i<n;i++){
printf("%d ",arr[i]);
}
printf("\n");
}

void solve(){
int n = dimension();
int *arr = array(n);
collector(arr,n);
print(arr,n);
}


int main(){
    int t;
    // scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}


