#include "gps.h"

static position_t getPosition(void);

static BufferedSerial gpsSerial(D53, D52, 9600);
static TinyGPSPlus gps;

position_t getGpsPosition(void) {

    if(gpsSerial.readable()) {
        char c;
        gpsSerial.read(&c, 1);

        if(gps.encode(c))
          return getPosition();
    }
}

static position_t getPosition(void) {
    position_t position = { 0.0, 0.0 };
    if (gps.location.isValid()) {
        char str[50];
        double lat = gps.location.lat();
        double lon = gps.location.lng();

        position.lat = lat;
        position.lon = lon;
    }
    return position;
}
