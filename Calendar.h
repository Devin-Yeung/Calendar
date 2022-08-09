#ifndef _CALENDAR_H_ 
#define _CALENDAR_H_ 
// define the maximum length of the event;
#define EVENTLEN 128
// define the fuzzy search size
#define SEARCHSIZE 5
// define the edit distance threshold
#define THRESHOLD 20





// Data Structure
typedef struct Event{
    char title[EVENTLEN];
    struct Event * next;
} Event;

typedef struct Day{
    Event * head;
} Day;

typedef struct Month{
    Day * days;
} Month;

typedef struct Calendar{
    Month * months;
    int year;
} Calendar;





// Data Operations
void initCalendar(int year, Calendar * calendar);
void destoryCalendar(Calendar * calendar);
void showMonth(int month, Calendar * calendar);
void addEvent(char* event, int month, int day, Calendar * calendar);
void delEvent(int eventId, int month, int day, Calendar * calendar);
int inquireEvents(int month, int day, Calendar * calendar);
void searchEvent(char * target, int * months, int * days,int * eventId, Calendar * calendar);





// Usr interface
int getMonthUI(void);
int getDayUI(int month);
void showMonthUI(Calendar * calendar);
void addEventUI(Calendar * calendar);
void delEventUI(Calendar * calendar);
void inquireEventsUI(Calendar * calendar);
void searchEventUI(Calendar * calendar);





// File operation
void readFile(Calendar * calendar);
void writeFile(Calendar * calendar);





// utils
_Bool s_getline(char * str, FILE * fp);
_Bool checkDay(int month, int day);
int extractDate(char * line);
void extractEvent(char * line, char * event);
int Zeller (int year, int month, int day);
int strMonth_to_numMonth(char * strMonth);
_Bool oneDigit(char * str);
void sort(int * arr,int len);
int editDistance (const char * word1, const char * word2);





#endif