#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/fsm.h"
#include "../../brick_game/tetris/tetris.h"

void print_overlay();
void print_start();
void print_game_over();
void highlight(int x_1, int y_1, int x_2, int y_2);

void print_fig(int **fig, int row, int col, int p_y, int p_x, char symbol,
               bool cover_with);
void print_player(Object player);
void cleaning_player(Object player);

void print_game_info(GameInfo_t game_info);

void game_screen();

#endif  // FRONTEND_H