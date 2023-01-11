#include "main.h"

static void display_time(uint32_t);
static void display_message(String);
static void do_beep(void);
static void display_clear(void);

static event_status_t protimer_state_handler_IDLE(protimer_t * const mobj, event_t * const e);
static event_status_t protimer_state_handler_TIME_SET(protimer_t * const mobj, event_t * const e);
static event_status_t protimer_state_handler_STAT(protimer_t * const mobj, event_t * const e);
static event_status_t protimer_state_handler_COUNTDOWN(protimer_t * const mobj, event_t * const e);
static event_status_t protimer_state_handler_PAUSE(protimer_t * const mobj, event_t * const e);

void protimer_init(protimer_t *mobj) {
    mobj->active_state = IDLE;
    mobj->pro_time = 0;
}

event_status_t protimer_state_machine (protimer_t *mobj, event_t *e){
    switch (mobj->active_state)
    {
        case IDLE:{
            return protimer_state_handler_IDLE(mobj, e);
        }
        case TIME_SET: {
            return protimer_state_handler_TIME_SET(mobj, e);
        }
        case STAT: {
            return protimer_state_handler_STAT(mobj, e);
        }
        case COUNTDOWN: {
            return protimer_state_handler_COUNTDOWN(mobj, e);
        }
        case PAUSE: {
            return protimer_state_handler_PAUSE(mobj, e);
        }
    }//END OF SWITCH

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_IDLE(protimer_t * const mobj, event_t * const e){
    switch (e->sig)
    {
        case ENTRY:{
            mobj->curr_time = 0;
            mobj->elapsed_time = 0;
            display_time(0);
            display_message("Set time");
            return EVENT_HANDLED;

        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;

        }
        case INC_TIME:{
            mobj->curr_time += 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSITION;
        }
        case START_PAUSE:{
            mobj->active_state = STAT;
            return EVENT_TRANSITION;
        }
        case TIME_TICK:{
            if(((protimer_tick_event_t *)(e))->ss == 5){
                do_beep();
                return EVENT_HANDLED;
            }

            return EVENT_IGNORED;

        }                
    }// END OF SWITCH

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_TIME_SET(protimer_t * const mobj, event_t * const e){
    switch (e->sig)
    {
        case ENTRY:{
            display_time(mobj->curr_time);
            return EVENT_HANDLED;
        }
        case EXIT:{
            display_clear();
            return EVENT_HANDLED;
        }
        case INC_TIME:{
            mobj->curr_time += 60;
            display_time(mobj->curr_time);
            return EVENT_HANDLED;
        }
        case DEC_TIME:{
            if (mobj->curr_time >= 60){
                mobj->curr_time -=60;
                display_time(mobj->curr_time);
                return EVENT_HANDLED;
            }

        }
        case START_PAUSE:{
            if (mobj->curr_time >= 60){
                mobj->active_state = COUNTDOWN;
            }
            return EVENT_TRANSITION;
        }
        case ABRT:{
            mobj->active_state = IDLE;
            return EVENT_TRANSITION;
        }
    }//END OF SWITCH

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_STAT(protimer_t * const mobj, event_t * const e){

    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_COUNTDOWN(protimer_t * const mobj, event_t * const e){
    return EVENT_IGNORED;
}

static event_status_t protimer_state_handler_PAUSE(protimer_t * const mobj, event_t * const e){
    return EVENT_IGNORED;
}

//////////////////////// Helper functions //////////////////
static void display_time(uint32_t){

}

static void display_message(String){

}

static void do_beep(void){
    
}

static void display_clear(void){

}