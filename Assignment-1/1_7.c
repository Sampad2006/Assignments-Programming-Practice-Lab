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

// Structure as a template
typedef struct {
    int roll;
    char name[100];
    int score;
} Student;

Student *students = NULL;  
int count = 0;    // variable to track size

// Function to add student
void addStudent(int roll, const char *name, int score) {
    students = (Student*) realloc(students, (count + 1) * sizeof(Student));// resize array by +1
    

    students[count].roll = roll;
    strcpy(students[count].name, name);
    students[count].score = score;
    count++;//incrementing count

    printf("Added\n");
}

// Function to delete via roll
void deleteStudent(int roll) {
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student not found\n");
        return;
    }

    // shift elements left
    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;//decrementing
    students = (Student*) realloc(students, count * sizeof(Student)); //new size
    printf("Student deleted\n");
}

// Function to display all students
void displayStudents() {
    printf("Student Records\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %d, Name: %s, Score: %d\n",students[i].roll, students[i].name, students[i].score);
    }
}

void solve() {
    int choice, roll, score;
    char name[100];

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Display Students\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll: ");
                scanf("%d", &roll);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter score: ");
                scanf("%d", &score);
                addStudent(roll, name, score);
                break;
            case 2:
                printf("Enter roll to delete: ");
                scanf("%d", &roll);
                deleteStudent(roll);
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                free(students); // cleanup
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
int main() {
  int t;
  // scanf("%d", &t);
  t==1;
  while(t--) solve();
    return 0;
}