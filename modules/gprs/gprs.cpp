#include "gprs.h"

static void ping(void);
static void waitPingResponse(gprs_t*);
static void checkSignalQuality(gprs_t*);

static UnbufferedSerial gprsSerial(USBTX, USBRX, 9600);

void updateGprs(gprs_t *gprsModule) {
    switch(gprsModule->state) {

        case INITIAL_STATUS:
            ping();
            gprsModule->state = WAITING_FOR_PING_RESPONSE;
            break;

        case WAITING_FOR_PING_RESPONSE:
            waitPingResponse(gprsModule);
            break;
        
        case REQUESTING_SIGNAL_QUALITY:
            checkSignalQuality(gprsModule);
            break;
    }
}

void initGprs(gprs_t *gprsModule) {
    gprsModule->state = INITIAL_STATUS;
}

void ping() {
    gprsSerial.write(AT);
}

void waitPingResponse(gprs_t *gprsModule) {
    char expectedResponse[] = "OK";

    gprsModule->state = INITIAL_STATUS;

    if (gprsSerial.readable()) {
        char response[] = gprsSerial.read();
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule->state = REQUESTING_SIGNAL_QUALITY;
        }
    }
}

void checkSignalQuality(gprs_t *gprsModule) {

}