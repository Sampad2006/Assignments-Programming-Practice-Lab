/*
Implement the programs in Q3 by breaking it into functions for i) getting the dimensions from user,
ii) dynamic memory allocation, iii) accepting the values and iv) printing the values.

Sampad De
002410501025
*/
#include <stdio.h>
#include <stdlib.h>

//taking input for dimensions
void get_dimensions(int *rows, int *cols) {
    printf("Enter rows and columns: ");
    scanf("%d %d",rows,cols);
}

//taking input for elements
void input(int rows,int cols,int **arr) {
    printf("Enter elements:\n");
    for (int i=0;i<rows;i++) {
        for (int j = 0;j<cols;j++) {
             scanf("%d",&arr[i][j]);
        }
    }
}
//displaying all elements
void display(int rows,int cols,int **arr) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}
//freeing up allocated memory
void free_matrix(int rows,int **arr) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

// For pointer-to-array type
void input_2(int rows,int cols,int (*arr)[cols]) {
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}


void display_2(int rows,int cols,int (*arr)[cols]) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}



// Array of pointers
void solve1() {
    int rows, cols;
    get_dimensions(&rows, &cols);
    //allocating memory
    int *arr[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(int));
    }
    //calling input and display functions
    input(rows, cols, arr);
    display(rows, cols, arr);

    for (int i = 0; i < rows; i++) free(arr[i]);
}

// Pointer to pointer, two malloc
void solve2_1() {
    int rows, cols;
    get_dimensions(&rows, &cols);

    int **arr = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(int));
    }

    input(rows, cols, arr);
    display(rows, cols, arr);
    free_matrix(rows, arr);
}

// Pointer to pointer, one malloc
void solve2_2() {
    int rows, cols;
    get_dimensions(&rows, &cols);
    //using first row to store pointers to other rows
    int **arr = malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    int *data = (int *)(arr + rows);

    for (int i = 0; i < rows; i++) {
        arr[i] = data + i * cols;
    }

    input(rows, cols, arr);
    display(rows, cols, arr);
    free(arr);
}

//  Pointer to an array
void solve3() {
    int rows, cols;
    get_dimensions(&rows, &cols);

    int (*arr)[cols] = malloc(rows * sizeof(*arr));
    if (!arr) {
        printf("Memory allocation process unsuccessful\n");
        return;
    }

    input_2(rows, cols, arr);
    display_2(rows, cols, arr);
    free(arr);
}


int main() {
  
    int t;
    while(1){
        printf("Enter 1 for part 1 \n2 for parts 2\n3 for part 3\n 4 to exit");
        scanf("%d", &t);
    if (t == 1) solve1();
    else if (t == 2) {

        printf("Enter 1 for part 1 and 2 for part 2:\n");
        int c;
        scanf("%d", &c);
        if (c == 1) solve2_1();//2.a
        else if (c == 2) solve2_2();//2.b
    }
    else if(t==3) solve3();
    else exit(0);
    }
    
}
