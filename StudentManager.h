#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Initialize.h"
#include "Grouper.h"
#include "Search.h"
#include "FileEdit.h"

// Function prototypes for student manager
void displayMenu();
void runStudentManager();
void displayAllStudents();
void displayStudentsBySection(int section);
void displayTopStudents(int n);
void searchStudentByID(long long int studentID);
void searchStudentByName(char *name);
void displayStatistics();

#endif