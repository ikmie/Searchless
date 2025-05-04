

#include "Search.h"


void searchbyID(long long int id) {
    int isFound = 0;
    for (int index = 0; index < TotalStudents; index++) {
        if (student[index].ID == id) {
            printf("Found student:\n");
            printf("No: %d\nID: %lld\nName: %s\nSection: %d\nScore: %.2f\n",
                   student[index].No, student[index].ID, student[index].name,
                   student[index].sec, student[index].score);
            isFound = 1;
            break;
        }
    }
    if (!isFound)
        printf("Student ID %lld not found.\n", id);
}

void searchbyName(const char *name) {
    int isFound = 0;
    for (int index = 0; index < TotalStudents; index++) {
        if (strcasecmp(student[index].name, name) == 0) {
            printf("Match found:\n");
            printf("No: %d\nID: %lld\nName: %s\nSection: %d\nScore: %.2f\n\n",
                   student[index].No, student[index].ID, student[index].name,
                   student[index].sec, student[index].score);
            isFound = 1;
        }
    }
    if (!isFound)
        printf("This Name is not found.\n");
}

/*This function helps users search from a range of scores, e.g 1-20 will be displayed
                                                               20-30 will be displayed
*/
void searchScoreRange(float min, float max) {
    int isFound = 0;
    printf("Students with scores between %.2f and %.2f:\n", min, max);
    for (int index = 0; index < TotalStudents; index++) {
        if (student[index].score >= min && student[index].score <= max) {
            printf("No: %d\nID: %lld\nName: %s\nSection: %d\nScore: %.2f\n\n",
                   student[index].No, student[index].ID, student[index].name,
                   student[index].sec, student[index].score);
            isFound = 1;
        }
    }
    if (!isFound)
        printf("No students found in the score range.\n");
}
