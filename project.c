#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define PASSING_MARKS 40


typedef struct {
    char name[MAX_NAME_LENGTH];
    int rollNumber;
    float marks;
    int isActive; 
} Student;


Student students[MAX_STUDENTS];
int studentCount = 0;

void displayWelcome();
void displayMenu();
void addStudent();
void displayAllStudents();
void modifyStudent();
void removeStudent();
void searchStudent();
void clearInputBuffer();

int main() {
    char userName[MAX_NAME_LENGTH];
    int choice;
    

    printf("========================================\n");
    printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
    
    printf("Please enter your name: ");
    fgets(userName, MAX_NAME_LENGTH, stdin);
    userName[strcspn(userName, "\n")] = 0;
    
    printf("\nWelcome, %s!\n", userName);
    printf("Let's manage student records efficiently.\n\n");

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                removeStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                printf("\nThank you for using the Student Record System, %s!\n", userName);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please select 1-6.\n\n");
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("\n========================================\n");
    printf("              MAIN MENU\n");
    printf("========================================\n");
    printf("1. Add Student Record\n");
    printf("2. Display All Students\n");
    printf("3. Modify Student Record\n");
    printf("4. Remove Student Record\n");
    printf("5. Search Student\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nDatabase is full! Cannot add more students.\n");
        return;
    }
    
    Student newStudent;
    newStudent.isActive = 1;
    
    printf("\n--- Add New Student ---\n");
    
    
    printf("Enter student name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    
    printf("Enter roll number: ");
    while (scanf("%d", &newStudent.rollNumber) != 1) {
        printf("Invalid input! Enter a valid roll number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNumber == newStudent.rollNumber) {
            printf("\nError: Roll number %d already exists!\n", newStudent.rollNumber);
            return;
        }
    }
    
    
    printf("Enter marks: ");
    while (scanf("%f", &newStudent.marks) != 1 || newStudent.marks < 0 || newStudent.marks > 100) {
        printf("Invalid input! Enter marks between 0 and 100: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    
    students[studentCount] = newStudent;
    studentCount++;
    
    
    printf("\n--- Student Added Successfully! ---\n");
    printf("Name: %s\n", newStudent.name);
    printf("Roll Number: %d\n", newStudent.rollNumber);
    printf("Marks: %.2f\n", newStudent.marks);
    
    if (newStudent.marks >= PASSING_MARKS) {
        printf("Status: congratulations you have passed\n");
    } else {
        printf("Status: better luck next time\n");
    }
}

void displayAllStudents() {
    int activeCount = 0;
    
    printf("\n========================================\n");
    printf("        ALL STUDENT RECORDS\n");
    printf("========================================\n");
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            activeCount++;
        }
    }
    
    if (activeCount == 0) {
        printf("No student records found.\n");
        return;
    }
    
    printf("\n%-20s %-12s %-10s %-10s\n", "Name", "Roll No.", "Marks", "Status");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            printf("%-20s %-12d %-10.2f ", 
                   students[i].name, 
                   students[i].rollNumber, 
                   students[i].marks);
            
            if (students[i].marks >= PASSING_MARKS) {
                printf("congratulations you have passed\n");
            } else {
                printf("better luck next time\n");
            }
        }
    }
    
    printf("\nTotal Active Students: %d\n", activeCount);
}

void modifyStudent() {
    int rollNo, found = 0, index;
    
    printf("\n--- Modify Student Record ---\n");
    printf("Enter roll number of student to modify: ");
    
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNumber == rollNo) {
            found = 1;
            index = i;
            break;
        }
    }
    
    if (!found) {
        printf("\nStudent with roll number %d not found!\n", rollNo);
        return;
    }
    
    printf("\nCurrent Information:\n");
    printf("Name: %s\n", students[index].name);
    printf("Roll Number: %d\n", students[index].rollNumber);
    printf("Marks: %.2f\n", students[index].marks);
    
    printf("\n--- Enter New Information ---\n");
    
    
    printf("Enter new name (or press Enter to keep current): ");
    char tempName[MAX_NAME_LENGTH];
    fgets(tempName, MAX_NAME_LENGTH, stdin);
    tempName[strcspn(tempName, "\n")] = 0;
    if (strlen(tempName) > 0) {
        strcpy(students[index].name, tempName);
    }
    
    
    printf("Enter new marks (or -1 to keep current): ");
    float tempMarks;
    if (scanf("%f", &tempMarks) == 1 && tempMarks >= 0 && tempMarks <= 100) {
        students[index].marks = tempMarks;
    }
    clearInputBuffer();
    
    printf("\n--- Student Record Updated! ---\n");
    printf("Name: %s\n", students[index].name);
    printf("Roll Number: %d\n", students[index].rollNumber);
    printf("Marks: %.2f\n", students[index].marks);
    printf("Status: %s\n", students[index].marks >= PASSING_MARKS ? "PASSED" : "FAILED");
}

void removeStudent() {
    int rollNo, found = 0;
    
    printf("\n--- Remove Student Record ---\n");
    printf("Enter roll number of student to remove: ");
    
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNumber == rollNo) {
            students[i].isActive = 0; 
            found = 1;
            printf("\nStudent '%s' (Roll No: %d) has been removed successfully!\n", 
                   students[i].name, rollNo);
            break;
        }
    }
    
    if (!found) {
        printf("\nStudent with roll number %d not found!\n", rollNo);
    }
}

void searchStudent() {
    int rollNo, found = 0;
    
    printf("\n--- Search Student ---\n");
    printf("Enter roll number to search: ");
    
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive && students[i].rollNumber == rollNo) {
            printf("\n--- Student Found! ---\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Marks: %.2f\n", students[i].marks);
            printf("Status: %s\n", students[i].marks >= PASSING_MARKS ? "congratulations you have passed" : "better luck next time");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\nStudent with roll number %d not found!\n", rollNo);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}