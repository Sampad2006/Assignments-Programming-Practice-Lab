/*
Consider an array that stores roll, name, and score of number of students. Develop a function to sort the
array. User of sort() will develop the comparison function for sorting on roll/score and ascending or
descending order and reuse the same sort() function. 

Sampad De
BCSE-II
002410501025
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//structure as template
typedef struct {
    int roll;
    char name[100];
    int score;
} Student;


//custom comparator
void sort(Student *arr, int n, bool (*cmp)(Student, Student)) {
    // Selection sort
    for (int i=0;i<n-1;i++){
        for (int j = i+1;j<n;j++) {
            if (cmp(arr[i], arr[j])) {
                Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
}

//All possibilities

// Roll ascending
bool RollAsc(Student a, Student b) {
    return a.roll>b.roll;
}
// Roll descending
bool RollDsc(Student a, Student b) {
    return b.roll>a.roll;
}
// Score ascending
bool ScoreAsc(Student a, Student b) {
    return a.score>b.score;
}
// Score descending
bool ScoreDcs(Student a, Student b) {
    return b.score>a.score;
}

// displays all the students
void display(Student *arr,int n) {
    printf("\nRecord of students\n");
    for (int i = 0;i<n;i++) {
        printf("Roll: %d, Name: %s, Score: %d\n",arr[i].roll,arr[i].name,arr[i].score);
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    Student *arr=(Student*)malloc(n*sizeof(Student)); // Allocating memory
    //Input
    for (int i=0;i<n;i++) {
    printf("Enter roll: ");
    scanf("%d", &arr[i].roll);
    printf("Enter name: ");
    scanf(" %[^\n]",&arr[i].name);
    printf("Enter score: ");
    scanf("%d", &arr[i].score);
    }
    while(1){
    int choice;
    printf("\nSort by:\n1. Ascending-Roll\n2. Descending-Roll\n3. Ascending-Score\n4. Descending-Score\n5. To exit\n");
    scanf("%d", &choice);

    switch (choice){
        case 1: sort(arr,n,RollAsc);break;
        case 2: sort(arr,n,RollDsc);break;
        case 3: sort(arr,n,ScoreAsc);break;
        case 4: sort(arr,n,ScoreDcs);break;
        case 5: exit(1);
        default:printf("Invalid choice\n");free(arr);return 0;
    }
    display(arr, n);
    }
    //clearing the memory
    free(arr);
    return 0;
}