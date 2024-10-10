#ifndef FSM_H
#define FSM_H

#include <stdlib.h>

#include "tetris.h"

typedef struct GameInfo_t {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct Object {
  int old_p_x;
  int old_p_y;
  int new_p_x;
  int new_p_y;
  int **fig;
  bool rotate_fig;
} Object;

typedef struct TemplateFigures {
  int **figure;
} TemplateFigures;

typedef enum {
  NoKey = 0,
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  TETRIS_START = 0,
  TETRIS_MOVEMENT,
  TETRIS_ATTACHINC,
  TETRIS_SPAWN,
  TETRIS_PAUSE,
  TETRIS_GAMEOVER
} Statuses;

typedef struct TetGame {
  GameInfo_t game_info;
  Object player;
  TemplateFigures *figures;
  UserAction_t action;
  Statuses status;
  struct timespec time_delay;

  int fall_delay;

} TetGame;

int reading_file();
void save_record(int score);

int **memory_matrices(int **matrices, int row, int col);
void init_templates(TetGame *game);
void init_info(TetGame *game);
void init_object(TetGame *game);
TetGame init_tet_game();

void cleaning_matrices(int **matrices, int row);
void cleaning_tet_game(TetGame *game);

#endif  // FSM_H