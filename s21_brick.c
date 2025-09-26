#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    game_stats_t stats;
    bool break_flag = TRUE;
    // frog_state state = START;
    stats_init(&stats);

    // int speed = 400000;
    time_t last_fall_time = 0;
    int fall_interval_ms = 1000;

    int **field = NULL;
    {
        field = (int **)calloc(24, sizeof(double *));
        for (int i = 0; i < 24; i++)
        {
            field[i] = (int *)calloc(15, sizeof(double));
            if (field[i] == NULL)
            {
                for (int j = 0; j < i; j++)
                    free(field[j]);
                free(field);
            }
        }
    }
    int **copy_field = NULL;
    {
        copy_field = (int **)calloc(24, sizeof(double *));
        for (int i = 0; i < 24; i++)
        {
            copy_field[i] = (int *)calloc(15, sizeof(double));
            if (copy_field[i] == NULL)
            {
                for (int j = 0; j < i; j++)
                    free(copy_field[j]);
                free(copy_field);
            }
        }
    }
    for (int j = 4; j < 15; j++)
        field[23][j] = 2;
    int next_fig = 1, number_fig = 0, state_fig = 0;
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    while (break_flag)
    {
        timeout(100);
        // usleep(speed);
        int stop = 0;
        if (next_fig)
        {
            number_fig = new_figure(field);
            next_fig = 0;
            state_fig = 0;
        }
        // move_FigureDown(field);
        // update_TetrisField(field);
        // for (int i = 22; i > 2; i--)
        // {
        //     for (int j = 13; j > 2; j--)
        //     {
        //         if (field[i][j] == 1 && field[i + 1][j] == 0)
        //         {
        //             change_color(i, j, 1);
        //             field[i][j] = 0;
        //             field[i + 1][j] = 1;
        //         }
        //         else if (field[i][j] == 0)
        //             change_color(i, j, 0);
        //         else if (field[i][j] == 2)
        //             change_color(i, j, 1);
        //     }
        // }
        // refresh();
        int signal = getch();
        if (signal != ERR)
        {
            UserAction_t action = get_signal(signal);
            if (action == Left)
            {
                move_FigureLeft(field);
                update_TetrisField(field);
            }
            else if (action == Right)
            {
                for (int i = 3; i < 23 && stop == 0; i++)
                {
                    for (int j = 13; j > 2 && stop == 0; j--)
                    {
                        if (field[i][j] == 1 && j < 13)
                        {
                            field[i][j + 1] = 1;
                            field[i][j] = 0;
                        }
                        else if (field[i][j] == 1 && j == 13)
                            stop = 1;
                    }
                }
            }
            else if (action == Up)
            {
                if (number_fig == 1)
                {
                    int ret = func_up_1(state_fig, field);
                    if (ret == RETURN_OK)
                        state_fig = (state_fig == 1) ? 0 : 1;
                }
                else if (number_fig == 2)
                {
                    func_up_2(state_fig, field);
                    state_fig = (state_fig < 3) ? state_fig + 1 : 0;
                }
                else if (number_fig == 3)
                {
                    func_up_3(state_fig, field);
                    state_fig = (state_fig < 3) ? state_fig + 1 : 0;
                }
                else if (number_fig == 5)
                {
                    int ret = func_up_5(state_fig, field);
                    if (ret == RETURN_OK)
                        state_fig = (state_fig == 1) ? 0 : 1;
                }
                else if (number_fig == 6)
                {
                    func_up_6(state_fig, field);
                    state_fig = (state_fig < 3) ? state_fig + 1 : 0;
                }
                else if (number_fig == 7)
                {
                    int ret = func_up_7(state_fig, field);
                    if (ret == RETURN_OK)
                        state_fig = (state_fig == 1) ? 0 : 1;
                }
            }
            update_TetrisField(field);
        }
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        long current_time_ms = now.tv_sec * 1000 + now.tv_nsec / 1000000;

        if (current_time_ms - last_fall_time >= fall_interval_ms)
        {
            move_FigureDown(field);
            update_TetrisField(field);
            last_fall_time = current_time_ms;
        }
        // UserAction_t action = get_signal(signal);
        s21_copy_field(copy_field, field);
        /*
        if (action == Left)
        {
            move_FigureLeft(field);
            update_TetrisField(field);
            // for (int i = 22; i > 2 && stop == 0; i--)
            // {
            //     for (int j = 4; j < 14 && stop == 0; j++)
            //     {
            //         if (field[i][j] == 1 && field[i][j - 1] == 0 && j > 4)
            //         {
            //             field[i][j - 1] = 1;
            //             field[i][j] = 0;
            //         }
            //         else if (field[i][j] == 1 && j == 4)
            //             stop = 1;
            //     }
            // }
        }
        else if (action == Right)
        {
            for (int i = 3; i < 23 && stop == 0; i++)
            {
                for (int j = 13; j > 2 && stop == 0; j--)
                {
                    if (field[i][j] == 1 && j < 13)
                    {
                        field[i][j + 1] = 1;
                        field[i][j] = 0;
                    }
                    else if (field[i][j] == 1 && j == 13)
                        stop = 1;
                }
            }
        }
        else if (action == Up)
        {
            if (number_fig == 1)
            {
                int ret = func_up_1(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
            else if (number_fig == 2)
            {
                func_up_2(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
            }
            else if (number_fig == 3)
            {
                func_up_3(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
            }
            else if (number_fig == 5)
            {
                int ret = func_up_5(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
            else if (number_fig == 6)
            {
                func_up_6(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
            }
            else if (number_fig == 7)
            {
                int ret = func_up_7(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
        }
        */
        if (stop == 1)
            s21_copy_field(field, copy_field);
        for (int i = 22; i > 2; i--)
            for (int j = 13; j > 2; j--)
                if (field[i][j] == 1 && field[i + 1][j] == 2)
                    next_fig = 1;
        if (next_fig == 1)
            for (int i = 22; i > 2; i--)
                for (int j = 13; j > 2; j--)
                    if (field[i][j] == 1)
                        field[i][j] = 2;
        // timeout(1000);
    }
}

