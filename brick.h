#ifndef BRICK_H
#define BRICK_H

#define SUCCESS 0
#define ERROR 1

#define WIN_INIT(time)        \
    {                         \
        initscr();            \
        noecho();             \
        curs_set(0);          \
        keypad(stdscr, TRUE); \
        timeout(time);        \
    }

void game_loop(void);

#endif