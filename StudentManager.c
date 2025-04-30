//StudentManager.c - Interface for managing student records

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Initialize.h"
#include "Tree.h"  // Include the Tree.h header

// Function prototypes
void displayMenu();
void addStudent();
void removeStudent();
void editStudentScore();
void sortStudents();
void displayStudents();
void saveToCSV();
int compareByName(const void* a, const void* b);
int compareByID(const void* a, const void* b);
int compareByScore(const void* a, const void* b);
void clearInputBuffer();

int main() {
    int choice;
    
    // load the CSV file
    studentInformation();
    
    printf("Student Management System\n");
    printf("========================\n");
    
    do {
        displayMenu();
        printf("Enter your choice (1-8): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                displayStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                removeStudent();
                break;
            case 4:
                editStudentScore();
                break;
            case 5:
                sortStudents();
                break;
            case 6:
                CreateGroup();  
                break;
            case 7:
                saveToCSV();
                printf("Data saved to CSV file successfully!\n");
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\n");
    } while (choice != 8);
    
    return 0;
}

// main menu
void displayMenu() {
    printf("\nMenu Options:\n");
    printf("1. Display all students\n");
    printf("2. Add a student\n");
    printf("3. Remove a student\n");
    printf("4. Edit student score\n");
    printf("5. Sort students\n");
    printf("6. Create student groups\n");  // *
    printf("7. Save changes to CSV\n");
    printf("8. Exit\n");
}

// Add student 
void addStudent() {
    if (TotalStudents >= 1000) {
        printf("Error: Maximum number of students reached.\n");
        return;
    }
    
    struct students newStudent;
    
    // Set student number no.
    newStudent.No = TotalStudents + 1;
    
    //student ID
    printf("Enter Student ID (e.g., 67070503xxx): ");
    if (scanf("%lld", &newStudent.ID) != 1) {
        printf("Invalid ID format.\n");
        clearInputBuffer();
        return;
    }
    
    // check if ID already exists
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == newStudent.ID) {
            printf("Error: Student ID already exists.\n");
            return;
        }
    }
    
    clearInputBuffer(); 
    
    //student name
    printf("Enter Student Name: ");
    fgets(newStudent.name, 30, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // Remove newline character
    
    //section
    printf("Enter Section: ");
    if (scanf("%d", &newStudent.sec) != 1) {
        printf("Invalid section format.\n");
        clearInputBuffer();
        return;
    }
    
    //score
    printf("Enter Score (0-100): ");
    if (scanf("%f", &newStudent.score) != 1) {
        printf("Invalid score format.\n");
        clearInputBuffer();
        return;
    }
    
    if (newStudent.score < 0 || newStudent.score > 100) {
        printf("Error: Score must be between 0 and 100.\n");
        return;
    }
    
    // Update max score (if needed)
    if (newStudent.score > MaxScore) {
        MaxScore = newStudent.score;
    }
    
    // Add the new student to the array
    student[TotalStudents] = newStudent;
    TotalStudents++;
    
    printf("Student added successfully!\n");
}

// Remove student 
void removeStudent() {
    long long int id;
    int found = 0;
    
    printf("Enter Student ID to remove: ");
    if (scanf("%lld", &id) != 1) {
        printf("Invalid ID format.\n");
        clearInputBuffer();
        return;
    }
    
    // Find student by ID
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == id) {
            found = 1;
            
            // shifting all students one position back
            for (int j = i; j < TotalStudents - 1; j++) {
                student[j] = student[j + 1];
            }
            
            TotalStudents--;
            printf("Student removed successfully!\n");
            
            // Renumber the students no.
            for (int j = 0; j < TotalStudents; j++) {
                student[j].No = j + 1;
            }
            
            // Recalculate the max score (if needed)
            if (id == MaxScore) {
                MaxScore = 0;
                for (int j = 0; j < TotalStudents; j++) {
                    if (student[j].score > MaxScore) {
                        MaxScore = student[j].score;
                    }
                }
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %lld not found.\n", id);
    }
}

