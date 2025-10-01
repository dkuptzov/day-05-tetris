#include "backend.h"
#include "brick.h"
#include "frontend.h"
#include "fsm.h"
#include <locale.h>
#include <ncurses.h>
#include <time.h>

int main(void)
{
    WIN_INIT(50);
    setlocale(LC_ALL, "");
    print_overlay();
    game_loop();
    endwin();

    return SUCCESS;
}

void game_loop(void)
{
    GameInfo_t brick_game;
    UserAction_t state = Pause;
    bool break_flag = TRUE;
    // int signal;
    time_t last_fall_time = 0;
    int fall_interval_ms = 1000;
    stats_init(&brick_game);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    while (break_flag)
    {
        if (state == Terminate)
        {
            // printf("TUT %d", state);
            remove_matrix(&brick_game);
            break_flag = FALSE;
        }
        else if (state == Pause)
        {
            print_pause();
            nodelay(stdscr, FALSE);
            int pause = getch();
            if (get_signal(pause) == Start)
            {
                sigact(Start, &brick_game);
                state = Action;
                nodelay(stdscr, TRUE);
            }
        }
        else
        {
            int signal = getch();
            if (signal != ERR)
            {
                state = get_signal(signal);
                if (state == Left || state == Right || state == Up || state == Down)
                    sigact(state, &brick_game);
            }
            else if (state != Pause && state != Terminate)
            {
                struct timespec now;
                clock_gettime(CLOCK_MONOTONIC, &now);
                long current_time_ms = now.tv_sec * 1000 + now.tv_nsec / 1000000;
                if (current_time_ms - last_fall_time >= fall_interval_ms)
                {
                    sigact(Action, &brick_game);
                    last_fall_time = current_time_ms;
                }
            }
        }
        refresh();
    }
}