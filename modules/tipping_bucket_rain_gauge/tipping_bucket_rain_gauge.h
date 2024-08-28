#ifndef TIPPING_BUCKET_RAIN_GAUGE
#define TIPPING_BUCKET_RAIN_GAUGE

#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include "gprs.h"
#include <mbed.h>

#define UPDATE_GPRS_TIME_IN_SECONDS 1.0
#define SERVER_UPDATE_TIME_IN_SECONDS 60.0

void initTippingBucketRainGauge(void);
void updateTippingBucketRainGauge(void);

#endif