/*
Store name and age of number of number of persons
Sampad De
BCSE-II
002410501025
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char name[100];
    int age;
}Person;
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

void display(Person *arr,int n){
printf("\nAfter sorting:\n");
for (int i=0;i<n;i++){
printf("%s - %d\n",arr[i].name,arr[i].age);
}
}

int main() {
int n;
printf("Enter number of persons: ");
scanf("%d",&n);
Person *arr = (Person*)malloc(n*sizeof(Person));
char str[100];
for (int i = 0; i < n; i++) {
printf("Enter name: ");
scanf("%s",&arr[i].name);
// strcpy(arr[i].name,str);
printf("Enter age: ");
scanf("%d",&arr[i].age);
}
sort(arr,n);
display(arr,n);
//clearing up memory
free(arr);
return 0;
}