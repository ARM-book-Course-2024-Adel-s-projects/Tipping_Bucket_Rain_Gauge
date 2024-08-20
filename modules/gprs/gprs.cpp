#include "gprs.h"
#include "serial_interface.h"

static void ping(void);
static void waitPingResponse(void);
static void getSignalQuality(void);
static void checkSignalQuality(void);
static void getNetworkRegistrationStatus(void);
static void checkNetworkRegistrationStatus(void);
static void setFullOperationMode(void);
static void checkFullOperationModeValue(void);
static void getSimAvailability(void);
static void checkSimAvailability(void);
static void readString(char*);

static BufferedSerial gprsSerial(PE_8, PE_7, 9600);

gprs_t gprsModule;

void updateGprs() {
    switch(gprsModule.state) {

        case DISCONNECTED:
            break;
        
        case PING:
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
        
        case SETTING_FULL_OPERATION_MODE:
            setFullOperationMode();
            break;
        
        case ANALYZING_FULL_OPERATION_MODE_VALUE:
            checkFullOperationModeValue();
            break;

        case REQUESTING_SIM_AVAILABILITY:
            getSimAvailability();
            break;
        
        case ANALYZING_SIM_AVAILABILITY:
            checkSimAvailability();
            break;
    }
}

void initGprs(void) {
    gprsModule.state = DISCONNECTED;
}

void startConnection(void) {
    gprsModule.state = PING;
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
    char expectedResponse[] = "+CSQ";

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
    char expectedResponse[] = "+CREG";

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
}

static void setFullOperationMode(void) {
    gprsModule.state = ANALYZING_FULL_OPERATION_MODE_VALUE;
    gprsSerial.write(CFUN1, sizeof(CFUN1));

    #ifdef LOG
    logMessage("ANALYZING FULL OPERATION MODE VALUE");
    #endif
}

static void checkFullOperationModeValue(void) {
    char expectedResponse[] = "CFUN=1";

    if (gprsSerial.readable()) {
        
        char response[MAX_RESPONSE_LENGTH];
        readString(response);
        
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule.state = REQUESTING_SIM_AVAILABILITY;

            #ifdef LOG
            logMessage("REQUESTING SIM AVAILABILITY");
            #endif
        }
    }
}

static void getSimAvailability(void) {
    gprsModule.state = ANALYZING_SIM_AVAILABILITY;
    gprsSerial.write(CPIN, sizeof(CPIN));

    #ifdef LOG
    logMessage("ANALYZING SIM AVAILABILITY");
    #endif
}

static void checkSimAvailability(void) {
    char expectedResponse[] = "READY";

    if (gprsSerial.readable()) {
        
        char response[MAX_RESPONSE_LENGTH];
        readString(response);
        
        if(strstr(response, expectedResponse) != NULL) {
            gprsModule.state = REGISTERING_TO_APN;

            #ifdef LOG
            logMessage("REGISTERING TO APN");
            #endif
        }
    }
}

bool getConnectionState(void) {
    return (gprsModule.state == DISCONNECTED) ? false : true;
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
