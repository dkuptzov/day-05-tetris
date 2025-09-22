#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "s21_brick.h"

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
    // board_t map;
    game_stats_t stats;
    // player_pos frog;

    bool break_flag = TRUE;
    // int signal = 0;
    frog_state state = START;

    stats_init(&stats);

    // int matr[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    int speed = 300000;
    // square_t test;
    int field[21][10] = {{0}};
    for (int j = 0; j < 10; j++)
        field[20][j] = 2;
    int x = 1, y = 4;
    field[x][y] = 1;
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    while (break_flag)
    {
        usleep(speed);
        // for (int i = 0; i < 20; i++)
        //     for (int j = 0; j < 10; j++)
        //         if (field[i][j] == 1)
        //         {
        //             attron(COLOR_PAIR(0));
        //             mvaddch(i, j, ' ');
        //             attroff(COLOR_PAIR(0));
        //         }
        //         else if (field[i][j] == 2)
        //         {
        //             // printw("%d %d  ", i, j);
        //             attron(COLOR_PAIR(1));
        //             mvaddch(i, j, ' ');
        //             attroff(COLOR_PAIR(1));
        //         }
        // refresh();
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                // printw("%d", x);
                if (field[i][j] == 1 && field[i + 1][j] == 0)
                {
                    attron(COLOR_PAIR(1));
                    mvaddch(i, j, ' ');
                    attroff(COLOR_PAIR(1));
                    field[i][j] = 0;
                }
                else if (field[i][j] == 1 && field[i + 1][j] == 2)
                {
                    attron(COLOR_PAIR(1));
                    mvaddch(i, j, ' ');
                    attroff(COLOR_PAIR(1));
                    field[i][j] = 2;
                    x = 0;
                }
                else if (field[i][j] == 0)
                {
                    attron(COLOR_PAIR(0));
                    mvaddch(i, j, ' ');
                    attroff(COLOR_PAIR(0));
                }
                else if (field[i][j] == 2)
                {
                    attron(COLOR_PAIR(1));
                    mvaddch(i, j, ' ');
                    attroff(COLOR_PAIR(1));
                }
                // else if (field[i + 1][j] == 2 && i < 20)
                // {
                //     field[i][j] = 2;
                //     x = 0;
                // }
            }
        }
        x++;
        // if (br == 1 || x == 20)
        // {
        //     printw("%d ", x);
        //     x = 1;
        //     br = 0;
        //     for (int i = 0; i < 20; i++)
        //         for (int j = 0; j < 10; j++)
        //             if (field[i][j] == 1)
        //                 field[i][j] = 2;
        // }
        field[x][y] = 1;
        refresh();

        if (state == GAMEOVER || state == EXIT_STATE || state == FILE_ERROR_STATE)
            break_flag = FALSE;

        // sigact(get_signal(signal), &state, &stats, &map, &frog);

        // if (state == MOVING || state == START)
        //     signal = GET_USER_INPUT;
    }

    if (state == FILE_ERROR_STATE)
    {
        // print_levelerror();
        nodelay(stdscr, FALSE);
        getch();
    }
}

// void clear_test(void)
// {
//     CLEAR_BACKPOS(10, 9);
//     CLEAR_BACKPOS(10, 10);
//     CLEAR_BACKPOS(10, 11);
//     CLEAR_BACKPOS(11, 9);
//     CLEAR_BACKPOS(11, 10);
//     CLEAR_BACKPOS(11, 11);
// }

void print_test(square_t *sq)
{
    // CLEAR_BACKPOS(sq->x1, sq->x2);
    // sq->x1++;
    // sq->x2++;
    CLEAR_BACKPOS(sq->x1, sq->y1);
    CLEAR_BACKPOS(sq->x1, sq->y1 + 1);
    CLEAR_BACKPOS(sq->x1, sq->y2);
    CLEAR_BACKPOS(sq->x2, sq->y1);
    CLEAR_BACKPOS(sq->x2, sq->y1 + 1);
    CLEAR_BACKPOS(sq->x2, sq->y2);
    sq->x1++;
    sq->x2++;
    print_rectangle(sq->x1, sq->x2, sq->y1, sq->y2);
    // mvaddch(sq->x1 + 1, sq->x2 + 1, ' ');
    refresh();
}

void print_overlay(void)
{
    // 0 30 0 30
    // print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);                       // игровое поле
    print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3); // дополнительное поле

    // мини поля с названиями LEVEL5 SCORE SPEED LIVES
    //  print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    //  print_rectangle(4, 6, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    //  print_rectangle(7, 9, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    //  print_rectangle(10, 12, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);

    // вывод текста на экран
    //  MVPRINTW(2, BOARD_M + 5, "LEVEL5");
    //  MVPRINTW(5, BOARD_M + 5, "SCORE");
    //  MVPRINTW(8, BOARD_M + 5, "SPEED");
    //  MVPRINTW(11, BOARD_M + 5, "LIVES");

    // print_rectangle(10, 11, 9, 11);

    // MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
    refresh();
}

void stats_init(game_stats_t *stats)
{
    stats->level = 1;
    stats->score = 0;
    stats->speed = 1;
    stats->lives = 9;
    stats->won = FALSE;
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x)
{
    MVADDCH(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;

    for (; i < right_x; i++)
        MVADDCH(top_y, i, ACS_HLINE);
    MVADDCH(top_y, i, ACS_URCORNER);

    for (int i = top_y + 1; i < bottom_y; i++)
    {
        MVADDCH(i, left_x, ACS_VLINE);
        MVADDCH(i, right_x, ACS_VLINE);
    }

    MVADDCH(bottom_y, left_x, ACS_LLCORNER);
    i = left_x + 1;
    for (; i < right_x; i++)
        MVADDCH(bottom_y, i, ACS_HLINE);
    MVADDCH(bottom_y, i, ACS_LRCORNER);
}
