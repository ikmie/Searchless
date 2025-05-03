//main program file 
#include "Initialize.h"
#include "Grouper.h"
#include "StudentManager.h"

int main() {
    //variables
    TotalStudents = 0;
    MaxScore = 0;
    
    //welcome box
    printf("\n");
    printf(" _________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|            WELCOME TO STUDENT MANAGEMENT SYSTEM         |\n");
    printf("|_________________________________________________________|\n");
    
    // Load student data
    printf("\n<------------ LOADING STUDENT DATA ------------->\n");
    studentInformation();
    printf("Student data loaded successfully!\n");
    printf("Total students: %d\n", TotalStudents);
    printf("Maximum score: %.2f\n", MaxScore);
    
    // Run the main application
    runStudentManager();
    
    //Clean
    if (root != NULL) {
        DeleteTree(root);
        free(root);
    }
    
    return 0;
}