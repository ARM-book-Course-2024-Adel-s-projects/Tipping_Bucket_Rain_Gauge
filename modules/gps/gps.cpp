#include "gps.h"

static void displayInfo(void);

static BufferedSerial gpsSerial(PG_14, PG_9, 4800);
static TinyGPSPlus gps;

void getGpsPosition(void) {

    if(gpsSerial.readable()) {
        char c;
        gpsSerial.read(&c, 1);

        if(gps.encode(c))
            displayInfo();
    }
}

static void displayInfo(void) {
    if (gps.location.isValid()) {
        char str[50];
        double lat = gps.location.lat();
        double lng = gps.location.lng();

        sprintf(str, "LAT=%lf, LON=%lf", lat, lng);
        logMessage(str);
    }
}
