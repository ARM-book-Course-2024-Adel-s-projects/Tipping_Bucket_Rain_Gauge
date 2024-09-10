//=====[Include Guards - Begin]===============================================

#ifndef _DATE_AND_TIME_
#define _DATE_AND_TIME_

//=====[Includes]=============================================================

#include "mbed.h"

//=====[Public Data Types]====================================================

/** \struct RainGauge
*
* @brief This struct helps to easly manage the date and time when needed.
*
*/
typedef struct DateTime {
    int year;
    int day;
    int month;
    int hour;
    int minute;
    int second;
} DateTime_t;

//=====[Function Declarations]================================================

/**
* @brief Get the current date and time as epoch
* @return A time_t (epoch time)
*/
time_t getEpochTime(void);

/**
* @brief Get a string with the current date and time.
* @return A string with the current date and time.
*/
char* getDateAndTime(void);

/**
* @brief Set the date and time of the system.
* @param year An integer representing the year.
* @param month An integer representing the month.
* @param day An integer representing the day.
* @param hour An integer representing the hour.
* @param minute An integer representing the minute.
* @param second An integer representing the second.
*/
void setDateAndTime(int year, int month, int day,
                    int hour, int minute, int second);

/**
* @brief Get a DateTime_t object from an epoch.
* @return A DateTime_t object to easly handle the date and time.
* @param epoch A time_t representing the date and time in epoch.
*/
DateTime_t getDateTimeFromEpoch(time_t epoch);

//=====[Include Guards - End]=================================================

#endif