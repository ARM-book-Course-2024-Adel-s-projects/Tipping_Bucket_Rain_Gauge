#include "tipping_bucket_rain_gauge.h"

static void sendTestMessage(void);

static Ticker gprsUpdater;
static Ticker dataSender;

void initTippingBucketRainGauge(void) {
    initRainGauge();
    initGprs();
    startConnection();
    
    gprsTicker.attach(&updateGprs, 1.0);
    dataSender.attach(&sendTestMessage, 60.0);
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