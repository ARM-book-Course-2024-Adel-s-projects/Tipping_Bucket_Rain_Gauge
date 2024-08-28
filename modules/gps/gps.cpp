#include "gps.h"

static void readString(char* str);

static BufferedSerial gpsSerial(PG_14, PG_9, 4800);
static TinyGPS gps;

void getGpsPosition(void) {
    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;

    if(gpsSerial.readable()) {
        char c = gpsSerial.read();

        if(gps.encode(c))
            newData = true;
    }

    if (newData) {
        float flat, flon;
        unsigned int sat;
        unsigned int hdop;
        unsigned long age;

        gps.f_get_position(&flat, &flon, &age);

        #ifdef LOG
        char str[50];
        flat = (flat == TinyGPS::GPS_INVALID_ANGLE) ? 0.0 : flat;
        sprintf(str, "LAT=%f", flat);
        logMessage(str);

        flon = (flon == TinyGPS::GPS_INVALID_ANGLE) ? 0.0 : flon;
        sprintf(str, "LON=%f", flon);
        logMessage(str);

        sat = (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES) ? 0 : gps.satellites();
        sprintf(str, "SAT=%d", sat);
        logMessage(str);

        hdop = (gps.hdop() == TinyGPS::GPS_INVALID_HDOP) ? 0 : gps.hdop();
        sprintf(str, "HDOP=%d", hdop);
        logMessage(str);
        #endif
    }
}
