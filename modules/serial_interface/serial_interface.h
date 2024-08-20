//=====[Include Guards - Begin]===============================================

#ifndef _SERIAL_INTERFACE_
#define _SERIAL_INTERFACE_

//=====[Includes]=============================================================

#include "rain_gauge.h"
#include "date_and_time.h"

//=====[Function Declarations]================================================

void uartTask(void);
void logMessage(char*);

//=====[Include Guards - End]=================================================

#endif