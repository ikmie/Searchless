//This code is for the main grouping function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Initialize.h"

int main(){

    studentInformation();

    for(int i=0;i<TotalStudents;i++){

        printf("%d %lld %s %d %.2f\n",student[i].No ,student[i].ID, student[i].name, student[i].sec, student[i].score);

    }

    printf("%.2f",MaxScore);

}