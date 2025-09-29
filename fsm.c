#include "backend.h"
#include "frontend.h"
#include "fsm.h"
#include <ncurses.h>

void sigact(UserAction_t sig, GameInfo_t *brick_game)
{
    switch (sig)
    {
    case Start:
        on_start_state(brick_game);
        break;
    case Action:
        on_action_state(brick_game);
        break;
    // case SPAWN:
    //     on_spawn_state(state, stats, map, frog_pos);
    //     break;
    // case MOVING:
    //     on_moving_state(sig, state, map, frog_pos);
    //     break;
    // case SHIFTING:
    //     on_shifting_state(state, stats, map, frog_pos);
    //     break;
    // case REACH:
    //     on_reach_state(state, stats, map, frog_pos);
    //     break;
    // case COLLIDE:
    //     on_collide_state(state, stats, frog_pos);
    //     break;
    // case GAMEOVER:
    //     print_banner(stats);
    //     break;
    default:
        break;
    }
}

UserAction_t get_signal(UserAction_t user_input)
{
    UserAction_t rc = Action;

    if (user_input == KEY_UP)
        rc = Up;
    else if (user_input == KEY_DOWN)
        rc = Down;
    else if (user_input == KEY_LEFT)
        rc = Left;
    else if (user_input == KEY_RIGHT)
        rc = Right;
    // else if (user_input == KEY_P)
    //     rc = Pause;
    else if (user_input == ENTER_KEY)
        rc = Start;
    // else if (user_input == ESCAPE)
    //     rc = Terminate;

    return rc;
}

void on_start_state(GameInfo_t *brick_game)
{
    // if (sig == Start)
    // {
    new_figure(brick_game->field);
    // }
    // if (sig == Action || sig == Start)
    // {
    //     move_FigureDown(brick_game->field);
    //     update_TetrisField(brick_game->field);
    // }
}

void on_action_state(GameInfo_t *brick_game)
{
    move_FigureDown(brick_game->field);
    update_TetrisField(brick_game->field);
}