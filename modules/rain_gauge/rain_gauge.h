//=====[Include Guards - Begin]===============================================

#ifndef _RAIN_GAUGE_
#define _RAIN_GAUGE_

//=====[Includes]=============================================================

#include "debouncer.h"
#include "date_and_time.h"
#include "mbed.h"
#include <ctime>

//=====[Macros]===============================================================

#define MAX_AMOUNT_OF_REGISTERS 100
#define SECONDS_IN_A_DAY 86400

//=====[Public Data Types]====================================================

/** \struct RainGauge
*
* @brief Holds information about the accumulated rain and the date of
* registration
*/
typedef struct RainGauge {
    unsigned int accumulatedRain;
    time_t epochTime;
} RainGauge_t;

//=====[Function Declarations]================================================

/**
* @brief Inits the rain gauge with accumulatedRain in 0 and the current epoch time.
* It also inits the debouncer.
*/
void initRainGauge(void);

/**
* @brief Updates the global rain gauge accumulated rain.
* If the date changes, the rain gauge is reseted and the previous register is saved.
*/
void updateRainMeasure(void);

/**
* @brief Saves a rain gauge struct in the last registrations array.
* @warning This function should be converted to private.
*/
void saveRainMeasure(void);

/**
* @brief Resets the rain gauge accumulatedRain to 0 and sets the current date as epoch time.
*/
void resetRainGauge(void);

/**
* @brief Gets the accumulated rain of the rain gauge.
* @returns The number of tips that the bucket made (not millimeters).
* @warning It needs to be updated to the amount of millimeters. Maybe it would be
* @warning a good idea if we create another function called getAccumulatedBucketTips.
*/
unsigned int getAccumulatedRain(void);

/**
* @brief This function checks if the rain gauge is registering rainfall in the same day.
* @returns True if the rain gauge is registering rainfall during the same date, else false.
* @warning This function should be converted to private.
*/
bool isSameDate(void);

/**
* @brief Returns the last 100 registrations.
* @returns RainGauge_t* an array of rain registrations (each one corresponding
* with a different date)
* @warning It needs to be refactored to analyze only the registers with more
* @warning than 0 millimeters of rainfall.
*/
RainGauge_t* getAllRegistrations(void);

/**
* @brief Gets the current day rainfall information.
* @returns A RainGauge_t struct with the information of the current day rainfall.
*/
RainGauge_t getCurrentDayRain(void);

//=====[Include Guards - End]=================================================

#endif