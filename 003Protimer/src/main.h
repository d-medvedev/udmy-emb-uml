#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

typedef enum {
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    START_PAUSE,
    ABRT,
    ENTRY,
    EXIT
}protimer_signal_t;

typedef enum{
    IDLE,
    TIME_SET,
    COUNTDOWN,
    PAUSE,
    STAT
}protimer_state_t;

typedef struct
{
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
}protimer_t;

typedef struct
{
    uint8_t sig;
}event_t;

typedef struct
{
    event_t super;

}protimer_user_event_t;

typedef struct
{
    event_t super;
    uint8_t ss;

}protimer_tick_event_t;

void protimer_init(protimer_t *mobj);

#endif