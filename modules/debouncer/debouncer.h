//=====[Include Guards - Begin]===============================================

#ifndef _DEBOUNCER_
#define _DEBOUNCER_

//=====[Includes]=============================================================

#include "mbed.h"

//=====[Macros]===============================================================

#define DEBOUNCER_TIME_MS 50
#define DELAY_TIME 1

//=====[Public Data Types]====================================================

/** \enum state_t
*
* @brief Represents the state of the debouncer FSM.
*
*/
typedef enum {
    DOWN,
    FALLING,
    RISING,
    UP,
} state_t;

/** \struct Debouncer
*
* @brief Holds information needed for the debouncer.
*
*/
typedef struct Debouncer {
    bool isADebounce;
    DigitalIn input;
    state_t currentState;
    uint8_t timer_accumulator;
} Debouncer_t;

//=====[Function Declarations]================================================

/**
* @brief Updates the FSM of the debouncer.
* @param debouncer Receives a Debouncer_t that needs to be updated.
*/
void updateDebouncer(Debouncer_t*);

/**
* @brief Initializes the debouncer.
* @param debouncer Receives a Debouncer_t that needs to be initialized.
*/
void initDebouncer(Debouncer_t*);

//=====[Include Guards - End]=================================================

#endif