void update_TetrisField(int **field)
{
    for (int i = 22; i > 2; i--)
    {
        for (int j = 13; j > 2; j--)
        {
            if (field[i][j] == 0)
                change_color(i, j, 0);
            else
                change_color(i, j, 1);
        }
    }
}

void move_FigureDown(int **field)
{
    for (int i = 22; i > 2; i--)
    {
        for (int j = 13; j > 2; j--)
        {
            if (field[i][j] == 1 && field[i + 1][j] == 0)
            {
                field[i][j] = 0;
                field[i + 1][j] = 1;
            }
        }
    }
}

void move_FigureLeft(int **field)
{
    int stop_round = 0;
    for (int i = 22; i > 2 && stop_round == 0; i--)
    {
        for (int j = 4; j < 14 && stop_round == 0; j++)
        {
            if (field[i][j] == 1 && field[i][j - 1] == 0 && j > 4)
            {
                field[i][j - 1] = 1;
                field[i][j] = 0;
            }
            else if (field[i][j] == 1 && j == 4)
                stop_round = 1;
        }
    }
}

/*
void game_loop(void)
{
    // board_t map;
    game_stats_t stats;
    struct timespec sp_start, sp_end, ts1, ts2;
    // player_pos frog;

    bool break_flag = TRUE;
    // int signal = 0;
    frog_state state = START;

    stats_init(&stats);

    int speed = 400000;
    // square_t test;

    int **field = NULL;
    {
        field = (int **)calloc(24, sizeof(double *));
        // if (field == NULL)
        //     ret = S21_MATRIX_WRONG;
        // for (int i = 0; i < 24 && ret == S21_MATRIX_OK; i++)
        for (int i = 0; i < 24; i++)
        {
            field[i] = (int *)calloc(15, sizeof(double));
            if (field[i] == NULL)
            {
                for (int j = 0; j < i; j++)
                    free(field[j]);
                free(field);
                // ret = S21_MATRIX_WRONG;
            }
        }
    }
    int **copy_field = NULL;
    {
        copy_field = (int **)calloc(24, sizeof(double *));
        // if (field == NULL)
        //     ret = S21_MATRIX_WRONG;
        // for (int i = 0; i < 24 && ret == S21_MATRIX_OK; i++)
        for (int i = 0; i < 24; i++)
        {
            copy_field[i] = (int *)calloc(15, sizeof(double));
            if (copy_field[i] == NULL)
            {
                for (int j = 0; j < i; j++)
                    free(copy_field[j]);
                free(copy_field);
                // ret = S21_MATRIX_WRONG;
            }
        }
    }
    // int field[24][15] = {{0}};
    for (int j = 4; j < 15; j++)
        field[23][j] = 2;
    // int x = 3, y = 9;
    // field[x][y] = 1;
    // field[3][8] = 1;
    // field[3][9] = 1;
    // field[3][10] = 1;
    // field[3][11] = 1;
    int next_fig = 1, number_fig = 0, state_fig = 0;
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    while (break_flag)
    {
        clock_gettime(CLOCK_MONOTONIC, &sp_start);
        usleep(speed);
        int stop = 0;
        if (next_fig)
        {
            number_fig = new_figure(field);
            next_fig = 0;
            state_fig = 0;
        }
        // for (int i = 3; i < 23; i++)
        for (int i = 22; i > 2; i--)
        {
            // for (int j = 3; j < 14; j++)
            for (int j = 13; j > 2; j--)
            {
                if (field[i][j] == 1 && field[i + 1][j] == 0)
                {
                    change_color(i, j, 1);
                    field[i][j] = 0;
                    field[i + 1][j] = 1;
                }
                // else if (field[i][j] == 1 && field[i + 1][j] == 2)
                // {
                //     change_color(i, j, 1);
                //     field[i][j] = 2;
                //     next_figure = 1;
                // }
                else if (field[i][j] == 0)
                    change_color(i, j, 0);
                else if (field[i][j] == 2)
                    change_color(i, j, 1);
                // printw("@");
            }
        }
        // x++;
        // field[x][y] = 1;
        refresh();
        int signal = getch();
        UserAction_t action = get_signal(signal);
        // как вариант сначала сохранить матрицу, если все изменения прошли хорошо,
        // оставляем измененную матрицу, иначе возвращаем копию
        // if (action == Left && y > 4)
        // copy_field = field;
        s21_copy_field(copy_field, field);
        if (action == Left)
        {
            for (int i = 22; i > 2 && stop == 0; i--)
            {
                for (int j = 4; j < 14 && stop == 0; j++)
                {
                    if (field[i][j] == 1 && field[i][j - 1] == 0 && j > 4)
                    {
                        field[i][j - 1] = 1;
                        field[i][j] = 0;
                        // y--;
                    }
                    else if (field[i][j] == 1 && j == 4)
                        stop = 1;
                }
            }
        }
        // else if (action == Right && y < 14)
        else if (action == Right)
        {
            for (int i = 3; i < 23 && stop == 0; i++)
            {
                for (int j = 13; j > 2 && stop == 0; j--)
                {
                    if (field[i][j] == 1 && j < 13)
                    {
                        field[i][j + 1] = 1;
                        field[i][j] = 0;
                        // y++;
                        // j++;
                    }
                    else if (field[i][j] == 1 && j == 13)
                        stop = 1;
                }
            }
        }
        else if (action == Up)
        {
            if (number_fig == 1)
            {
                int ret = func_up_1(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
            else if (number_fig == 2)
            {
                func_up_2(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
            }
            else if (number_fig == 3)
            {
                func_up_3(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
            }
            else if (number_fig == 5)
            {
                int ret = func_up_5(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
            else if (number_fig == 6)
            {
                func_up_6(state_fig, field);
                state_fig = (state_fig < 3) ? state_fig + 1 : 0;
                // if (ret == RETURN_OK)
                //     state_fig = (state_fig == 1) ? 0 : 1;
            }
            else if (number_fig == 7)
            {
                int ret = func_up_7(state_fig, field);
                if (ret == RETURN_OK)
                    state_fig = (state_fig == 1) ? 0 : 1;
            }
        }
        if (stop == 1)
            s21_copy_field(field, copy_field);
        // field = copy_field;
        for (int i = 22; i > 2; i--)
            for (int j = 13; j > 2; j--)
                if (field[i][j] == 1 && field[i + 1][j] == 2)
                    next_fig = 1;
        if (next_fig == 1)
            for (int i = 22; i > 2; i--)
                for (int j = 13; j > 2; j--)
                    if (field[i][j] == 1)
                        field[i][j] = 2;
        if (state == GAMEOVER || state == EXIT_STATE || state == FILE_ERROR_STATE)
            break_flag = FALSE;

        // sigact(get_signal(signal), &state, &stats, &map, &frog);

        // if (state == MOVING || state == START)
        //     signal = GET_USER_INPUT;
        clock_gettime(CLOCK_MONOTONIC, &sp_end);
        if (sp_end.tv_sec - sp_start.tv_sec <= 0 && (ts2.tv_nsec == 33000000 - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
            nanosleep(&ts2, &ts1);
    }

    if (state == FILE_ERROR_STATE)
    {
        // print_levelerror();
        nodelay(stdscr, FALSE);
        getch();
    }
}
*/

