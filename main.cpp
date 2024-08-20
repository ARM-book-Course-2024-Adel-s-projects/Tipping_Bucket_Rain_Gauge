#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include "gprs.h"
#include <mbed.h>

int main() {
    initRainGauge();
    initGprs();
    while (true) {
        updateRainMeasure();
        uartTask();
        updateGprs();
        thread_sleep_for(DELAY_TIME);
    }
}
