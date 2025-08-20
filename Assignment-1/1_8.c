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

typedef struct {
    int roll;
    char name[100];
    int score;
} Student;

//sorting
void sort(Student *arr, int n, int (*cmp)(Student, Student)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cmp(arr[i], arr[j])) {
                Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// all possibilities 
// Roll ascending
int compareByRollAsc(Student a, Student b) {
    return a.roll - b.roll;
}
// Roll descending
int compareByRollDesc(Student a, Student b) {
    return b.roll - a.roll;
}
// Score ascending
int compareByScoreAsc(Student a, Student b) {
    return a.score - b.score;
}
// Score descending
int compareByScoreDesc(Student a, Student b) {
    return b.score - a.score;
}

// Display
void display(Student *arr,int n) {
    printf("\nStudent Records\n");
    for (int i = 0;i<n;i++) {
        printf("Roll: %d, Name: %s, Score: %d\n",
          arr[i].roll, arr[i].name, arr[i].score);
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    Student *arr=(Student*)malloc(n*sizeof(Student));
    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter roll: ");
        scanf("%d", &arr[i].roll);
        printf("Enter name: ");
        scanf("%s", arr[i].name);
        printf("Enter score: ");
        scanf("%d", &arr[i].score);
    }

    int choice;
    printf("\nSort by:\n1. Roll-Asc\n2. Roll-Desc\n3. Score-Asc\n4.Score-Desc\n");
    scanf("%d", &choice);
    //menu
    switch (choice){
        case 1: sort(arr,n,compareByRollAsc);break;
        case 2: sort(arr,n,compareByRollDesc);break;
        case 3: sort(arr,n,compareByScoreAsc);break;
        case 4: sort(arr,n,compareByScoreDesc);break;
        default:printf("Invalid choice\n");free(arr);return 0;
    }

    display(arr, n);
    //clearing up memory
    free(arr);
    return 0;
}