void change_color(int i, int j, int color)
{
    attron(COLOR_PAIR(color));
    mvaddch(i, j, ' ');
    attroff(COLOR_PAIR(color));
}

void print_overlay(void)
{
    // 0 30 0 30
    print_rectangle(0, 20 + 1, 0, BOARD_M + 1);                       // игровое поле
    print_rectangle(0, 20 + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3); // дополнительное поле

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

UserAction_t get_signal(int user_input)
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
    // else if (user_input == ESCAPE)
    //     rc = ESCAPE_BTN;
    // else if (user_input == ENTER_KEY)
    //     rc = ENTER_BTN;

    return rc;
}

int new_figure(int **matrix)
{
    srand((unsigned)time(NULL));
    int random_number = rand() % 10;
    while (random_number > 7 || random_number == 0)
        random_number = rand() % 10;
    // printw("%d", random_number);
    // удалить потом
    // random_number = 1;
    switch (random_number)
    {
    case 1:
        matrix[3][8] = 1;
        matrix[3][9] = 1;
        matrix[3][10] = 1;
        matrix[3][11] = 1;
        break;
    case 2:
        matrix[3][8] = 1;
        matrix[4][8] = 1;
        matrix[4][9] = 1;
        matrix[4][10] = 1;
        break;
    case 3:
        matrix[3][10] = 1;
        matrix[4][8] = 1;
        matrix[4][9] = 1;
        matrix[4][10] = 1;
        break;
    case 4:
        matrix[3][9] = 1;
        matrix[3][10] = 1;
        matrix[4][9] = 1;
        matrix[4][10] = 1;
        break;
    case 5:
        matrix[3][9] = 1;
        matrix[3][10] = 1;
        matrix[4][8] = 1;
        matrix[4][9] = 1;
        break;
    case 6:
        matrix[3][9] = 1;
        matrix[4][8] = 1;
        matrix[4][9] = 1;
        matrix[4][10] = 1;
        break;
    case 7:
        matrix[3][8] = 1;
        matrix[3][9] = 1;
        matrix[4][9] = 1;
        matrix[4][10] = 1;
        break;
    default:
        break;
    }
    return random_number;
}

