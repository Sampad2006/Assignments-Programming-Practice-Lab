/*
Implement Q.5 using structure.
Sampad De
BCSE-II
002410501025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct as template
typedef struct{
    char name[100];
    int age;
}Person;
//insertion sort
void sort(Person *arr, int n) { 
    for (int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) {
    if (arr[i].age>arr[j].age) {
    Person temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    }
    }
    }
}
//printing list
void display(Person *arr,int n){
printf("\nAfter sorting:\n");
for (int i=0;i<n;i++){
printf("%s - %d\n",arr[i].name,arr[i].age);
}
}
int main() {
 int n;
 printf("Enter number of persons: "); // input n
 scanf("%d",&n);
 Person *arr = (Person*)malloc(n*sizeof(Person)); // memory allocation
 //input
 for (int i = 0; i < n; i++) {
 printf("Enter name: ");
 scanf(" %[^\n]",(arr[i].name)); 
 printf("Enter age: ");
 scanf("%d",&arr[i].age);
 }
 sort(arr,n); // sorting
 display(arr,n); // displaying
 free(arr); // freeing up memory
 return 0;
}
