/*
Store name and age of number of number of persons.Collect the data and display data in the ascending order of age.
Implement without using structure.Write functions for memory allocation of the list,sorting and display of data.

Sampad De
002410501025
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//insertion sort
void sort(char **names, int *ages, int n) {
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

void display(char**names,int *ages,int n){
printf("\nAfter sorting:\n");
for (int i=0;i<n;i++){
printf("%s - %d\n",names[i],ages[i]);
}
}

void solve() {
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
//sorting simultaneously ages and corresponding names
sort(names,ages,n);
display(names,ages,n);
//clearing up memory
for (int i=0;i<n;i++) free(names[i]);
free(names);
free(ages);
}

int main(){
    solve();

}   