#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "students.dat"

struct student {
    char name[30];
    int roll;
    char dept[30];
};

struct student s[MAX];
int count = 0;

void loadFromFile();
void saveToFile();
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();


int main() {
    int choice;

    loadFromFile();  

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search by Roll Number\n");
        printf("4. Update Student Details\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                saveToFile();  
                printf("Data saved. Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        return; 
    }

    fread(&count, sizeof(int), 1, fp);
    fread(s, sizeof(struct student), count, fp);
    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(s, sizeof(struct student), count, fp);
    fclose(fp);
}

void addStudent() {
    if (count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

    printf("\nEnter Name: ");
    fgets(s[count].name, sizeof(s[count].name), stdin);
    s[count].name[strcspn(s[count].name, "\n")] = 0;

    printf("Enter Roll No: ");
    scanf("%d", &s[count].roll);
    getchar();

    printf("Enter Department: ");
    fgets(s[count].dept, sizeof(s[count].dept), stdin);
    s[count].dept[strcspn(s[count].dept, "\n")] = 0;

    count++;
    saveToFile();
    printf("Student added & saved successfully!\n");
}

void viewStudents() {
    if (count == 0) {
        printf("No student records available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Name       : %s\n", s[i].name);
        printf("Roll No    : %d\n", s[i].roll);
        printf("Department : %s\n", s[i].dept);
    }
}

void searchStudent() {
    int roll, found = 0;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name       : %s\n", s[i].name);
            printf("Roll No    : %d\n", s[i].roll);
            printf("Department : %s\n", s[i].dept);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

void updateStudent() {
    int roll, found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);
    getchar();

    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            printf("Enter New Name: ");
            fgets(s[i].name, sizeof(s[i].name), stdin);
            s[i].name[strcspn(s[i].name, "\n")] = 0;

            printf("Enter New Department: ");
            fgets(s[i].dept, sizeof(s[i].dept), stdin);
            s[i].dept[strcspn(s[i].dept, "\n")] = 0;

            saveToFile();
            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

void deleteStudent() {
    int roll, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            for (int j = i; j < count - 1; j++) {
                s[j] = s[j + 1];
            }
            count--;
            saveToFile();
            printf("Student record deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}
