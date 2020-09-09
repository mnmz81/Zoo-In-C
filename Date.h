#ifndef DATE_H_
#define DATE_H_

typedef struct Date{
    int day;
    int month;
    int year;
}Date;

void dateCopy(Date* a,Date* b);

    
#endif