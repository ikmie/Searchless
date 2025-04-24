#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int TotalStudents;
float MaxScore;

struct students{
    int No;
    long long int ID;
    char name[30];
    int sec;
    float score;
}student[1000];

void studentInformation();

#endif