#ifndef FSM_H
#define FSM_H

#include "backend.h"

#define ENTER_KEY 10

typedef enum
{
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

UserAction_t get_signal(UserAction_t user_input);
void sigact(UserAction_t sig, GameInfo_t *brick_game);
void on_start_state(GameInfo_t *brick_game);
void on_action_state(GameInfo_t *brick_game);

#endif