// Edit a student's score
void editStudentScore() {
    long long int id;
    int found = 0;
    float newScore;
    
    printf("Enter Student ID to edit score: ");
    if (scanf("%lld", &id) != 1) {
        printf("Invalid ID format.\n");
        clearInputBuffer();
        return;
    }
    
    // Find student by ID
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == id) {
            found = 1;
            
            printf("Current score for %s: %.2f\n", student[i].name, student[i].score);
            printf("Enter new score (0-100): ");
            
            if (scanf("%f", &newScore) != 1) {
                printf("Invalid score format.\n");
                clearInputBuffer();
                return;
            }
            
            if (newScore < 0 || newScore > 100) {
                printf("Error: Score must be between 0 and 100.\n");
                return;
            }
            
            student[i].score = newScore;
            printf("Score updated successfully!\n");
            
            // Update max score (if needed)
            if (newScore > MaxScore) {
                MaxScore = newScore;
            } else if (student[i].score == MaxScore && newScore < MaxScore) {
                // Recalculate max score
                MaxScore = 0;
                for (int j = 0; j < TotalStudents; j++) {
                    if (student[j].score > MaxScore) {
                        MaxScore = student[j].score;
                    }
                }
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %lld not found.\n", id);
    }
}

// Sort students by name, ID, or score
void sortStudents() {
    int choice;
    
    printf("\nSort by:\n");
    printf("1. Name\n");
    printf("2. ID\n");
    printf("3. Score\n");
    printf("Enter your choice (1-3): ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    
    switch (choice) {
        case 1:
            qsort(student, TotalStudents, sizeof(struct students), compareByName);
            printf("Students sorted by name.\n");
            break;
        case 2:
            qsort(student, TotalStudents, sizeof(struct students), compareByID);
            printf("Students sorted by ID.\n");
            break;
        case 3:
            qsort(student, TotalStudents, sizeof(struct students), compareByScore);
            printf("Students sorted by score.\n");
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }
    
    // Renumber the students after sorting no.
    for (int i = 0; i < TotalStudents; i++) {
        student[i].No = i + 1;
    }
    
    // Display the sorted students
    displayStudents();
}

// Display all students
void displayStudents() {
    printf("\n%-5s %-15s %-35s %-10s %-7s\n", "No.", "Student ID", "Student Name", "Section", "Score");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < TotalStudents; i++) {
        printf("%-5d %-15lld %-35s %-10d %-7.2f\n", 
            student[i].No, 
            student[i].ID, 
            student[i].name, 
            student[i].sec, 
            student[i].score);
    }
    
    printf("\nTotal Students: %d\n", TotalStudents);
    printf("Maximum Score: %.2f\n", MaxScore);
}

// Save student data to CSV file
void saveToCSV() {
    FILE *file = fopen("ScoreSheet.csv", "w");
    
    if (file == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }
    
    //header
    fprintf(file, "No.,Student ID,Student Name,Section,Score\n");
    
    //student data
    for (int i = 0; i < TotalStudents; i++) {
        fprintf(file, "%d,%lld,%s,%d,%.0f\n", 
            student[i].No, 
            student[i].ID, 
            student[i].name, 
            student[i].sec, 
            student[i].score);
    }
    
    fclose(file);
}

// Comparison function for sorting by name
int compareByName(const void* a, const void* b) {
    const struct students* studentA = (const struct students*)a;
    const struct students* studentB = (const struct students*)b;
    return strcmp(studentA->name, studentB->name);
}

// Comparison function for sorting by ID
int compareByID(const void* a, const void* b) {
    const struct students* studentA = (const struct students*)a;
    const struct students* studentB = (const struct students*)b;
    
    if (studentA->ID < studentB->ID) return -1;
    if (studentA->ID > studentB->ID) return 1;
    return 0;
}

// Comparison function for sorting by score (descending order)
int compareByScore(const void* a, const void* b) {
    const struct students* studentA = (const struct students*)a;
    const struct students* studentB = (const struct students*)b;
    
    if (studentA->score > studentB->score) return -1;
    if (studentA->score < studentB->score) return 1;
    return 0;
}

// Clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}