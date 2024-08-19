#include "debouncer.h"
#include "rain_gauge.h"
#include "serial_interface.h"
#include <mbed.h>

int main() {
    initRainGauge();
    while (true) {
        updateRainMeasure();
        uartTask();  
        thread_sleep_for(DELAY_TIME);
    }
}
