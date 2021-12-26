/*
Utils are store in this file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calendar.h"


// utils

/**
 * @description: read a file line by line, and replace the '\n' to '\0' ; if reach the end of file, return -1
 * @param {char *} str(store this line)
 * @param {FILE *} pointer to the file
 * @return {_Bool} if reach the end of file 
 */
_Bool s_getline(char * str, FILE * fp){
    _Bool flag = 0;
    char * pstr = str;
    char current;
    while( (current = fgetc(fp)) != '\n' ){
        // check if reach the end of file
        if(feof(fp) != 0){
            flag = 1;
            break;
        }
        *pstr++ = current;
    }
    // *pstr = '\n';
    *pstr = '\0';

    // if reach the end of file, return 1
    return flag;
}





/**
 * @description: extract date from a certain format of str (example: 01|hello world),this function will not check the validity of the output date
 * @param {char *} string
 * @return {int} date
 */
int extractDate(char * line){
    char date[2];
    char * pdate = date;
    char * pline = line;
    while(*pline != '|'){
        // strcpy
        *pdate++ = *pline++;
    }
    return atoi(date);
}





/**
 * @description: extract event from a certain format of str (example: 01|hello world)
 * @param {char *} string
 * @param {char *} a string to store event
 * @return {*}
 */
void extractEvent(char * line, char * event){
    memset(event,0,sizeof(char[EVENTLEN]));
    char * pevent = event;
    char * pline = line;
    
    // move pointer to the character '|'
    while(*pline != '|'){
        pline++;
    }
    pline++;
    
    // strcpy
    while(*pline != '\0'){    
        *pevent++ = *pline++;
    }
    *pevent = '\0';
}






/**
 * @description: Calculate the day of the week for the given date, using Zeller algorithm
 * @param {int} current year
 * @param {int} current month
 * @param {int} current day
 * @return {int} day of week(numerical), 0 stands for Sunday, 1 stands for Monday ...
 */
int Zeller (int year, int month, int day){
    int century;
    int week;

    if(month == 1 || month == 2){
        month += 12;
        year -= 1;
    }

    century = year / 100;
    year = year % 100;     
    week = year + year / 4 + century / 4 - 2*century + 26 * (month + 1) / 10 + day - 1;

    return week % 7;
}





/**
 * @description: Check the validity of the given date
 * @param {int} current month
 * @param {int} current day
 * @return {_Bool} isVaild
 */
_Bool checkDay(int month, int day){
    const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(day <= daysInMonth[month - 1] && day >= 1 ){
        return 1;
    }
    else{
        return 0;
    }
}





/**
 * @description: Convert a string to numerical month, if nothing match or invalid input, return 0
 * @param {char *} strMonth
 * @return {int} numerical month
 */
int strMonth_to_numMonth(char * strMonth){
    const char * StrMonthA[12] = {"January","February","March","April","May","June","July","August","September","Octorber","November","December"};
    for(int i = 0; i < 12; i++){
        if(strcmp(strMonth,StrMonthA[i]) == 0){
            return i+1;
        }
    }

    const char * StrMonthB[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for(int i = 0; i < 12; i++){
        if(strcmp(strMonth,StrMonthB[i]) == 0){
            return i+1;
        }
    }

    const char * StrMonthC[12] = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    for(int i = 0; i < 12; i++){
        if(strcmp(strMonth,StrMonthC[i]) == 0){
            return i+1;
        }
    }

    // nothing match or invalid input
    return 0;
}




/**
 * @description: check if there is only one num in one line
 * @param {char *} str
 * @return {*} _Bool
 */
_Bool oneDigit(char * str){
    char * pstr = str;
    // remove leading space
    while(*pstr == ' '){
        pstr++;
    }
    // flag indicate if reach the first digit
    int flag = 0;
    while(*pstr != '\0'){
        if(flag == 0 && isdigit(*pstr) == 1){
            flag = 1;
        // jump the first num
            while(flag == 1 && isdigit(*pstr) == 1 && *pstr != '\0'){
                pstr++;
            }
            if(*pstr == '\0')
                break;
        }
        // check if have tailing spaces
        if(flag == 1 && *pstr != ' '){
            return 0;
        }
        pstr++;
    }
    return flag;
}



/**
 * @description: sort the array in descending orders
 * @param {int *} array
 * @param {int} array length
 * @return {*}
 */
void sort(int * arr,int len){
    int tmp; //for swap
    for(int i = 0; i < len; i++){
        int j = i;
        while(j > 0 && arr[j-1] < arr[j]){
            // swap
            tmp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = tmp;
            j--;
        }
    }
}





/**
 * @description: calculate the edit distance between two word, the smaller the distance means they are more similar
 * @param {char *} word1
 * @param {char *} word2
 * @return {int} distance
 * @Note: Modified from https://www.lemoda.net/c/levenshtein/
 */
int editDistance (const char * word1,const char * word2){
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}