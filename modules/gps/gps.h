#ifndef _GPS_
#define _GPS_

#include "TinyGPSPlus.h"
#include "serial_interface.h"
#include "date_and_time.h"

#define LOG

typedef struct position {
    double lat;
    double lon;
} position_t;

void initGps(void);
bool setSystemDateAndTime(void);
position_t getGpsPosition(void);

#endif