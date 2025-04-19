//This code is for reading the csv file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void studentInformation();

//Will be used to keep track of the amount of students, starts at 0
int TotalStudents = 0;
//will be used to keep track of the max score
float MaxScore=-1;

//Data struct with student information
struct students{
    int No;
    long long int ID;
    char name[30];
    int sec;
    float score;
}student[1000];

//function for reading csv file
void studentInformation(){

    //opens file
    FILE *file = fopen("ScoreSheet.csv","r");

    //check if file exists
    if (file == NULL){
        printf("Error: Unable to open the file.\n");
        return;
    }

    //variables
    char line[1000];
    int i=0, isFirstLine=1;

    while (fgets(line, sizeof(line), file))
    {
        //skips the header
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        //gets the information
        sscanf(line, "%d,%lld,%[^,],%d,%f",
               &student[i].No, &student[i].ID,
               student[i].name, &student[i].sec,
               &student[i].score);

        TotalStudents++;

        //find max score
        if(student[i].score>MaxScore){

            MaxScore=student[i].score;

        }

        i++;
    }

    //close the file
    fclose(file);

}