#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include "fsm.h"

void stats_init(GameInfo_t *game)
{
    int **field = NULL, **next = NULL;
    field = (int **)calloc(BottomBorderField, sizeof(double *));
    for (int i = 0; i < BottomBorderField; i++)
    {
        field[i] = (int *)calloc(MaxRightBorderField, sizeof(double));
        if (field[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(field[j]);
            free(field);
        }
    }
    for (int j = 4; j < RightBorderField; j++)
        field[BottomBorderField - 1][j] = 2;
    next = (int **)calloc(4, sizeof(double *));
    for (int i = 0; i < 4; i++)
    {
        next[i] = (int *)calloc(MaxRightBorderField, sizeof(double));
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
    for (int i = 22; i > 2; i--)
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
}

int move_FigureLeft(int **field)
{
    int stop_round = 0;
    for (int i = 22; i > 2 && stop_round == 0; i--)
    {
        for (int j = 4; j <= RightBorderField && stop_round == 0; j++)
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
    return stop_round;
}