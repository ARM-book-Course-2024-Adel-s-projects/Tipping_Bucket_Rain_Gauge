#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include "gprs.h"
#include <mbed.h>

#define SECOND 2000

int tick_counter = 0;

int main() {
    initRainGauge();
    initGprs();
    thread_sleep_for(2000);
    startConnection();
    while (true) {
        updateRainMeasure();
        uartTask();
        if (tick_counter++ >= SECOND) {
            if (!getConnectionState()) {
                startConnection();
                thread_sleep_for(2000);
            }
            updateGprs();
            tick_counter = 0;
        }
        thread_sleep_for(DELAY_TIME);
    }
}
