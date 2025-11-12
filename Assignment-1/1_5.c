/*
Store name and age of number of persons (number provided at run time). Collect the data and display
data in the ascending order of age. Implement without using structure. Write functions for memory
allocation of the list, sorting and display of data.
Sampad De
002410501025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char **names,int *ages,int n) { 
    //insertion sort
 for (int i = 0; i < n-1; i++) {
 for (int j = i+1; j < n; j++) {
 if (ages[i]>ages[j]) {
 // Swap ages
 int tempAge = ages[i];
 ages[i] = ages[j];
 ages[j] = tempAge;
 // Swap names
 char *tempName = names[i];
 names[i] = names[j];
 names[j] = tempName;
 }
 }
 }
}

//Function to display list
void print(char **names,int *ages,int n){
 printf("The final list after sorting is :\n");
 for(int i=0;i<n;i++){
 printf("%s - %d\n",names[i],ages[i]);
 }
}
int main() {
 int n;
 //input
 printf("Enter number of persons: ");
 scanf("%d", &n); 
 //Allocating memory
 int *ages = (int*)malloc(n*sizeof(int)); 
 char **names = (char**)malloc(n*sizeof(char *)); 
 char str[100];
 for (int i = 0; i < n; i++) {
 printf("Enter name: ");
 //input name
 scanf(" %[^\n]", str); 
 names[i] = (char*)malloc((strlen(str)+1)*sizeof(char));
 strcpy(names[i], str); //copying string
 printf("Enter age: ");
 scanf("%d", &ages[i]); // input age
 }
 sort(names, ages, n); // sorting by ages
 print(names, ages, n); // prints the final result
 for (int i=0;i<n;i++) free(names[i]);
 free(names);
 free(ages);
 return 0;
}
   