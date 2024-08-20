#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include "gprs.h"
#include <mbed.h>

#define SECOND 1000

int tick_counter = 0;

int main() {
    initRainGauge();
    initGprs();
    while (true) {
        updateRainMeasure();
        uartTask();
        if (tick_counter++ >= SECOND) {
            updateGprs();
            tick_counter = 0;
        }
        thread_sleep_for(DELAY_TIME);
    }
}
