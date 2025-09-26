#ifndef DEFINES_H
#define DEFINES_H

typedef struct
{
    int x;
    int y;
} player_pos;

#define WIN_INIT(time)        \
    {                         \
        initscr();            \
        noecho();             \
        curs_set(0);          \
        keypad(stdscr, TRUE); \
        timeout(time);        \
    }

#define GET_USER_INPUT getch()

#define SUCCESS 0
#define ERROR 1

#define INTRO_MESSAGE "Press ENTER to start!"
#define INTRO_MESSAGE_LEN 21

#define ROWS_MAP 21 // количество строк поля
#define COLS_MAP 90

#define BOARD_N (ROWS_MAP + MAP_PADDING * 2)
#define BOARD_M 30
#define HUD_WIDTH 12
#define MAP_PADDING 3 // отступ от края игрового поля

#define BOARDS_BEGIN 2

#define PRINT_FROG(x, y) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), "@")
#define MVPRINTW(y, x, ...) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

typedef struct
{
    int score;
    int level;
    int speed;
    int lives;
    int won;
} game_stats_t;

typedef struct square
{
    int x1;
    int x2;
    int y1;
    int y2;
} square_t;

typedef struct
{
    char finish[BOARD_M + 2];
    char ways[ROWS_MAP + 2][COLS_MAP + 2];
} board_t;

typedef enum
{
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    REACH,
    COLLIDE,
    GAMEOVER,
    EXIT_STATE,
    FILE_ERROR_STATE
} frog_state;

typedef enum
{
    Start = 0,
    Pause = 1,
    Terminate = 2,
    Left = 3,
    Right = 4,
    Up = 5,
    Down = 6,
    Action
} UserAction_t;

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

typedef enum s21_result
{
    RETURN_OK = 0,
    RETURN_WRONG = 1,
} result_t;

void game_loop(void);
void print_overlay(void);
void stats_init(game_stats_t *stats);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

void print_test(square_t *sq);
void clear_test(void);
void change_color(int i, int j, int color);
UserAction_t get_signal(int user_input);
int new_figure(int **matrix);
void s21_copy_field(int **A, int **B);
int func_up_1(int state_fig, int **field);
void func_up_2(int state_fig, int **field);
void func_up_3(int state_fig, int **field);
int func_up_5(int state_fig, int **field);
void func_up_6(int state_fig, int **field);
int func_up_7(int state_fig, int **field);
void update_TetrisField(int **field);
void move_FigureDown(int **field);
void move_FigureLeft(int **field);

#endif
