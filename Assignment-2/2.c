#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "students.dat"

//defining student structure
typedef struct {
    int roll;
    char name[100];
    int marks[5];
    int deleted; // 0 = active, 1 = logically deleted
} Student;

//declaring all the functions for free access
void addRecord();
void display();
void searchRecord();
void edit();
void logicalDelete();
void physicalDelete();
bool isRollUnique(int roll);

void addRecord() {
    Student s;
    //opening file in append and binary mode
    FILE *fp = fopen(FILENAME, "ab+");
    if(!fp){
      printf("Error opening file!\n");
      return;
    }

    //input
    printf("Enter roll number: ");
    scanf("%d",&s.roll);

    //checking for unique roll number
    if(!isRollUnique(s.roll)){
      printf("Roll number already exists!\n");
      fclose(fp);
      return;
    }

    //input  name and marks
    printf("Enter name: ");
    getchar(); //clear buffer
    fgets(s.name,100,stdin);


    printf("Enter marks in 5 subjects:\n");
    for (int i=0;i<5;i++) {
        scanf("%d", &s.marks[i]);
    }

    //setting variable active
    s.deleted = 0;


    fwrite(&s,sizeof(Student),1,fp);
    printf("Record added\n");

    fclose(fp);
}

void display() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (!s.deleted) {
            int total = 0;
            for (int i = 0; i < 5; i++) {
                total += s.marks[i];
            }
            printf("Name: %s", s.name);
            printf("Roll: %d\n", s.roll);
            printf("Total: %d\n\n", total);
        }
    }

    fclose(fp);
}

void searchRecord() {
    int roll,flag = 0;


    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("Records dont exist!\n");
        return;
    }

    printf("Enter roll to search: ");
    scanf("%d", &roll);

    Student s;
    while(fread(&s, sizeof(Student), 1, fp)){
        if (s.roll==roll && !s.deleted) {
              printf("Record Found!\nRoll: %d\nName: %s\nMarks: ", s.roll, s.name);
           for (int i=0;i<5;i++) printf("%d ",s.marks[i]);
            printf("\n");
            flag=1;
            break;

        }
    }
  

    if (!flag) printf("Record not found!\n");
    fclose(fp);

}
void edit(){

    int roll, flag = 0;
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }


    printf("Enter roll to edit: ");
    
    scanf("%d", &roll);

  Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {

        if (s.roll == roll && !s.deleted) {
              flag = 1;
          printf("Enter new name: ");
          getchar();
           fgets(s.name,100,stdin);
            // s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new marks for all subjects: ");
            for (int i=0;i<5;i++) scanf("%d", &s.marks[i]);
            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);
            printf("Record updated\n");
            break;
        }
    }

    if (!flag) printf("Record not found!\n");
    fclose(fp);
}
void logicalDelete() {

    int roll, flag = 0;
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }


    printf("Enter roll to logically delete: ");
    scanf("%d", &roll);


    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
        if (s.roll==roll && !s.deleted) {
           s.deleted = 1; //our variable to mark deletion
            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);
            printf("Record logically deleted\n");
            flag=1;
            break;
        }
    }

    if(!flag)printf("Record not found\n");
    fclose(fp);
}
void physicalDelete() {

    FILE *fp = fopen(FILENAME, "rb");

    FILE *temp = fopen("temp.dat", "wb");
    if (!fp||!temp) {
        printf("Error \n");
        return;
    }
    //manually only storing elements that are not logically deleted
    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
        if(!s.deleted) fwrite(&s,sizeof(Student),1,temp);
    }


    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);


    printf("Physical deletion completed!\n");
}
bool isRollUnique(int roll){

    FILE *fp = fopen(FILENAME, "rb");
    if (!fp)return 1; // no file means unique

    Student s;
    while (fread(&s,sizeof(Student),1,fp)) {
      if (s.roll==roll &&!s.deleted) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

int main() {
    int choice;

    while (1) {
      //final menu for operations
      printf("\nMenu:\n");
        printf("1.Add Record\n");
        printf("2.Display Records\n");
        printf("3.Search by Roll\n");
        printf("4.Edit\n");
        printf("5.Logical Delete\n");
        printf("6.Physical Delete\n");
        printf("7.Exit\n");
        printf("Enter: ");
        scanf("%d", &choice);
      
        switch (choice) {
            case 1: addRecord(); break;
            case 2: display(); break;
            case 3: searchRecord(); break;
            case 4: edit(); break;
            case 5: logicalDelete(); break;
            case 6: physicalDelete(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");

        }
    }
    return 0;
}







