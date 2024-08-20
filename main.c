#include <mbed.h>

static UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
static UnbufferedSerial sim800l(PE_8, PE_7, 9600);
char sim800l_response[100];
char at_command[100];

static void sendAtCommand(char*);
static void readString(char*, UnbufferedSerial);
static void readSim800lResponse(void);

static void readString(char* str, UnbufferedSerial serial) {
    int strIndex = 0;
    char byte;
    while(true) {
        serial.read(&byte, 1);

        if(byte == '\n') {
            str[strIndex] = '\n';
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
        readString(sim800l_response, sim800l);
        uartUsb.write(sim800l_response);
    } else {
        uartUsb.write("No response received yet...\n");
    }
}

int main() {
    while(true) {
        if(uartUsb.readable()) {
            readString(at_command, uartUsb);
            sendAtCommand(at_command);
            
            thread_sleep_for(1000);
            
            readSim800lResponse();    
        }
    }
}

void sendAtCommand(char* command) {
    sim800l.write(command);

    if (strstr(command, "CIPSEND") != NULL) {
        sim800l.write(0x1A);
    }

    uartUsb.write("Sent: ");
    uartUsb.write(command);
}