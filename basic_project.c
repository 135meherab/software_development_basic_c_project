#include <stdio.h>
#include <stdlib.h>

struct Student{
    int id;
    char name[50];
    char department[50];
    int age;
};

void add_student(){
    FILE *file;
    struct Student student;

    file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("unable to open file!\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &student.id);

    while (getchar() != '\n');

    printf("Enter student name: ");
    scanf("%[^\n]s", student.name);

    while (getchar() != '\n');
    printf("Enter student department: ");
    scanf("%[^\n]s", student.department);


    printf("Enter student age: ");
    scanf("%d", &student.age);

    fprintf(file, "%d %s %s %d\n", student.id, student.name, student.department, student.age);
    fclose(file);
    printf("Student added successfully!\n");
}

void display_menu(){
    printf("\n1. Add Student\n2. View all Student\n3. Search Student\n4. Delete Student\n5. Exit\n");
}

void search_student(){
    FILE *file;
    struct Student student;
    int id;

    file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter student ID to search: ");
    scanf("%d", &id);

    while (fscanf(file, "%d %s %s %d", &student.id, student.name, student.department, &student.age)!= EOF) {
        if (student.id == id) {
            printf("Student found:\nID: %d\nName: %s\nDepartment: %s\nAge: %d\n", student.id, student.name, student.department, student.age);
            return;
        }
    }

    printf("Student not found!\n");
    fclose(file);
}

void delete_student(){
    FILE *file, *temp;
    struct Student student;
    int id;

    file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Unable to open file!\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Unable to open temporary file!\n");
        fclose(file);
        return;
    }

    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d %s %s %d", &student.id, student.name, student.department, &student.age)!= EOF) {
        if (student.id!= id) {
            fprintf(temp, "%d %s %s %d\n", student.id, student.name, student.department, student.age);
        }
    }

    fclose(file);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void display_student(){
    FILE *file;
    struct Student student;

    file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    printf("=============================================================\n");
    printf("ID\t\tName\t\t\tDepartment\tAge\n");
    printf("=============================================================\n");

    while (fscanf(file, "%d %s %s %d", &student.id, student.name, student.department, &student.age)!= EOF) {
        printf("%d\t\t%s\t\t\t%s\t\t%d\n", student.id, student.name, student.department, student.age);
    }

    fclose(file);
}
int main(){
    int choice;
    while (1)
    {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if (choice == 1){
            add_student();
        }
        else if(choice == 2){
            display_student();
        }
        else if(choice == 3){
            search_student();
        }
        else if(choice == 4){
            delete_student();
        }
        else{
            printf("Exiting...\n");
            break;
        }

    }
    return 0;   
}