#include "tipping_bucket_rain_gauge.h"

static void sendTestMessage(void);

static Ticker gprsUpdater;
static Ticker dataSender;

void initTippingBucketRainGauge(void) {
    initRainGauge();
    initGprs();
    startConnection();
    
    gprsUpdater.attach(&updateGprs, UPDATE_GPRS_TIME_IN_SECONDS);
    dataSender.attach(&sendTestMessage, SERVER_UPDATE_TIME_IN_SECONDS);
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