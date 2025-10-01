#ifndef FSM_H
#define FSM_H

#include "backend.h"

#define ENTER_KEY 10
#define ESCAPE 27
#define KEY_UP 259
#define KEY_LEFT 260
#define KEY_RIGHT 261

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
void on_left_state(GameInfo_t *brick_game);
void on_right_state(GameInfo_t *brick_game);
void on_down_state(GameInfo_t *brick_game);
// void on_rotate_state(GameInfo_t *brick_game);

#endif