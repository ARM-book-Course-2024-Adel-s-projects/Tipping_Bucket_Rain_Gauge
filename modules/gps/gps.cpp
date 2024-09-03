#include "gps.h"

static position_t getPosition(void);
static void setDate(void);

static BufferedSerial gpsSerial(D53, D52, 9600);
static TinyGPSPlus gps;

position_t getGpsPosition(void) {

    if(gpsSerial.readable()) {
        char c;
        gpsSerial.read(&c, 1);

        if(gps.encode(c))
          return getPosition();
    }

    return (position_t){0.0, 0.0};
}

bool setSystemDateAndTime(void) {
    if(gpsSerial.readable()) {
        char c;
        gpsSerial.read(&c, 1);

        if(gps.encode(c)) {
            setDate();
            return true;  
        }
    }
    return false;
}

static position_t getPosition(void) {
    position_t position = { 0.0, 0.0 };
    if (gps.location.isValid()) {
        double lat = gps.location.lat();
        double lon = gps.location.lng();

        position.lat = lat;
        position.lon = lon;
    }
    return position;
}

static void setDate(void) {
    if (gps.date.isValid() && gps.time.isValid()) {
        int year = (int) gps.date.year();
        int month = (int) gps.date.month();
        int day = (int) gps.date.month();
        int hour = (int) gps.time.hour();
        int minute = (int) gps.time.minute();
        int second = (int) gps.time.second();

        setDateAndTime(year, month, day, hour, minute, second);
    }
}
