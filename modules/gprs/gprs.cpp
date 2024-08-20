#include "gprs.h"
#include "serial_interface.h"

static void ping(void);
static void waitPingResponse();
static void checkSignalQuality();
static void readString(char*);

static BufferedSerial gprsSerial(PE_8, PE_7, 9600);

gprs_t gprsModule;

void updateGprs() {
    switch(gprsModule.state) {

        case INITIAL_STATUS:
            ping();
            gprsModule.state = WAITING_FOR_PING_RESPONSE;
            break;

        case WAITING_FOR_PING_RESPONSE:
            waitPingResponse();
            break;
        
        case REQUESTING_SIGNAL_QUALITY:
            checkSignalQuality();
            break;
    }
}

void initGprs() {
    gprsModule.state = INITIAL_STATUS;
}

void ping() {
    gprsSerial.write(AT, sizeof(AT));

    #ifdef LOG
    logMessage("SENDING PING");
    #endif
}

void waitPingResponse() {
    char expectedResponse[] = "OK";

    gprsModule.state = INITIAL_STATUS;

    if (gprsSerial.readable()) {
        
        char response[MAX_RESPONSE_LENGTH];
        readString(response);
        
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule.state = REQUESTING_SIGNAL_QUALITY;

            #ifdef LOG
            logMessage("REQUESTING SIGNAL QUALITY");
            #endif
        }
    }
}

void checkSignalQuality() {
    
}

static void readString(char* str) {
    int strIndex = 0;
    char byte;
    while(true) {
        gprsSerial.read(&byte, 1);

        if(byte == '\n') {
            str[strIndex] = '\n';
            str[strIndex + 1] = '\0';
            break;
        }

        if(strIndex < MAX_RESPONSE_LENGTH) {
            str[strIndex++] = byte;
        }
    }
}