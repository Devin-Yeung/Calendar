/*
File I/O operations are stored in this file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calendar.h"


// File operations

/**
 * @description: load all the data from file and write to the memory, the file must be named with the month(Initial the capital letter)
 * @param {Calendar *} calendar
 * @return {*}
 * FIXME: If the file does not exist, create the file instead
 */
void readFile(Calendar * calendar){

    const char * MonthFile[12] = {"January.txt","February.txt","March.txt","April.txt","May.txt","June.txt","July.txt","August.txt","September.txt","Octorber.txt","November.txt","December.txt"};

    // i indicate the current month
    for(int i = 1; i <= 12; i++){

        FILE * fp = fopen(MonthFile[i-1],"r");

        // check wether can open the file
        if(fp == NULL){
            printf("Can not open the file!\n");
            printf("The file will be initialize after your quit this program.\n");
            return;
        }
        // check if file is empty, if empty, close the file
        if(feof(fp) == EOF){
            fclose(fp);
            return;
        }

        char line[EVENTLEN+8];
        char title[EVENTLEN];
        int today;
        // check if reach the end of the file
        while(s_getline(line, fp) != 1){
            // extract info from current line and 
            extractEvent(line,title);
            today = extractDate(line);
            addEvent(title,i,today,calendar);
            // empty the line and title
            memset(line,0,EVENTLEN+8);
            memset(title,0,EVENTLEN);
        }
        
        fclose(fp);

    }
    return;
}






/**
 * @description: load all the data from memory and write to the file, the file must be named with the month(Initial the capital letter)
 * @param {Calendar *} calendar
 * @return {*}
 */
void writeFile(Calendar * calendar){
    const char * MonthFile[12] = {"January.txt","February.txt","March.txt","April.txt","May.txt","June.txt","July.txt","August.txt","September.txt","Octorber.txt","November.txt","December.txt"};
    const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // i indicate the current month
    for(int i = 1; i <= 12; i++){
        FILE * fp = fopen(MonthFile[i-1],"w");

        // check wether can open the file
        if(fp == NULL){
            printf("Can not open the file!");
            return;
        }
        fflush(fp);
        // j indicate the current day
        for(int j = 1; j < daysInMonth[i-1]; j++){
            Day * pday = &(calendar -> months[i-1].days[j-1]);

            Event * pscan = pday -> head;
            // check if there are events today
            while (pscan != NULL){
                fprintf(fp,"%d|%s\n",j,pscan -> title);
                pscan = pscan -> next;
            }
        }
           
        fclose(fp);
    }
}
