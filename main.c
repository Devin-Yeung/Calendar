#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calendar.h"

int main(void){
    setbuf(stdout,NULL);
    // init an empty calendar
    Calendar calendar;
    initCalendar(2022,&calendar);
    // read data from file
    readFile(&calendar);

    while(1){
        printf("*==================================*\n");
        printf("*      1) Display month calendar   *\n");
        printf("*      2) Add events               *\n");
        printf("*      3) Delete events            *\n");
        printf("*      4) Inquire events           *\n");
        printf("*      5) Search events            *\n");
        printf("*      6) Quit                     *\n");
        printf("*==================================*\n");
        printf("Please enter the choice number to select the operation:");
    
        // clear stdin
        fflush(stdin);
        char usrInput[128];
        fgets(usrInput,127,stdin);

        int selection = 0;
        selection =  atoi(usrInput);
        // if input 'q', also quit
        if(*usrInput == 'q'){
            selection = 6;
        }
        // indicate whether program will exit or not
        _Bool willExit = 0;
        switch(selection) {
            case 1:
                showMonthUI(&calendar);
                break;
            case 2:
                addEventUI(&calendar);
                // save file after the operation
                writeFile(&calendar);
                break;
            case 3:
                delEventUI(&calendar);
                // save file after the operation
                writeFile(&calendar);
                break;
            case 4:
                inquireEventsUI(&calendar);
                break;
            case 5:
                searchEventUI(&calendar);
                break;
            case 6:
                willExit = 1;
                break;
            default:
                printf("Invalid options! Please select again !\n");
                break;
        }
        // determine exit or not
        if(willExit){
            break;
        }
    }
    // save file when quit
    writeFile(&calendar);
    return 0;
}
