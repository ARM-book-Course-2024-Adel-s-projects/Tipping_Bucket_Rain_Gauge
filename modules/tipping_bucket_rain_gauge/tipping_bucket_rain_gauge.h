#ifndef TIPPING_BUCKET_RAIN_GAUGE
#define TIPPING_BUCKET_RAIN_GAUGE

#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include "gprs.h"
#include <mbed.h>

void initTippingBucketRainGauge(void);
void updateTippingBucketRainGauge(void);

#endif