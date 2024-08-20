#include <mbed.h>
#include <chrono>

static UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
static UnbufferedSerial sim800l(PE_8, PE_7, 9600);
char sim800l_response[100];
char at_command[100];

static void sendAtCommand(char*);
static void readString(char*, UnbufferedSerial*);
static void readSim800lResponse(void);
static void writeSerial(const char*, UnbufferedSerial*);

static void writeSerial(const char* message, UnbufferedSerial* serial) {
    int stringLength;
    stringLength = strlen(message);
    serial->write(message, stringLength);
}

static void readString(char* str, UnbufferedSerial *serial) {
    int strIndex = 0;
    char byte;
    while(true) {
        serial->read(&byte, 1);

        if(byte == '\n') {
            str[++strIndex] = '\n';
            str[strIndex + 1] = '\0';
            break;
        }

        if(strIndex < sizeof(str) - 1) {
            str[strIndex++] = byte;
        }
    }
}

void readSim800lResponse() {
    if(sim800l.readable()) {
        readString(sim800l_response, &sim800l);
        uartUsb.write(sim800l_response, strlen(sim800l_response));
    } else {
        writeSerial("No response received yet...\n", &uartUsb);
    }
}

int main() {
    while(true) {
        if(uartUsb.readable()) {
            readString(at_command, &uartUsb);
            sendAtCommand(at_command);
            
            thread_sleep_for(1000);
            
            readSim800lResponse();    
        }
    }
}

void sendAtCommand(char* command) {
    sim800l.write(command, strlen(command));

    if (strstr(command, "CIPSEND") != NULL) {
        char ctrlZ = 0x1A;
        sim800l.write(&ctrlZ, 1);
    }

    writeSerial("Sent: ", &uartUsb);
    uartUsb.write(command, strlen(command));
}