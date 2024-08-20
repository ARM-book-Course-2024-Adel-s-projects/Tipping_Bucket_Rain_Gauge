#include <mbed.h>
#include <chrono>

static UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
static BufferedSerial sim800l(PE_8, PE_7, 9600);
char sim800l_response[100];
char at_command[100];

static void sendAtCommand(char*);
static void readStringUnbuffered(char*, UnbufferedSerial*);
static void readStringBuffered(char*, BufferedSerial*);
static void readSim800lResponse(void);
static void writeSerial(const char*, UnbufferedSerial*);

static void writeSerial(const char* message, UnbufferedSerial* serial) {
    int stringLength;
    stringLength = strlen(message);
    serial->write(message, stringLength);
}

static void readStringUnbuffered(char* str, UnbufferedSerial *serial) {
    int strIndex = 0;
    char byte;
    while(true) {
        serial->read(&byte, 1);

        if(byte == '\n') {
            str[strIndex] = '\n';
            str[strIndex + 1] = '\0';
            break;
        }

        if(strIndex < 99) {
            str[strIndex++] = byte;
        }
    }
}

static void readStringBuffered(char* str, BufferedSerial *serial) {
    int strIndex = 0;
    char byte;
    while(true) {
        serial->read(&byte, 1);

        if(byte == '\n') {
            str[strIndex] = '\n';
            str[strIndex + 1] = '\0';
            break;
        }

        if(strIndex < 99) {
            str[strIndex++] = byte;
        }
    }
}

void readSim800lResponse() {
    if(sim800l.readable()) {
        readStringBuffered(sim800l_response, &sim800l);
        uartUsb.write(sim800l_response, strlen(sim800l_response));
    } else {
        writeSerial("No response received yet...\n", &uartUsb);
    }
}

int main() {
    while(true) {
        if(uartUsb.readable()) {
            readStringUnbuffered(at_command, &uartUsb);
            sendAtCommand(at_command);
            
            thread_sleep_for(1000);
            
            readSim800lResponse();    
        } else if (sim800l.readable()) {
            readSim800lResponse();
        }
    }
}

void sendAtCommand(char* command) {
    sim800l.write(command, strlen(command));
    sim800l.write("\r\n", 2);

    if (strstr(command, "CIPSEND") != NULL) {
        char ctrlZ = 0x1A;
        sim800l.write(&ctrlZ, 1);
        sim800l.write("\r\n", 2);
    }

    writeSerial("Sent: ", &uartUsb);
    uartUsb.write(command, strlen(command));
}