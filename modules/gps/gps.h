#ifndef _GPS_
#define _GPS_

#include "TinyGPS++.h"
#include "serial_interface.h"

#define LOG

void initGps(void);
void getGpsPosition(void);

#endif