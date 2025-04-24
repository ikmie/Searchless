//This code is for reading the csv file

#include "Initialize.h"

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