#ifndef FILEEDIT_H
#define FILEEDIT_H

#include "Initialize.h"

void addStudent(int No, long long int ID, const char* name, int sec, float score);
int deleteStudent(long long int ID);
int editStudent(long long int ID, const char* newName, int newSec, float newScore);
void saveToCSV(const char* filename);

#endif
