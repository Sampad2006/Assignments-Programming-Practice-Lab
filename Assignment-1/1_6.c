/*
Store name and age of number of number of persons
*/
//Sampad De
//002410501025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Student {
    char name[100];
    int age;
    
};
void sort(struct Student *arr, int n) {
    for (int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) {
    if (arr[i].age>arr[j].age) {
    // Swap ages
    int tempAge = arr[i].age;
    arr[i].age = arr[j].age;
    arr[j].age = tempAge;
    // Swap names
    char *tempName = arr[i].name;
    arr[i].name = arr[j].name;
    arr[j].name = tempName;
    }
    }
    }
}

void display(char**names,int *ages,int n){
printf("\nAfter sorting:\n");
for (int i=0;i<n;i++){
printf("%s - %d\n",names[i],ages[i]);
}
}

int main() {
int n;
printf("Enter number of persons: ");
scanf("%d",&n);
int *ages = (int*)malloc(n*sizeof(int));
char **names = (char**)malloc(n*sizeof(char*));
char str[100];
for (int i = 0; i < n; i++) {
printf("Enter name: ");
scanf("%s",str);
names[i] = malloc(strlen(str)+1);
strcpy(names[i],str);
printf("Enter age: ");
scanf("%d",&ages[i]);
}
sort(names,ages,n);
display(names,ages,n);
//clearing up memory
for (int i=0;i<n;i++) free(names[i]);
free(names);
free(ages);
return 0;
}