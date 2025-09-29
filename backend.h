#ifndef BACKEND_H
#define BACKEND_H

typedef struct
{
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef enum
{
    LeftBorderField = 3,
    RightBorderField = 13,
    MaxRightBorderField = 15,
    BottomBorderField = 24,
} ParamsField_t;

void stats_init(GameInfo_t *game);
void move_FigureDown(int **field);
int move_FigureLeft(int **field);
#endif