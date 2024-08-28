#include "tipping_bucket_rain_gauge.h"

static void sendTestMessage(void);

static Ticker dataSender;
static Ticker gprsUpdater;
static Ticker gpsUpdater;

void initTippingBucketRainGauge(void) {
    initRainGauge();
    initGprs();
    startConnection();
    
    dataSender.attach(&sendTestMessage, SERVER_UPDATE_TIME_IN_SECONDS);
    gpsUpdater.attach(&getGpsPosition, UPDATE_GPS_TIME_IN_SECONDS);
    gprsUpdater.attach(&updateGprs, UPDATE_GPRS_TIME_IN_SECONDS);
}

void updateTippingBucketRainGauge(void) {
    updateRainMeasure();
    uartTask();
}

void sendTestMessage(void) {
    unsigned int rain = getAccumulatedRain();
    char str[12];

    sprintf(str, "%d", rain);
    sendData(str);
}