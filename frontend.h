#ifndef FRONTEND_H
#define FRONTEND_H

#define BOARD_M 22
#define HUD_WIDTH 16
#define BOARDS_BEGIN 2

#define MVPRINTW(y, x, ...) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_pause(void);
int new_figure(int **matrix);
void update_TetrisField(int **field);
void change_color(int i, int j, int color);
void print_next_figure(GameInfo_t *brick_game);
void next_figure_to_field(GameInfo_t *brick_game);

#endif