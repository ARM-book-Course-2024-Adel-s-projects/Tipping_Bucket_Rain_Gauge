#ifndef _GPS_
#define _GPS_

#include "TinyGPSPlus.h"
#include "serial_interface.h"

#define LOG

typedef struct {
    double lat;
    double lon;
} position_t;

void initGps(void);
position_t getGpsPosition(void);

#endif