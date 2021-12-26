/*
User interfaces are stored in this file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calendar.h"


// usr interface

/**
 * @description: UI to get a valid month from usr, function will check the validity of the usr input,if usr want to go back to the main menu, -1 will be given as the return value
 * @param {*}
 * @return {*} month (numerical)
 */
int getMonthUI(void){
    int month;
    do {
        char input[128];
        memset(input,0,sizeof(char[128]));
        printf("Please select a month('q' back to main menu):");
        fflush(stdin);
        scanf("%[^\n]%*c",input);
        
        // back to main menu
        if(*input == 'q'){
            return -1;
        }
        
        month = strMonth_to_numMonth(input);
        if (month == 0)
            printf("WARNING: Invalid input! (Wrong Month)\n");

    } while(month == 0);

    return month;
}





/**
 * @description: UI to get a valid day from usr, function will check the validity of the usr input,if usr want to go back to the main menu, -1 will be given as the return value
 * @param {int} current month
 * @return {*} day(in this month,numerical)
 */
int getDayUI(int month){
    int day;   
    do {
        char input[128];
        memset(input,0,sizeof(char[128]));
        printf("Please select a day('q' back to main menu):");
        fflush(stdin);
        scanf("%[^\n]%*c",input);

        // back to main menu
        if(*input == 'q'){
            return -1;
        }

        if(oneDigit(input) == 0){
            printf("More than one day or invalid characters\n");
            day = -1;
        }
        else{
            day = atoi(input);
            if(checkDay(month,day) == 0)
                printf("WARNING: Invalid input! (Wrong Date)\n");
        }
    } while(checkDay(month,day) == 0);

    return day;
}





/**
 * @description: UI to help usr show month
 * @param {Calendar *} calendar
 * @return {*}
 */
void showMonthUI(Calendar * calendar){
    int month = getMonthUI();
    // check if usr want to go back to main menu
    if(month == -1){
        return;
    }
    // clear();
    showMonth(month,calendar);
    return;
}





/**
 * @description: UI to help usr add a new events
 * @param {Calendar *} calendar
 * @return {*}
 */
void addEventUI(Calendar * calendar){
    int month;
    int day;
    char title[EVENTLEN];
    memset(title,0,sizeof(char[EVENTLEN]));

    // get vaild date from usr input
    month = getMonthUI();
    if (month == -1){
        // back to main menu
        return;
    }
    

    while(1){
        day = getDayUI(month);
        if (day == -1){
            // back to main menu
            return;
        }
        printf("Here are the events you have day\n");
        inquireEvents(month,day,calendar);

        printf("Please input your event('q!' back to main menu):");
        // clean stdin
        fflush(stdin);
        s_getline(title,stdin);
        // if usr input 'q!',back to main menu
        // if press 'q' quit, it may cause that usr can not add an event lead with 'q'
        if(title[0] == 'q' && title[1] == '!'){
            return;
        }
        addEvent(title,month,day,calendar);
        printf("After adding the event(s), the event(s) for today are as follows:\n");
        inquireEvents(month,day,calendar);
    }
    return;
}






/**
 * @description: UI to help usr delete events
 * @param {Calendar *} calendar
 * @return {*}
 */
void delEventUI(Calendar * calendar){
    int month;
    int day;
    // int eventId;


    // get vaild date from usr input
    month = getMonthUI();
    if (month == -1){
        // back to main menu
        return;
    }

    while(1){
        day = getDayUI(month);
        if (day == -1){
            // back to main menu
            return;
        }

        // check if have events today
        Day * pday = &(calendar -> months[month-1].days[day-1]);
        if(pday -> head == NULL){
            printf("No events today!\n");
            return;
        }

        // eventNum stores how many events are there today
        int eventNum = inquireEvents(month,day,calendar);
        printf("Please select the events you want to delete('q' back to main menu):");
        // clean stdin(prevent unexpected error)
        fflush(stdin);
        
        char input[128];
        memset(input,0,sizeof(char[128]));
        s_getline(input,stdin);
        // clear();

        // if usr input 'q', back to main menu
        if(*input == 'q'){
            return;
        }


        int * eventIds;
        eventIds = malloc(sizeof(int[eventNum]));
        memset(eventIds,0,sizeof(int[eventNum]));
        int * peventId = eventIds;
        char * pinput = input;
        // store all the id to an array and del the repeated id
        while(*pinput != '\0'){
            if (*pinput == ' '){
                pinput++;
                continue;
            }
            int tmp = atoi(pinput);
            int isRepeat = 0;
            // check if repeat
            for(int i = 0; i < eventNum; i++){
                // check if out of range
                if(tmp > eventNum || tmp <= 0){
                    printf("WARNING: %d is a Wrong EventID! (will be excluded)\n",tmp);
                    isRepeat = 1;
                    break;
                }
                // if repeated -> 1 ,no repeated -> 0
                if(eventIds[i] == tmp){
                    isRepeat = 1;
                    break;
                }
            }
            // if no repeat, add to the arr, if repeat, do not add to the arr
            if(isRepeat == 0)
                *peventId++ = tmp;
            else
                peventId++;
            // advance the pointer to next event id
            while(*pinput != ' ' && *pinput != '\0' ){
                pinput++;
            }
        }


        // since linked list is used, we must delete the event from large index to small index
        sort(eventIds,eventNum);
        // if there are no valid event will be deleted, value equal to 0
        int haveEvent = 1;
        // del event one by one
        for(int i = 0; i < eventNum; i++){
            // if current eventId = 0, which means reach the end of arr
            if(eventIds[i] == 0){
                if(i == 0){
                    // if the first value in the arr is 0, means no vaild event to be delete
                    haveEvent = 0;
                    printf("No valid events to be deleted (invalid eventId)\n");
                    return;
                }
                break;
            }
            if(haveEvent){
                delEvent(eventIds[i],month,day,calendar);
            }
        }
        
        // show todays' events today
        printf("After deleting the event(s)(invalid eventId is excluded), the remaining event(s) for today are as follows:\n");
        inquireEvents(month,day,calendar);
    }

    return;
}






