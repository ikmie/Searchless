// StudentManager.c

#include "StudentManager.h"
#include <ctype.h>

void displayMenu() {
    printf("\n\n");
    printf(" _________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|            STUDENT MANAGEMENT SYSTEM MENU               |\n");
    printf("|_________________________________________________________|\n");
    printf("| 1. Display all students                                 |\n");
    printf("| 2. Display students by section                          |\n");
    printf("| 3. Display top performers                               |\n");
    printf("| 4. Search student by ID                                 |\n");
    printf("| 5. Search student by name                               |\n");
    printf("| 6. Display statistics                                   |\n");
    printf("| 7. Create student groups                                |\n");
    printf("| 8. Add Student                                          |\n"); // Added option 8
    printf("| 9. Delete Student                                       |\n"); // Added option 9
    printf("| 10. Edit Student                                         |\n"); // Added option 10
    printf("| 11. Exit                                                |\n"); // Changed 8 to 11
    printf("|_________________________________________________________|\n");
    printf("\n>> Please enter your choice: ");
}

void displayAllStudents() {
    printf("\n<------------------- ALL STUDENTS ------------------->\n");
    printf(" ________________________________________________________ \n");
    printf("| No. | STUDENT ID |      STUDENT NAME       | SEC | SCORE |\n");
    printf("|_____|____________|_________________________|_____|_______|\n");
    
    for (int i = 0; i < TotalStudents; i++) {
        printf("| %3d | %lld | %-22s | %2d  | %5.1f |\n", 
            student[i].No, student[i].ID, student[i].name, 
            student[i].sec, student[i].score);
    }
    
    printf("|_____|____________|_________________________|_____|_______|\n");
    printf("| Total students: %3d                                   |\n", TotalStudents);
    printf("|_______________________________________________________|\n");
}

void displayStudentsBySection(int section) {
    int count = 0;
    float totalScore = 0.0, avgScore = 0.0;
    
    printf("\n<----------- STUDENTS IN SECTION %d ----------->\n", section);
    printf(" ________________________________________________________ \n");
    printf("| No. | STUDENT ID |      STUDENT NAME       | SEC | SCORE |\n");
    printf("|_____|____________|_________________________|_____|_______|\n");
    
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].sec == section) {
            printf("| %3d | %lld | %-22s | %2d  | %5.1f |\n", 
                student[i].No, student[i].ID, student[i].name, 
                student[i].sec, student[i].score);
            count++;
            totalScore += student[i].score;
        }
    }
    
    if (count > 0) {
        avgScore = totalScore / count;
    }
    
    printf("|_____|____________|_________________________|_____|_______|\n");
    printf("| Total students: %3d                                   |\n", count);
    printf("| Average score: %5.2f                                  |\n", avgScore);
    printf("|_______________________________________________________|\n");
}

void displayTopStudents(int n) {
    if (n <= 0 || n > TotalStudents) {
        printf("\n<--- Invalid number of students! Please enter a value between 1 and %d --->\n", TotalStudents);
        return;
    }
    
    // Create a copy of the student array to sort
    struct students tempStudents[1000];
    for (int i = 0; i < TotalStudents; i++) {
        tempStudents[i] = student[i];
    }
    
    // Sort by score in descending order
    for (int i = 0; i < TotalStudents - 1; i++) {
        for (int j = i + 1; j < TotalStudents; j++) {
            if (tempStudents[i].score < tempStudents[j].score) {
                struct students temp = tempStudents[i];
                tempStudents[i] = tempStudents[j];
                tempStudents[j] = temp;
            }
        }
    }
    
    printf("\n<------------------- TOP %d STUDENTS ------------------->\n", n);
    printf(" ________________________________________________________ \n");
    printf("| RANK | STUDENT ID |      STUDENT NAME       | SEC | SCORE |\n");
    printf("|______|____________|_________________________|_____|_______|\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %3d  | %lld | %-22s | %2d  | %5.1f |\n", 
            i + 1, tempStudents[i].ID, tempStudents[i].name, 
            tempStudents[i].sec, tempStudents[i].score);
    }
    
    printf("|_____|____________|_________________________|_____|_______|\n");
}

