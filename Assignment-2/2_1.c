/*
Write a program to store student information in a file and to do the following operations.
 Information includes roll, name, and score in five subjects. Use may like to add record 
 (check if roll number is unique), display all records showing roll, name and total score. 
 User may search for the record against a roll.
User may edit the details in a record.User may delete record.
Deletion may be logical (by some means indicate it is an invalid record and to be avoided in processing) 
and physical(file will not have the record ).


Name-Sampad De
Roll-002410501025
Class-BCSE-2

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

//defining student structure as template
typedef struct {
    int roll;
    char name[100];
    int marks[5];
    int deleted; // 0 = active, 1 = logically deleted
} Student;

//declaring all the functions for free access throughout
void addRecord();
void display();
void searchRecord();
void edit();
void logicalDelete();
void physicalDelete();
bool isRollUnique(int roll);

void addRecord() {
    Student s;
    //opening file in append binary mode
    FILE *fp =fopen(FILENAME,"ab+");
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

    //Input name and marks
    printf("Enter name: ");
    getchar(); //clear buffer
    fgets(s.name,100,stdin);
    // printf("\n");

    //Input marks
    printf("Enter marks in 5 subjects:\n");
    for (int i=0;i<5;i++) {
        scanf("%d", &s.marks[i]);
    }

    //Setting variable active
    s.deleted = 0;

    //Addition
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
    //Print all info
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        
            int total = 0;
            for (int i = 0; i < 5; i++) {
                total += s.marks[i];
            }
            printf("Name: %s", s.name);
            printf("Roll: %d\n", s.roll);
            printf("Marks: \n");
            for(int i = 0; i < 5; i++){
                printf("%d\n",s.marks[i]);
            }
            printf("Total: %d\n\n", total);
        
    }

    fclose(fp);
}

void searchRecord(){

    int roll,flag = 0;//Flag stores whether 


    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {//If file is empty ,no records
        printf("Records dont exist!\n");
        return;
    }
    //roll
    printf("Enter roll to search: ");
    scanf("%d", &roll);

    Student s;
    while(fread(&s,sizeof(Student),1,fp)){
        if(s.roll==roll && !s.deleted) { //Searching by roll
              printf("Record Found!\nRoll: %d\nName: %s\nMarks: ", s.roll, s.name);
           for(int i=0;i<5;i++)printf("%d ",s.marks[i]);
            printf("\n");
            flag=1;
            break;

        }
    }
  
    //If records dont exist
    if (!flag) printf("Record not found!\n");
    fclose(fp);

}
//Editing records
void edit(){

    int roll, flag = 0;//Flag to check 
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) { //flag 
        printf("No records found!\n");
        return;
    }

    // Enter roll
    printf("Enter roll to edit: ");
    scanf("%d", &roll);

  Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll && !s.deleted) {
              flag = 1;
          printf("Enter new name: ");
          getchar();
           fgets(s.name,100,stdin);
            printf("Enter new marks for all subjects: ");
            for (int i=0;i<5;i++) scanf("%d", &s.marks[i]);

             fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);

         printf("Record updated\n");
            break;
        }
    }

    if(!flag)printf("Record not found!\n");
    fclose(fp);
}
//No actual deletion just marking
void logicalDelete() {
    //flag to mark deletion
    int roll, flag = 0;
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    //input
    printf("Enter roll to logically delete: ");
    scanf("%d", &roll);
    if(!isRollUnique){
        printf("Roll doesnt exist");
        return ;
    }

    Student s;
    while(fread(&s,sizeof(Student),1,fp)){
        if(s.roll==roll && !s.deleted){
           s.deleted = 1; // variable to mark deletion 
             fseek(fp,-sizeof(Student),SEEK_CUR);
            fwrite(&s,sizeof(Student),1,fp);
         printf("Record logically deleted\n");
            flag=1;
                break;
        }
    }

     if(!flag)printf("Record not found\n");
    fclose(fp);
}
//actually deleting records
void physicalDelete(){
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

    FILE *fp =fopen(FILENAME, "rb");
    if (!fp)return 1; // no file means unique

    //if it exists, not unique
    Student s;
     while (fread(&s,sizeof(Student),1,fp)) {
      if(s.roll==roll &&!s.deleted) {
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
        printf("1.Add Record \n");
        printf("2.Display Records\n");
        printf("3.Search by Roll\n");
        printf("4.Edit\n");
        printf("5.Logical Deletion\n");
        printf("6.Physical Deletion\n");
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