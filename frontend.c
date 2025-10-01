#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "backend.h"
#include "frontend.h"

void print_overlay(void)
{
    // 0 30 0 30
    print_rectangle(0, 20 + 1, 0, BOARD_M);                           // игровое поле
    print_rectangle(0, 20 + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3); // дополнительное поле

    // мини поля с названиями LEVEL5 SCORE SPEED LIVES
    print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    print_rectangle(4, 6, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    print_rectangle(7, 9, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
    // print_rectangle(10, 12, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);

    // вывод текста на экран
    MVPRINTW(2, BOARD_M + 5, "BEST");
    MVPRINTW(5, BOARD_M + 5, "SCORE 0");
    MVPRINTW(8, BOARD_M + 5, "LEVEL 1");
    // MVPRINTW(11, BOARD_M + 5, "LIVES ");

    // print_rectangle(10, 11, 9, 11);

    // MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);

    // print_rectangle(1, 3, 12 + 3, 12 + 12 + 2);

    refresh();
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

// void print_square(int top_y, int bottom_y, int left_x, int right_x)
// {
//     attron(COLOR_PAIR(1));
//     for (int y = top_y; y <= bottom_y; y++)
//     {
//         for (int x = left_x; x <= right_x; x++)
//         {
//             mvaddch(y, x, ' ');
//         }
//     }
//     attroff(COLOR_PAIR(1));
// }

// void print_square(int y, int x)
// {
//     attron(COLOR_PAIR(1));
//     mvaddch(y, x, ' ');
//     attroff(COLOR_PAIR(1));
// }

void print_pause(void)
{
    MVPRINTW(30, 0, "Press Entet to Start/Continue!");
}

int new_figure(int **matrix)
{
    srand((unsigned)time(NULL));
    int random_number = rand() % 10;
    while (random_number > 7 || random_number == 0)
        random_number = rand() % 10;
    random_number = 7;
    switch (random_number)
    {
    case 1:
        matrix[3][12] = 1;
        matrix[3][13] = 1;
        matrix[3][14] = 1;
        matrix[3][15] = 1;
        break;
    case 2:
        matrix[3][12] = 1;
        matrix[4][12] = 1;
        matrix[4][13] = 1;
        matrix[4][14] = 1;
        break;
    case 3:
        matrix[3][14] = 1;
        matrix[4][12] = 1;
        matrix[4][13] = 1;
        matrix[4][14] = 1;
        break;
    case 4:
        matrix[3][12] = 1;
        matrix[3][13] = 1;
        matrix[4][12] = 1;
        matrix[4][13] = 1;
        break;
    case 5:
        matrix[3][13] = 1;
        matrix[3][14] = 1;
        matrix[4][12] = 1;
        matrix[4][13] = 1;
        break;
    case 6:
        matrix[3][13] = 1;
        matrix[4][12] = 1;
        matrix[4][13] = 1;
        matrix[4][14] = 1;
        break;
    case 7:
        matrix[3][12] = 1;
        matrix[3][13] = 1;
        matrix[4][13] = 1;
        matrix[4][14] = 1;
        break;
    default:
        break;
    }
    return random_number;
}

void update_TetrisField(int **field)
{
    for (int i = 22; i > 2; i--)
    {
        for (int j = RightBorderField; j >= LeftBorderField; j--)
        {
            if (field[i][j] == 0)
                change_color(i, j, 0);
            else
                change_color(i, j, 1);
        }
    }
}

void change_color(int i, int j, int color)
{
    attron(COLOR_PAIR(color));
    mvaddch(i, j, ' ');
    attroff(COLOR_PAIR(color));
}

void print_next_figure(GameInfo_t *brick_game)
{
    for (int i = 3; i <= 4; i++)
        for (int j = 12; j <= 14; j++)
            if (brick_game->next[i][j] == 1)
            {
                attron(COLOR_PAIR(1));
                mvaddch(i + 11, j + 25, ' ');
                attroff(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(0));
                mvaddch(i + 11, j + 25, ' ');
                attroff(COLOR_PAIR(0));
            }
}

void next_figure_to_field(GameInfo_t *brick_game)
{
    for (int i = 3; i <= 4; i++)
        for (int j = 8; j <= 10; j++)
            if (brick_game->next[i][j] == 1 && brick_game->field[i][j] == 0)
                brick_game->field[i][j] = 1;
}
