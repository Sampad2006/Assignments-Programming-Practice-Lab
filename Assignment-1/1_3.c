/*
Implement a 2 dimensional array of integers using a) array of pointers b)pointer to pointer(with two malloc statements and again with one malloc statement),c)pointer to an array.Accept the value for the elements and print those.

Sampad De
002410501025
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//array of pointers
void solve1(){
   int rows, cols;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    int *arr[rows]; 
    // Allocate each row separately
    for (int i = 0; i < rows; i++) {
    arr[i] = (int *)malloc(cols * sizeof(int));
    }
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    scanf("%d", &arr[i][j]);
    }
    }
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    printf("%d ", arr[i][j]);
    }
    printf("\n");
    }
    // Free memory
    for (int i = 0; i < rows; i++) {free(arr[i]);
    }
    // return 0;
}

//using 2 mallocs
void solve2_1(){
   int rows, cols;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    int **arr; 
    arr=(int**)malloc(rows*sizeof(int*));
    // Allocating each row separately
    for (int i = 0; i < rows; i++) {
    arr[i] = (int *)malloc(cols * sizeof(int));
    }
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    scanf("%d", &arr[i][j]);
    }
    }
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    printf("%d ", arr[i][j]);
    }
    printf("\n");
    }
    // Free memory
    for (int i = 0; i < rows; i++) {free(arr[i]);
    }
    free(arr);
         

}
//using 1 malloc
void solve2_2(){
  int rows, cols;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    int **arr=(int**)malloc(rows*sizeof(int*)+(rows*cols)*(sizeof(int)));
        for(int i=0;i<rows;i++){
            arr[i]=(int*)(arr+rows+(i)*cols);
        }
        
        //Taking input
        printf("Enter elements:\n");
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++)
            scanf("%d",(arr[i]+j));
        }
        //Printing
        printf("Matrix:\n");
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                printf("%d ",*(arr[i]+j));
            }
            printf("\n");
        }
    }



//pointer to an array
void solve3(){
   int rows, cols;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    
    // Pointer to an array with cols fixed
    int (*arr)[cols];

    // Allocating memory
    arr = malloc(rows * sizeof(*arr));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Input
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // Output
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free memory
    free(arr);
}
int main(){
    int t;
    printf("Enter 1 for part 1 \n2 then 1 or 2 for parts1,2\n3 for part 3\n");
    scanf("%d",&t);
    // t=1;
    if(t==1) solve1();
    else if(t==2){
        int c;scanf("%d",&c);
        if(c==1) solve2_1();
        else if(c==2)
         solve2_2();
        }
    else solve3();
}