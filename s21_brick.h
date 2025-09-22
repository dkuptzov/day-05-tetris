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

void game_loop(void);
void print_overlay(void);
void stats_init(game_stats_t *stats);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

void print_test(square_t *sq);
void clear_test(void);

#endif
