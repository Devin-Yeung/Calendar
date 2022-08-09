/*
Data operations are stored in this file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calendar.h"





/**
 * @description: initialize an empty calendar
 * @param {int} current year
 * @param {Calendar *} calendar
 * @return {*}
 * FIXME: leap year is not supported
 */
void initCalendar(int year, Calendar * calendar){
    // const int leap_daysInMonths[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    const int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // init months and year
    calendar -> year = year;
    calendar -> months = malloc(sizeof(Month[12]));
    
    // init days
    for(int i = 0; i < 12; i++){
        // j stores how many days in this month
        int j = daysInMonths[i];
        calendar -> months[i].days = malloc(sizeof(Day[j])); 
    }

    // init events for everyday
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < daysInMonths[i]; j++){
            // set pday to current day
            Day * pday = &(calendar -> months[i].days[j]);
            // init events
            pday -> head = NULL;
        }
    }
}





/**
 * @description: destory the calendar
 * @param {Calendar *} calendar
 * @return {*}
 */
void destoryCalendar(Calendar * calendar){
    // const int leap_daysInMonths[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    const int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // destory events for everyday
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < daysInMonths[i]; j++){
            // set pday to current day
            Day * pday = &(calendar -> months[i].days[j]);
            // destory events
            Event * pevent = pday -> head;
            while(pevent != NULL) {
                Event * pcur = pevent;
                pevent = pevent->next;
                free(pcur);
            }
        }
    }

    // destory days
    for(int i = 0; i < 12; i++){
        free(calendar -> months[i].days);
    }

    // destory months 
    free(calendar -> months);
}





/**
 * @description: show the calendar view for a given month
 * @param {int} month
 * @param {Calendar *} calendar
 * @return {*}
 */
void showMonth(int month, Calendar * calendar){ 
    const char * weeks = "Su Mo Tu We Th Fr Sa";
    const int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    const char * months[12] = {"January","February","March","April","May","June","July","August","September","Octorber","November","December"};

    // generate the head of the calendar
    int left_width =( 20 - strlen(months[month - 1]) ) / 2;
    int right_width = 20 - strlen(months[month - 1]) - left_width;
    // printf("%s","=====================\n");
    printf("%*s",left_width,"");
    printf("%s",months[month - 1]);
    printf("%*s\n",right_width,"");
    printf("%s\n",weeks);

    // get first day of the month
    int week_day = Zeller(calendar -> year,month,1);
    printf("%*s",week_day * 3,"");
    // print the date one by one
    for(int day = 1; day <= daysInMonths[month - 1]; day++){
        Day * pday = &(calendar -> months[month-1].days[day-1]);

        // start a new line when week day is 7 and reset
        if(week_day == 7){
            week_day = 0;
            printf("\n");
        }

        // deal with the output content
        char date[4];
        char * pdate;
        pdate = date;
        memset(date,0,sizeof(char[4]));
        date[3] = '\0';
        if(day < 10){
            *pdate = ' ';
            pdate++;
        }
        // integer to char
        sprintf(pdate,"%d",day);

        // check if there are any events today, if any event exist, add a '+' sign
        if(pday -> head != NULL){
            date[2] = '+';
        }
        else{
            date[2] = ' ';
        }
        printf("%s",date);
        week_day++;
    }
    printf("\n");
}





/**
 * @description: add event to a certain day, month and day must be correct
 * @param {char*} the name of the event
 * @param {int} current month
 * @param {int} current day
 * @param {Calendar *} calendar
 * @return {*}
 */
void addEvent(char* event, int month, int day, Calendar * calendar){
    Day * pday = &(calendar -> months[month-1].days[day-1]);

    // allocate memory for the new event
    Event * pevent = malloc(sizeof(Event));
    // init the event
    memset(pevent -> title,0,EVENTLEN);
    pevent -> next = NULL;
    strncpy(pevent -> title,event,EVENTLEN);

    // check if there are any events today, if no event exists, head must point to the new event
    if(pday -> head == NULL){
        pday -> head = pevent;
    }
    // if there are events today, find the last events
    else{
        Event * pscan = pday -> head;
        while(pscan -> next != NULL){
            pscan = pscan -> next;
        }
        // let the last event point to the new event
        pscan -> next = pevent;
    }
}






/**
 * @description: delete a certain event in a certain day, eventId can be seen from the output of inquireEvents(), month and day must be correct
 * @param {int} eventId
 * @param {int} current month
 * @param {int} current day
 * @param {Calendar *} calendar
 * @return {*}
 */
void delEvent(int eventId, int month, int day, Calendar * calendar){
    Day * pday = &(calendar -> months[month-1].days[day-1]);
    Event * pevent = pday -> head;

    // check if there are any events today
    if(pevent == NULL){
        printf("No events today! \n");
        return;
    }

    // if usr delete the first event, let head point to the second event
    if(eventId == 1){
        pday -> head = pevent -> next;
        free(pevent);
        return;
    }

    // let pointer point to the event before the event to be deleted
    for(int i = 2; i < eventId; i++){
        // check if reach the end of the list
        if(pevent -> next == NULL){
            printf("Wrong EventID! (out of range)\n");
            return;
        }
        // advance pointer
        pevent = pevent -> next;
    }
    // check if reach the end of the list
    if(pevent -> next == NULL){
        printf("Wrong EventID! (out of range)\n");
        return;
    }


    // check if the event to be deleted is the last event
    if(pevent -> next -> next == NULL){
        // pdel point to the event to be deleted
        Event * pdel = pevent -> next;
        pevent -> next = NULL;
        free(pdel);
    }
    else{
        // pdel point to the event to be deleted
        Event * pdel = pevent -> next;
        pevent -> next = pdel -> next;
        free(pdel);
    }

}





/**
 * @description: inquire events for a certain date, the result will be print out in the console, month and day must be correct
 * @param {int} current month
 * @param {int} current day
 * @param {Calendar *} calendar
 * @return {int} number of events
 */
int inquireEvents(int month, int day, Calendar * calendar){
    Day * pday = &(calendar -> months[month-1].days[day-1]);
    Event * pevent = pday -> head;
    // counter stores how many events are there today
    int counter = 0;
    // check if there are any events today
    if(pevent == NULL){
        printf("No events today! \n");
        return counter;
    }

    for(int i = 1; pevent != NULL; i++){
        printf("%d. %s\n",i,pevent -> title);
        counter++;
        // advance pointer
        pevent = pevent -> next;
    }
    return counter;
}





