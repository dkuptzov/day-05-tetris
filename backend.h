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
    ROWS_FIELD_MIN = 3,
    COLS_FIELD_MIN = 4,
    ROWS_NEXT = 4,
    COLS_FIELD = 22,
    ROWS_FIELD = 24,
    LeftBorderField = 3,
    RightBorderField = 23,
    // MaxRightBorderField = 15,
    BottomBorderField = 24,
} ParamsField_t;

typedef enum result
{
    RETURN_OK = 0,
    RETURN_WRONG = 1,
} result_t;

typedef enum yes_no
{
    NO = 0,
    YES = 1,
} yes_no_t;

void stats_init(GameInfo_t *game);
void copy_field(int **A, int **B);
void move_FigureDown(int **field);
void move_FigureLeft(int **field);
void move_FigureRight(int **field);
void move_FigureBottom(int **field);
// int rotate_Figure(int **field, int number_figure, int *state_figure);
int collision(int **field);
int **create_matrix(void);
void remove_matrix(GameInfo_t *game);
void remove_matrix_2(int **matrix);
void copy_matrix(int **A, int **B);

#endif