void s21_copy_field(int **A, int **B)
{
    for (int i = 0; i < 24; i++)
        for (int j = 0; j < 15; j++)
            A[i][j] = B[i][j];
}

int func_up_1(int state_fig, int **field)
{
    int count = 0, break_for = 0, result = RETURN_OK;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 3 && state_fig == 0 && field[i - 1][j] == 0 && field[i - 2][j] == 0 && field[i + 1][j] == 0)
            {
                // все поля надо проверить что они равны 0, которые становятся 1
                field[i][j - 1] = 0;
                field[i][j - 2] = 0;
                field[i][j + 1] = 0;
                field[i - 1][j] = 1;
                field[i - 2][j] = 1;
                field[i + 1][j] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && j > 5 && field[i][j - 1] == 0 && field[i][j - 2] == 0 && field[i][j + 1] == 0 && j < 13)
            {
                field[i - 1][j] = 0;
                field[i + 1][j] = 0;
                field[i + 2][j] = 0;
                field[i][j - 1] = 1;
                field[i][j - 2] = 1;
                field[i][j + 1] = 1;
                break_for = 1;
            }
            else if ((count == 3 && state_fig == 0) || (count == 2 && state_fig == 1))
            {
                break_for = 1;
                result = RETURN_WRONG;
            }
        }
    }
    return result;
}

void func_up_2(int state_fig, int **field)
{
    int count = 0, break_for = 0;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 3 && state_fig == 0 && field[i - 1][j] == 0 && field[i + 1][j] == 0 && field[i - 1][j + 1] == 0)
            {
                field[i][j - 1] = 0;
                field[i][j + 1] = 0;
                field[i - 1][j - 1] = 0;
                field[i - 1][j] = 1;
                field[i + 1][j] = 1;
                field[i - 1][j + 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && field[i + 1][j] == 0 && field[i][j - 2] == 0)
            {
                field[i + 1][j - 1] = 0;
                field[i + 2][j - 1] = 0;
                field[i + 1][j] = 1;
                field[i][j - 2] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 2 && field[i - 1][j] == 0 && field[i + 1][j] == 0 && field[i + 1][j - 1] == 0)
            {
                field[i][j - 1] = 0;
                field[i][j + 1] = 0;
                field[i + 1][j + 1] = 0;
                field[i - 1][j] = 1;
                field[i + 1][j] = 1;
                field[i + 1][j - 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 3 && field[i][j - 1] == 0 && field[i][j + 1] == 0 && field[i - 1][j - 1] == 0)
            {
                field[i - 1][j] = 0;
                field[i + 1][j] = 0;
                field[i + 1][j - 1] = 0;
                field[i][j - 1] = 1;
                field[i][j + 1] = 1;
                field[i - 1][j - 1] = 1;
                break_for = 1;
            }
        }
    }
}

