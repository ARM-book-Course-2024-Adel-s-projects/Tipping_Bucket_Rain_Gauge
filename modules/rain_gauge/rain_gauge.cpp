//=====[Includes]=============================================================

#include "rain_gauge.h"

//=====[Macros]===============================================================

#define REED_SWITCH_PIN D0

//=====[Private Variables]====================================================

static Debouncer_t reedSwitchDebouncer = {true, DigitalIn(REED_SWITCH_PIN), UP};
static RainGauge_t rainGauge;
static RainGauge_t lastRegistrations[MAX_AMOUNT_OF_REGISTERS];
static uint8_t registrationsIndex;

//=====[Functions Implementation]=============================================

void initRainGauge() {
    rainGauge.accumulatedRain = 0;
    rainGauge.epochTime = time(NULL);
    registrationsIndex = 0;
    initDebouncer(&reedSwitchDebouncer);
}

void saveRainMeasure() {
    lastRegistrations[registrationsIndex] = rainGauge;
    registrationsIndex = ++registrationsIndex % MAX_AMOUNT_OF_REGISTERS;
}

void resetRainGauge() {
    rainGauge.accumulatedRain = 0;
    rainGauge.epochTime = time(NULL);
}

void updateRainMeasure() {
    updateDebouncer(&reedSwitchDebouncer);
    if(!reedSwitchDebouncer.isADebounce){
        if(isSameDate()) {
            rainGauge.accumulatedRain++;
        } else {
            saveRainMeasure();
            resetRainGauge();
        }
    }
}

unsigned int getAccumulatedRain() {
    return rainGauge.accumulatedRain;
}

bool isSameDate() {
    time_t timeNow = time(NULL);
    return ((rainGauge.epochTime / SECONDS_IN_A_DAY) == (rainGauge.epochTime / SECONDS_IN_A_DAY));
}

RainGauge_t getCurrentDayRain() {
    return rainGauge;
}

RainGauge_t* getAllRegistrations() {
    return lastRegistrations;
}