void searchStudentByID(long long int studentID) {
    int found = 0;
    
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == studentID) {
            printf("\n<------------------- STUDENT FOUND ------------------->\n");
            printf(" ________________________________________________________ \n");
            printf("| No. | STUDENT ID |      STUDENT NAME       | SEC | SCORE |\n");
            printf("|_____|____________|_________________________|_____|_______|\n");
            printf("| %3d | %lld | %-22s | %2d  | %5.1f |\n", 
                student[i].No, student[i].ID, student[i].name, 
                student[i].sec, student[i].score);
            printf("|_____|____________|_________________________|_____|_______|\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\n<--- Student with ID %lld was not found! --->\n", studentID);
    }
}

void searchStudentByName(char *name) {
    int found = 0;
    char searchName[30];
    char tempName[30];
    
    // Convert search name to lowercase for case-insensitive search
    strcpy(searchName, name);
    for (int i = 0; searchName[i]; i++) {
        searchName[i] = tolower(searchName[i]);
    }
    
    printf("\n<------------------- SEARCH RESULTS ------------------->\n");
    printf(" ________________________________________________________ \n");
    printf("| No. | STUDENT ID |      STUDENT NAME       | SEC | SCORE |\n");
    printf("|_____|____________|_________________________|_____|_______|\n");
    
    for (int i = 0; i < TotalStudents; i++) {
        // Convert student name to lowercase for comparison
        strcpy(tempName, student[i].name);
        for (int j = 0; tempName[j]; j++) {
            tempName[j] = tolower(tempName[j]);
        }
        
        // Check if search term appears in student name
        if (strstr(tempName, searchName) != NULL) {
            printf("| %3d | %lld | %-22s | %2d  | %5.1f |\n", 
                student[i].No, student[i].ID, student[i].name, 
                student[i].sec, student[i].score);
            found = 1;
        }
    }
    
    printf("|_____|____________|_________________________|_____|_______|\n");
    
    if (!found) {
        printf("\n<--- No students matching '%s' were found! --->\n", name);
    }
}

void displayStatistics() {
    float sum = 0.0, average = 0.0;
    float minScore = MaxScore; // Initialize to max possible score
    float maxScore = 0.0;
    int section31Count = 0, section32Count = 0;
    float section31Sum = 0.0, section32Sum = 0.0;
    
    // Calculate statistics
    for (int i = 0; i < TotalStudents; i++) {
        sum += student[i].score;
        
        if (student[i].score < minScore) minScore = student[i].score;
        if (student[i].score > maxScore) maxScore = student[i].score;
        
        if (student[i].sec == 31) {
            section31Count++;
            section31Sum += student[i].score;
        } else if (student[i].sec == 32) {
            section32Count++;
            section32Sum += student[i].score;
        }
    }
    
    average = sum / TotalStudents;
    float section31Avg = (section31Count > 0) ? section31Sum / section31Count : 0;
    float section32Avg = (section32Count > 0) ? section32Sum / section32Count : 0;
    
    // Count students in score ranges
    int range0_25 = 0, range26_50 = 0, range51_75 = 0, range76_100 = 0;
    
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].score >= 0 && student[i].score <= 25) range0_25++;
        else if (student[i].score > 25 && student[i].score <= 50) range26_50++;
        else if (student[i].score > 50 && student[i].score <= 75) range51_75++;
        else if (student[i].score > 75 && student[i].score <= 100) range76_100++;
    }
    
    // Display statistics
    printf("\n<------------------- CLASS STATISTICS ------------------->\n");
    printf(" ________________________________________________________ \n");
    printf("| Total Students: %-38d |\n", TotalStudents);
    printf("| Average Score: %-38.2f |\n", average);
    printf("| Minimum Score: %-38.2f |\n", minScore);
    printf("| Maximum Score: %-38.2f |\n", maxScore);
    printf("|________________________________________________________|\n");
    printf("| Section 31 Students: %-32d |\n", section31Count);
    printf("| Section 31 Average: %-32.2f |\n", section31Avg);
    printf("| Section 32 Students: %-32d |\n", section32Count);
    printf("| Section 32 Average: %-32.2f |\n", section32Avg);
    printf("|________________________________________________________|\n");
    printf("| Score Distribution:                                 |\n");
    printf("| 0-25: %-6d (%-6.2f%%)                               |\n", 
        range0_25, (float)range0_25 / TotalStudents * 100);
    printf("| 26-50: %-5d (%-6.2f%%)                               |\n", 
        range26_50, (float)range26_50 / TotalStudents * 100);
    printf("| 51-75: %-5d (%-6.2f%%)                               |\n", 
        range51_75, (float)range51_75 / TotalStudents * 100);
    printf("| 76-100: %-4d (%-6.2f%%)                               |\n", 
        range76_100, (float)range76_100 / TotalStudents * 100);
    printf("|________________________________________________________|\n");
}

