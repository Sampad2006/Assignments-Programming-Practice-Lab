/*
Implement a one dimensional array of integers where array size of the array will be provided during runtime.Accept the value for the elements and print those using pointers.

Sampad De
002410501025
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void solve(){
   int rows, cols;
    printf("Enter n");
    int n;
    scanf("%d %d", &n);
    int *arr; 
    //single dimensional array
    arr= (int *)malloc(cols * sizeof(int));
   
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    scanf("%d", &arr[i]);
    }
}
for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
}

//clearing up memory
    free(arr);
}

int main(){
    int t;
    // scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}