void func_up_3(int state_fig, int **field)
{
    int count = 0, break_for = 0;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 3 && state_fig == 0 && field[i - 1][j] == 0 && field[i + 1][j] == 0 && field[i + 1][j + 1] == 0)
            {
                field[i][j - 1] = 0;
                field[i][j + 1] = 0;
                field[i - 1][j + 1] = 0;
                field[i - 1][j] = 1;
                field[i + 1][j] = 1;
                field[i + 1][j + 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && field[i - 1][j + 1] == 0 && field[i - 1][j + 2] == 0)
            {
                field[i + 1][j] = 0;
                field[i + 1][j + 1] = 0;
                field[i - 1][j + 1] = 1;
                field[i - 1][j + 2] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 2 && field[i - 1][j] == 0 && field[i + 1][j] == 0 && field[i - 1][j - 1] == 0)
            {
                field[i][j - 1] = 0;
                field[i][j + 1] = 0;
                field[i + 1][j - 1] = 0;
                field[i - 1][j] = 1;
                field[i + 1][j] = 1;
                field[i - 1][j - 1] = 1;
                break_for = 1;
            }
            else if (count == 3 && state_fig == 3 && field[i][j - 1] == 0 && field[i][j + 1] == 0 && field[i - 1][j + 1] == 0)
            {
                field[i - 1][j] = 0;
                field[i - 1][j - 1] = 0;
                field[i + 1][j] = 0;
                field[i][j - 1] = 1;
                field[i][j + 1] = 1;
                field[i - 1][j + 1] = 1;
                break_for = 1;
            }
        }
    }
}

int func_up_5(int state_fig, int **field)
{
    int count = 0, break_for = 0, result = RETURN_OK;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 3 && state_fig == 0 && field[i - 1][j] == 0 && field[i + 1][j + 1] == 0)
            {
                field[i - 1][j + 1] = 0;
                field[i - 1][j + 2] = 0;
                field[i - 1][j] = 1;
                field[i + 1][j + 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && field[i - 1][j + 1] == 0 && field[i - 1][j + 2] == 0 && j != 12)
            {
                field[i - 1][j] = 0;
                field[i + 1][j + 1] = 0;
                field[i - 1][j + 1] = 1;
                field[i - 1][j + 2] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && j == 12)
            {
                break_for = 1;
                result = RETURN_WRONG;
            }
        }
    }
    return result;
}

void func_up_6(int state_fig, int **field)
{
    int count = 0, break_for = 0;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 3 && state_fig == 0 && field[i + 1][j] == 0)
            {
                field[i][j - 1] = 0;
                field[i + 1][j] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && field[i][j - 1] == 0)
            {
                field[i - 1][j] = 0;
                field[i][j - 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 2 && field[i - 1][j] == 0)
            {
                field[i][j + 1] = 0;
                field[i - 1][j] = 1;
                break_for = 1;
            }
            else if (count == 3 && state_fig == 3 && field[i][j + 1] == 0)
            {
                field[i + 1][j] = 0;
                field[i][j + 1] = 1;
                break_for = 1;
            }
        }
    }
}

int func_up_7(int state_fig, int **field)
{
    int count = 0, break_for = 0, result = RETURN_OK;
    for (int i = 3; i < 23 && break_for == 0; i++)
    {
        for (int j = 4; j < 14 && break_for == 0; j++)
        {
            if (field[i][j] == 1)
                count++;
            if (count == 2 && state_fig == 0 && field[i + 1][j - 1] == 0 && field[i + 2][j - 1] == 0)
            {
                field[i][j - 1] = 0;
                field[i + 1][j + 1] = 0;
                field[i + 1][j - 1] = 1;
                field[i + 2][j - 1] = 1;
                break_for = 1;
            }
            else if (count == 2 && state_fig == 1 && field[i][j - 1] == 0 && field[i + 1][j + 1] == 0)
            {
                field[i][j + 1] = 0;
                field[i - 1][j + 1] = 0;
                field[i][j - 1] = 1;
                field[i + 1][j + 1] = 1;
                break_for = 1;
            }
            // else if (count == 2 && state_fig == 1 && j == 12)
            // {
            //     break_for = 1;
            //     result = RETURN_WRONG;
            // }
        }
    }
    return result;
}