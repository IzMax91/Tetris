#ifndef BACKEND_H
#define BACKEND_H

#include "fsm.h"
#include "tetris.h"

int** random_figures(TetGame game);
void copying_array(int** copied_array, int** copying_array, int row, int col);

void falling_figure(TetGame* game, bool* hold);
bool control(int key, TetGame* game);
void userInput(TetGame* game, bool hold);
int collision_check(TetGame* game, bool hold, bool rotation);
void save_field(Object player, GameInfo_t* game_info);
int spawn_figure(TetGame* game);
void full_row(TetGame* game);
void scoring(TetGame* game, int number_lines);
void scoring(TetGame* game, int number_lines);
void rotation_fig(TetGame* game);
void field_clearing(int** field);

int status_check(TetGame* game, bool hold);

#endif  // BACKEND_H