void runStudentManager() {
    int choice;
    int keepRunning = 1;
    
    while (keepRunning) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear input buffer
        
        switch (choice) {
            case 1:
                displayAllStudents();
                break;
                
            case 2: {
                int section;
                printf("\n>> Enter section number: ");
                scanf("%d", &section);
                getchar(); // Clear input buffer
                displayStudentsBySection(section);
                break;
            }
                
            case 3: {
                int n;
                printf("\n>> Enter number of top students to display: ");
                scanf("%d", &n);
                getchar(); // Clear input buffer
                displayTopStudents(n);
                break;
            }
                
            case 4: {
                long long int id;
                printf("\n>> Enter student ID to search: ");
                scanf("%lld", &id);
                getchar(); // Clear input buffer
                searchStudentByID(id);
                break;
            }
                
            case 5: {
                char name[30];
                printf("\n>> Enter student name to search: ");
                fgets(name, 30, stdin);
                // Remove trailing newline character
                name[strcspn(name, "\n")] = 0;
                searchStudentByName(name);
                break;
            }
                
            case 6:
                displayStatistics();
                break;
                
            case 7:
                CreateGroup();
                break;
                
            case 8: { // Case 8: Add Student
                int no, sec;
                long long int id;
                char name[30];
                float score;
                
                printf("\n>> Enter student details:\n");
                printf("   No: ");
                scanf("%d", &no);
                getchar(); // Clear input buffer
                printf("   ID: ");
                scanf("%lld", &id);
                getchar(); // Clear input buffer
                printf("   Name: ");
                fgets(name, 30, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                printf("   Section: ");
                scanf("%d", &sec);
                getchar(); // Clear input buffer
                printf("   Score: ");
                scanf("%f", &score);
                getchar(); //clear input buffer
                
                addStudent(no, id, name, sec, score); // Call addStudent with arguments
                break;
            }
            case 9: { // Case 9: Delete Student
                long long int id;
                printf("\n>> Enter student ID to delete: ");
                scanf("%lld", &id);
                getchar(); // Clear input buffer
                
                int result = deleteStudent(id); // Call deleteStudent with argument
                if (result) {
                    printf("\n<--- Student deleted successfully! --->\n");
                } else {
                    printf("\n<--- Student with ID %lld not found! --->\n", id);
                }
                break;
            }
            case 10: { // Case 10: Edit Student
                long long int id;
                char newName[30];
                int newSec;
                float newScore;
                
                printf("\n>> Enter student ID to edit: ");
                scanf("%lld", &id);
                getchar(); // Clear input buffer
                printf("   New Name: ");
                fgets(newName, 30, stdin);
                newName[strcspn(newName, "\n")] = 0; // Remove newline
                printf("   New Section: ");
                scanf("%d", &newSec);
                getchar(); // Clear input buffer
                printf("   New Score: ");
                scanf("%f", &newScore);
                getchar(); //clear input buffer
                
                int result = editStudent(id, newName, newSec, newScore); // Call editStudent with arguments
                if (result) {
                    printf("\n<--- Student edited successfully! --->\n");
                } else {
                    printf("\n<--- Student with ID %lld not found! --->\n", id);
                }
                break;
            }
                
            case 11: // Changed from 8 to 11
                printf("\n<------------------- EXITING PROGRAM ------------------->\n");
                printf("Thank you for using the Student Management System!\n");
                keepRunning = 0;
                break;
                
            default:
                printf("\n<--- Invalid choice! Please try again. --->\n");
                break;
        }
    }
}

