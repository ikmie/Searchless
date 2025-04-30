#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Initialize.h"

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

#endif /* STUDENTMANAGER_H */