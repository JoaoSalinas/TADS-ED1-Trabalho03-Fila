
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

typedef struct date{
    int day;
    int month;
    int year;    
} Date;


typedef struct time{
    int hours;
    int minutes;
    int seconds;
}Time;

Date* createDate();
Time* createTime();

int dayOfWeekString(Date* date);
int fullMonthString(int month);
int fullDateString(Date* date);

int validateTime(Time* time);

int validateDate(Date* date);
int validateYear(int year);
int validateMonth(int month);
int validateDay(Date* date);
int lastDayOfMonth(Date* date);
int leapYear(int year);

int dateCompare(Date* firstDate, Date* secondDate);
int timeCompare(Time* firstTime, Time* secondTime);