/**
 * @description: UI to help usr inquire events
 * @param {Calendar *} calendar
 * @return {*}
 */
void inquireEventsUI(Calendar * calendar){
    int month;
    int day;

    // get vaild date from usr input
    month = getMonthUI();
    if (month == -1){
        // back to main menu
        return;
    }
    while(1){
        day = getDayUI(month);
        if (day == -1){
            // back to main menu
            return;
        }
        inquireEvents(month,day,calendar);
    }

}





/**
 * @description: UI to help usr search events(fuzzy search is supported)
 * @param {Calendar *} calendar
 * @return {*}
 */
void searchEventUI(Calendar * calendar){
    int months[SEARCHSIZE];
    int days[SEARCHSIZE];
    int eventIds[SEARCHSIZE];
    char target[EVENTLEN];
    printf("Please input the event you want to search:");
    fflush(stdin);
    s_getline(target,stdin);
    searchEvent(target,months,days,eventIds,calendar);
    
    // check if there are anything match
    if(*months == 0){
        printf("Nothing Match!\n");
        return;
    }


    printf("The most similar events are listed below:\n");
    for(int i = 0; i < SEARCHSIZE; i++){
        if(months[i] == 0){
            break;
        }
        int m = months[i];
        int d = days[i];
        Event * pevent = (calendar -> months[m-1].days[d-1].head);
        // advance pointer to the right place
        for(int j = 1; j < eventIds[i]; j++){
            if (pevent -> next == NULL){
                break;
            }
            pevent = pevent -> next;
        }
        printf("%2d.%-2d\t%s\n",months[i],days[i],pevent -> title);
    }
    return;
}






/**
 * @description: fuzzy search invent
 * @param {char *} target
 * @param {int *} months
 * @param {int *} days
 * @param {int *} eventIds
 * @param {Calendar *} calendar
 * @return {*}
 */
void searchEvent(char * target, int * months, int * days,int * eventIds, Calendar * calendar){
    const int days_in_months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // init the array
    // set distance threshold
    int distance[SEARCHSIZE] = {0};
    memset(distance,20,sizeof(int[SEARCHSIZE]));
    memset(months,THRESHOLD,sizeof(int[SEARCHSIZE]));
    memset(days,0,sizeof(int[SEARCHSIZE]));
    memset(eventIds,0,sizeof(int[SEARCHSIZE]));
    // traverse the month
    for(int month = 1; month <= 12; month++){
        // traverse the day
        for(int day = 1; day <= days_in_months[month - 1]; day++){

            Day * pday = &(calendar -> months[month - 1].days[day - 1]);
            // check if have events today
            if (pday -> head == NULL){
                continue;
            }
            // traverse the event
            Event * pevent = pday -> head;
            for(int eventId = 1; ;eventId++){
                int tmp_dist = editDistance(pevent -> title,target);
                // printf("distance between %s and %s is: %d\n",pevent -> title, target, tmp_dist);
                // check if tmp_dist is smaller than the largest distance, if true, put this event to the array
                for(int i = 0; i < SEARCHSIZE; i++){
                    if(tmp_dist < distance[i]){
                        distance[i] = tmp_dist;
                        months[i] = month;
                        days[i] = day;
                        eventIds[i] = eventId;
                        break;
                    }
                }
                // check the if next events exists
                if(pevent -> next != NULL){
                    (pevent = pevent -> next);
                }
                else
                    break;
            }
        }    
    }
    return;
}