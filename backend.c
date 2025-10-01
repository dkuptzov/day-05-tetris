#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include "fsm.h"

void stats_init(GameInfo_t *game)
{
    int **field = NULL, **next = NULL;
    field = (int **)calloc(ROWS_FIELD, sizeof(double *));
    for (int i = 0; i < ROWS_FIELD; i++)
    {
        field[i] = (int *)calloc(COLS_FIELD, sizeof(double));
        if (field[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(field[j]);
            free(field);
        }
    }
    for (int j = 0; j < ROWS_FIELD - 1; j++)
        field[ROWS_FIELD - 1][j] = 2;
    next = (int **)calloc(ROWS_NEXT, sizeof(double *));
    for (int i = 0; i < ROWS_NEXT; i++)
    {
        next[i] = (int *)calloc(COLS_FIELD, sizeof(double));
        if (next[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(next[j]);
            free(next);
        }
    }
    game->field = field;
    game->next = next;
    game->high_score = 0;
    game->score = 0;
    game->level = 1;
    game->speed = 1;
    game->pause = Pause;
}

void move_FigureDown(int **field)
{
    // int next_figure = NO;
    for (int i = ROWS_FIELD - 2; i >= ROWS_FIELD_MIN; i--)
    {
        for (int j = RightBorderField; j >= LeftBorderField; j--)
        {
            if (field[i][j] == 1 && field[i + 1][j] == 0)
            {
                field[i][j] = 0;
                field[i + 1][j] = 1;
            }
        }
    }
    // for (int i = 22; i > 2; i--)
    //     for (int j = RightBorderField; j >= LeftBorderField; j--)
    //         if (field[i][j] == 1 && field[i + 1][j] == 2)
    //             next_figure = YES;
    // return next_figure;
}

void move_FigureLeft(int **field)
{
    int stop_round = 0;
    // int stop_round = 0, **copy_field = create_matrix();
    // copy_matrix(copy_field, field);
    // for (int i = ROWS_FIELD - 2; i >= ROWS_FIELD_MIN && stop_round == 0; i--)
    for (int i = ROWS_FIELD_MIN; i <= ROWS_FIELD - 2 && stop_round == 0; i++)
    {
        for (int j = COLS_FIELD_MIN; j <= COLS_FIELD && stop_round == 0; j++)
        {
            if (field[i][j] == 1 && field[i + 1][j - 2] == 1 && COLS_FIELD_MIN == j - 2)
                stop_round = 1;
            else if (field[i][j] == 1 && field[i + 1][j - 1] == 1 && COLS_FIELD_MIN == j - 1)
                stop_round = 1;
            else if (field[i][j] == 1 && field[i][j - 1] == 0 && j > COLS_FIELD_MIN)
            {
                field[i][j - 1] = 1;
                field[i][j] = 0;
            }
            // else if ((field[i][j] == 1 && j == COLS_FIELD_MIN))
            else if ((field[i][j] == 1 && j == COLS_FIELD_MIN) || (field[i][j] == 1 && field[i][j - 1] > 1))
                stop_round = 1;
        }
    }
    // if (stop_round)
    //     copy_matrix(field, copy_field);
    // remove_matrix_2(copy_field);
    // copy_field = NULL;
}

void move_FigureRight(int **field)
{
    int stop_round = 0;
    // int stop_round = 0, **copy_field = create_matrix();
    // copy_matrix(copy_field, field);
    for (int i = ROWS_FIELD_MIN; i <= ROWS_FIELD - 2 && stop_round == 0; i++)
    // for (int i = ROWS_FIELD - 2; i >= ROWS_FIELD_MIN && stop_round == 0; i--)
    {
        for (int j = COLS_FIELD; j >= COLS_FIELD_MIN && stop_round == 0; j--)
        {
            if (field[i][j] == 1 && field[i + 1][j + 2] == 1 && COLS_FIELD == j + 2)
                stop_round = 1;
            else if (field[i][j] == 1 && field[i + 1][j + 1] == 1 && COLS_FIELD == j + 1)
                stop_round = 1;
            else if (field[i][j] == 1 && field[i][j + 1] == 0 && j < COLS_FIELD)
            {
                field[i][j + 1] = 1;
                field[i][j] = 0;
            }
            else if ((field[i][j] == 1 && j == COLS_FIELD) || (field[i][j] == 1 && field[i][j + 1] > 1))
            {
                // printf("TUT");
                stop_round = 1;
            }
            // printf("%d\n", stop_round);
        }
    }
    // if (stop_round)
    //     copy_matrix(field, copy_field);
    // remove_matrix_2(copy_field);
    // copy_field = NULL;
}

void move_FigureBottom(int **field)
{
    int count = 0, count_max = 50;
    for (int i = ROWS_FIELD - 2; i >= ROWS_FIELD_MIN; i--)
        for (int j = COLS_FIELD_MIN; j <= COLS_FIELD; j++)
            if (field[i][j] == 1 && field[i + 1][j] == 0)
            {
                int x = i + 1;
                while (field[x++][j] == 0)
                    count++;
                if (count < count_max)
                    count_max = count;
            }
    for (int i = ROWS_FIELD - 2; i >= ROWS_FIELD_MIN; i--)
        for (int j = COLS_FIELD_MIN; j <= COLS_FIELD; j++)
            if (field[i][j] == 1)
            {
                field[i][j] = 0;
                field[i + count_max][j] = 1;
            }
}

// int rotate_Figure(int **field, int number_figure, int *state_figure)
// {
//     if (number_figure == 1)
//     {
//         int ret = func_up_1(*state_figure, field);
//         if (ret == RETURN_OK)
//             *state_figure = (*state_figure == 1) ? 0 : 1;
//     }
//     else if (number_figure == 2)
//     {
//         func_up_2(*state_figure, field);
//         *state_figure = (*state_figure < 3) ? *state_figure + 1 : 0;
//     }
//     else if (number_figure == 3)
//     {
//         func_up_3(*state_figure, field);
//         *state_figure = (*state_figure < 3) ? *state_figure + 1 : 0;
//     }
//     else if (number_figure == 5)
//     {
//         int ret = func_up_5(*state_figure, field);
//         if (ret == RETURN_OK)
//             *state_figure = (*state_figure == 1) ? 0 : 1;
//     }
//     else if (number_figure == 6)
//     {
//         func_up_6(*state_figure, field);
//         *state_figure = (*state_figure < 3) ? *state_figure + 1 : 0;
//     }
//     else if (number_figure == 7)
//     {
//         int ret = func_up_7(*state_figure, field);
//         if (ret == RETURN_OK)
//             *state_figure = (*state_figure == 1) ? 0 : 1;
//     }
//     return 0;
// }

int **create_matrix(void)
{
    int **A = (int **)calloc(ROWS_FIELD, sizeof(int *));
    for (int i = 0; i < ROWS_FIELD; i++)
    {
        A[i] = (int *)calloc(COLS_FIELD, sizeof(int));
        if (A[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(A[j]);
            free(A);
        }
    }
    return A;
}

void copy_matrix(int **A, int **B)
{
    if (A != NULL || B != NULL)
        for (int i = 0; i < ROWS_FIELD; i++)
            for (int j = 0; j < COLS_FIELD; j++)
                A[i][j] = B[i][j];
}

int collision(int **field)
{
    int next_figure = NO;
    for (int i = 22; i > 2; i--)
        for (int j = RightBorderField; j >= LeftBorderField; j--)
            if (field[i][j] == 1 && field[i + 1][j] == 2)
                next_figure = YES;
    if (next_figure == YES)
    {
        for (int i = 22; i > 2; i--)
            for (int j = RightBorderField; j >= LeftBorderField; j--)
                if (field[i][j] == 1)
                    field[i][j] = 2;
    }
    return next_figure;
}

void remove_matrix(GameInfo_t *game)
{
    if (game != NULL)
    {
        if (game->field)
        {
            for (int i = 0; i < ROWS_FIELD; i++)
                free(game->field[i]);
            free(game->field);
        }
        game->field = NULL;
        if (game->next != NULL)
        {
            for (int i = 0; i < ROWS_NEXT; i++)
                free(game->next[i]);
            free(game->next);
        }
        game->next = NULL;
    }
}

void remove_matrix_2(int **matrix)
{
    if (matrix)
    {
        for (int i = 0; i < ROWS_FIELD; i++)
            free(matrix[i]);
        free(matrix);
    }
}