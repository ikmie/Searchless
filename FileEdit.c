#include "FileEdit.h"

void addStudent(int No, long long int ID, const char* name, int sec, float score) {
    if (TotalStudents >= 1000) {
        printf("Error: Maximum student capacity reached.\n");
        return;
    }

    student[TotalStudents].No = No;
    student[TotalStudents].ID = ID;
    strncpy(student[TotalStudents].name, name, sizeof(student[TotalStudents].name) - 1);
    student[TotalStudents].name[sizeof(student[TotalStudents].name) - 1] = '\0';
    student[TotalStudents].sec = sec;
    student[TotalStudents].score = score;

    if (score > MaxScore) {
        MaxScore = score;
    }

    TotalStudents++;
}

int deleteStudent(long long int ID) {
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == ID) {
            for (int j = i; j < TotalStudents - 1; j++) {
                student[j] = student[j + 1];
            }
            TotalStudents--;
            recomputeMaxScore();
            return 1;
        }
    }
    return 0;
}

int editStudent(long long int ID, const char* newName, int newSec, float newScore) {
    for (int i = 0; i < TotalStudents; i++) {
        if (student[i].ID == ID) {
            strncpy(student[i].name, newName, sizeof(student[i].name) - 1);
            student[i].name[sizeof(student[i].name) - 1] = '\0';
            student[i].sec = newSec;
            student[i].score = newScore;

            recomputeMaxScore();
            return 1;
        }
    }
    return 0;
}

void recomputeMaxScore() {
    MaxScore = 0.0f;
    for (int i = 0; i < TotalStudents; ++i) {
        if (student[i].score > MaxScore) {
            MaxScore = student[i].score;
        }
    }
}

void saveToCSV(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    fprintf(file, "No.,Student ID,Student Name,Section,Score\n");

    for (int i = 0; i < TotalStudents; i++) {
        fprintf(file, "%d,%lld,%s,%d,%.2f\n",
                student[i].No,
                student[i].ID,
                student[i].name,
                student[i].sec,
                student[i].score);
    }

    fclose(file);
    printf("Student data saved.\n");
}
