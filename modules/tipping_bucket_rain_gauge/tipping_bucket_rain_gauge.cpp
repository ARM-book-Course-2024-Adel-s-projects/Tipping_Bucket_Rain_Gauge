#include "tipping_bucket_rain_gauge.h"

static void sendTestMessage(void);

static Ticker dataSender;
static Ticker gprsUpdater;
static systemDateTimeSet = false;

void initTippingBucketRainGauge(void) {
    initRainGauge();
    initGprs();
    startConnection();
    
    dataSender.attach(&sendTestMessage, SERVER_UPDATE_TIME_IN_SECONDS);
    gprsUpdater.attach(&updateGprs, UPDATE_GPRS_TIME_IN_SECONDS);
}

void updateTippingBucketRainGauge(void) {
    if (!systemDateTimeSet && setSystemDateAndTime()) {
        updateDateAndTime();
        systemDateTimeSet = true;
    }
    updateRainMeasure();
    uartTask();
}

void sendTestMessage(void) {
    unsigned int rain = getAccumulatedRain();
    position_t pos = getGpsPosition();

    char str[100];

    sprintf(str, "Acumulated rain: %d\n\nLat= %lf, Lon=%lf", rain, pos.lat, pos.lon);
    sendData(str);
}