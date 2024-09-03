#include "tipping_bucket_rain_gauge.h"

static void sendTestMessage(void);
static void checkGprsConnection(void);

static Ticker dataSender;
static Ticker gprsUpdater;
static Ticker gprsConnectionChecker;

static position_t pos = {0.0, 0.0};
static bool systemDateTimeSet = false;

void initTippingBucketRainGauge(void) {
    initRainGauge();
    initGprs();
    startConnection();
    
    dataSender.attach(&sendTestMessage, SERVER_UPDATE_TIME_IN_SECONDS);
    gprsUpdater.attach(&updateGprs, UPDATE_GPRS_TIME_IN_SECONDS);
    gprsConnectionChecker.attach(&checkGprsConnection, 300.0);
}

void updateTippingBucketRainGauge(void) {
    setSystemDateAndTime();
    updateDateAndTime();    
    pos = getGpsPosition();
    updateRainMeasure();
    uartTask();
}

static void sendTestMessage(void) {
    if(readyToSendData()) {
        unsigned int rain = getAccumulatedRain();
        DateTime_t dateTime = getDateTimeFromEpoch(getCurrentDayRain().epochTime);

        char str[200];

        sprintf(str, "Acumulated rain: %d\n\nLat= %lf, Lon=%lf\n\nDate: %d/%d/%d %d:%d:%d", rain, pos.lat, pos.lon, dateTime.day, dateTime.month, dateTime.year, dateTime.hour, dateTime.minute, dateTime.second);
        sendData(str);
    }
}

static void checkGprsConnection(void) {
    if (!readyToSendData()) {
        startConnection();
    }
}