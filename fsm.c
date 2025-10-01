#include "backend.h"
#include "frontend.h"
#include "fsm.h"
#include <ncurses.h>

// typedef enum
// {
//     Start,
//     Pause,
//     Terminate,
//     Left,
//     Right,
//     Up,
//     Down,
//     Action
// } UserAction_t;

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
    case Left:
        on_left_state(brick_game);
        break;
    case Right:
        on_right_state(brick_game);
        break;
    case Down:
        on_down_state(brick_game);
        break;
    // case Up:
    //     on_rotate_state(brick_game);
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
    else if (user_input == ENTER_KEY)
        rc = Start;
    else if (user_input == ESCAPE)
        rc = Terminate;
    // else if (user_input == KEY_P)
    //     rc = Pause;

    return rc;
}

void on_start_state(GameInfo_t *brick_game)
{
    // if (sig == Start)
    // {
    new_figure(brick_game->field);
    new_figure(brick_game->next);
    print_next_figure(brick_game);
    // }
    // if (sig == Action || sig == Start)
    // {
    //     move_FigureDown(brick_game->field);
    //     update_TetrisField(brick_game->field);
    // }
}

void on_action_state(GameInfo_t *brick_game)
{
    // int next_figure = NO;
    move_FigureDown(brick_game->field);
    // next_figure = collision(brick_game->field);
    // // update_TetrisField(brick_game->field);
    // if (next_figure == YES)
    // {
    //     collision(brick_game->field);
    //     next_figure_to_field(brick_game);
    //     new_figure(brick_game->next);
    //     print_next_figure(brick_game);
    // }
    update_TetrisField(brick_game->field);
}

void on_left_state(GameInfo_t *brick_game)
{
    move_FigureLeft(brick_game->field);
    update_TetrisField(brick_game->field);
}

void on_right_state(GameInfo_t *brick_game)
{
    move_FigureRight(brick_game->field);
    update_TetrisField(brick_game->field);
}

void on_down_state(GameInfo_t *brick_game)
{
    move_FigureBottom(brick_game->field);
    update_TetrisField(brick_game->field);
}

// void on_rotate_state(GameInfo_t *brick_game)
// {
//     rotate_Figure(brick_game->field);
//     update_TetrisField(brick_game->field);
// }