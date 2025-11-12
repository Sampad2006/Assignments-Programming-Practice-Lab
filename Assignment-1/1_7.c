/*
Maintain a list to store roll, name and score of students. As and when required student record may be
added or deleted. Also, the list has to be displayed. Design suitable functions for different operations. 
Sampad De
BCSE-II
002410501025
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure as template for students
typedef struct {
    int roll;
    char name[100];
    int score;
} Student;

Student *students = NULL; 
int cnt = 0;    // Global variable to keep track of size

// Function to add new student
void addStudent(int roll, char *name, int score) {
    students = (Student*) realloc(students, (cnt + 1) * sizeof(Student));// resizing the array with +1 size
    students[cnt].roll = roll;
    strcpy(students[cnt].name, name);
    students[cnt].score = score;
    cnt++; // Increases the size by one
    printf("Added\n");
}

// Deletes student by roll 
void deleteStudent(int roll) {
    int idx = -1;
    for (int i = 0; i < cnt; i++) {
        if (students[i].roll == roll) {
            idx = i;
            break;
        }
    }
    if (idx==-1) {
        printf("Student not found\n");return; // If not found
    }
    // shifting all elements after deleted element to the left 
    for (int i = idx;i<cnt-1;i++) {
        students[i] = students[i + 1];
    }
    cnt--; // decreasing global size counter by one
    students = (Student*) realloc(students, cnt * sizeof(Student));
    printf("Student deleted\n");
}

// display all records
void display() {
    printf("Student Records\n");
    for (int i = 0; i < cnt; i++) {
        printf("Roll: %d, Name: %s, Score: %d\n",students[i].roll, students[i].name, students[i].score);
    }
}

void solve() {
    int choice, roll, score;
    char name[100];


    while (1) {
        printf("\n1. Add new student \n");
        printf("2.  Display records  \n");
        printf("3. Delete \n");
        printf("4. Exit \n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                //input
                printf("Enter roll: ");
                scanf("%d",&roll);
                printf("Enter name: ");
                scanf(" %[^\n]",name);
                printf("Enter score: ");
                scanf("%d", &score);

                //Adding data to the list
                addStudent(roll, name, score);
                break;
            case 2:
                 //printing
                display();
                break;
            case 3:
                printf("Delete student with roll : ");
                scanf("%d", &roll);
                deleteStudent(roll);
                break;
            case 4:
                free(students); // freeing up memory 
                return ;
            default:
                printf("Invalid choice!\n");
        }
    }
}
int main() {
  solve();
}