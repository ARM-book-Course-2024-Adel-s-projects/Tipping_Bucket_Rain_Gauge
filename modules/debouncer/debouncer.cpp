//=====[Includes]=============================================================

#include "debouncer.h"

//=====[Functions Implementation]=============================================

void updateDebouncer(Debouncer_t* debouncer) {
    debouncer->isADebounce = true;
    
    switch(debouncer->currentState) {

        case UP:
            if(debouncer->input.read()) {
                debouncer->currentState = FALLING;
                debouncer->timer_accumulator = 0;
            }
            break;
        
        case FALLING:
            if((debouncer->timer_accumulator * DELAY_TIME) >= DEBOUNCER_TIME_MS){
                if(!debouncer->input.read()) {
                    debouncer->currentState = DOWN;
                } else {
                    debouncer->currentState = UP;
                }
            }
            debouncer->timer_accumulator++;
            break;
        
        case DOWN:
            if(!debouncer->input.read()) {
                debouncer->currentState = RISING;
                debouncer->timer_accumulator = 0;
            }
            break;
        
        case RISING:
            if((debouncer->timer_accumulator * DELAY_TIME) >= DEBOUNCER_TIME_MS) {
                if(debouncer->input.read()) {
                    debouncer->currentState = UP;
                    debouncer->isADebounce = false;
                } else {
                    debouncer->currentState = DOWN;
                }
            }
            debouncer->timer_accumulator++;
            break;
    }
}

void initDebouncer(Debouncer_t* debouncer) {
    if(debouncer->input.read()) {
        debouncer->currentState = UP;
    } else {
        debouncer->currentState = DOWN;
    }

    debouncer->input.mode(PullUp);
    debouncer->timer_accumulator = 0;
    debouncer->isADebounce = true;
}