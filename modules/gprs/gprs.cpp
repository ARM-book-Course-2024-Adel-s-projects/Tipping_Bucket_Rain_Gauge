#include "gprs.h"
#include "serial_interface.h"

static void ping(void);
static void waitPingResponse(void);
static void getSignalQuality(void);
static void checkSignalQuality(void);
static void getNetworkRegistrationStatus(void);
static void checkNetworkRegistrationStatus(void);
static void readString(char*);

static BufferedSerial gprsSerial(PE_8, PE_7, 9600);

gprs_t gprsModule;

void updateGprs() {
    switch(gprsModule.state) {

        case INITIAL_STATUS:
            ping();
            break;

        case WAITING_FOR_PING_RESPONSE:
            waitPingResponse();
            break;
        
        case REQUESTING_SIGNAL_QUALITY:
            getSignalQuality();
            break;
        
        case ANALYZING_SIGNAL_QUALITY:
            checkSignalQuality();
            break;
        
        case REQUESTING_NETWORK_REGISTRATION_STATUS:
            getNetworkRegistrationStatus();
            break;
        
        case ANALYZING_NETWORK_REGISTRATION_STATUS:
            checkNetworkRegistrationStatus();
            break;
    }
}

void initGprs() {
    gprsModule.state = INITIAL_STATUS;
}

static void ping(void) {
    gprsModule.state = WAITING_FOR_PING_RESPONSE;

    gprsSerial.write(AT, sizeof(AT));

    #ifdef LOG
    logMessage("SENDING PING");
    #endif
}

static void waitPingResponse(void) {
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

static void getSignalQuality(void) {
    gprsModule.state = ANALYZING_SIGNAL_QUALITY;
    gprsSerial.write(CSQ, sizeof(CSQ));

    #ifdef LOG
    logMessage("GETTING SIGNAL QUALITY");
    #endif
}

static void checkSignalQuality(void) {
    char expectedResponse[] = "OK";

    gprsModule.state = INITIAL_STATUS;

    if (gprsSerial.readable()) {
        
        char response[MAX_RESPONSE_LENGTH];
        readString(response);
        
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule.state = REQUESTING_NETWORK_REGISTRATION_STATUS;

            #ifdef LOG
            logMessage("REQUESTING NETWORK REGISTRATION STATUS");
            #endif
        }
    }
}

static void getNetworkRegistrationStatus(void) {
    gprsModule.state = ANALYZING_NETWORK_REGISTRATION_STATUS;
    gprsSerial.write(CREG, sizeof(CREG));

    #ifdef LOG
    logMessage("ANALYZING NETWORK REGISTRATION STATUS");
    #endif
}

static void checkNetworkRegistrationStatus(void) {
    char expectedResponse[] = "OK";

    gprsModule.state = INITIAL_STATUS;

    if (gprsSerial.readable()) {
        
        char response[MAX_RESPONSE_LENGTH];
        readString(response);
        
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule.state = SETTING_FULL_OPERATION_MODE;

            #ifdef LOG
            logMessage("SETTING FULL OPERATION MODE");
            #endif
        }
    }

    #ifdef LOG
    logMessage("SETTING FULL OPERATION MODE");
    #endif
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
