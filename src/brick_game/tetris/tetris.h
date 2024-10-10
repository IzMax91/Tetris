#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <string.h>
#include <time.h>

#define INIT_ARRAY(array, el_0_0, el_0_1, el_0_2, el_0_3, el_0_4, el_1_0, el_1_1, el_1_2, el_1_3,  \
                   el_1_4, el_2_0, el_2_1, el_2_2, el_2_3, el_2_4, el_3_0, el_3_1, el_3_2, el_3_3, \
                   el_3_4, el_4_0, el_4_1, el_4_2, el_4_3, el_4_4)                                 \
  array[0][0] = el_0_0;                                                                            \
  array[0][1] = el_0_1;                                                                            \
  array[0][2] = el_0_2;                                                                            \
  array[0][3] = el_0_3;                                                                            \
  array[0][4] = el_0_4;                                                                            \
  array[1][0] = el_1_0;                                                                            \
  array[1][1] = el_1_1;                                                                            \
  array[1][2] = el_1_2;                                                                            \
  array[1][3] = el_1_3;                                                                            \
  array[1][4] = el_1_4;                                                                            \
  array[2][0] = el_2_0;                                                                            \
  array[2][1] = el_2_1;                                                                            \
  array[2][2] = el_2_2;                                                                            \
  array[2][3] = el_2_3;                                                                            \
  array[2][4] = el_2_4;                                                                            \
  array[3][0] = el_3_0;                                                                            \
  array[3][1] = el_3_1;                                                                            \
  array[3][2] = el_3_2;                                                                            \
  array[3][3] = el_3_3;                                                                            \
  array[3][4] = el_3_4;                                                                            \
  array[4][0] = el_4_0;                                                                            \
  array[4][1] = el_4_1;                                                                            \
  array[4][2] = el_4_2;                                                                            \
  array[4][3] = el_4_3;                                                                            \
  array[4][4] = el_4_4;

#define HEIGHT_FIELD 20
#define WIDTH_FIELD 10
#define NUMBER_FIGURES 7
#define SIZE_FIGURES 5
#define START_POS_X 4
#define START_POS_Y 1

#define FILES_NAME "high_score.txt"

#define HIGHLIGHT_SYMBOL "\""
#define BRICK_SYMBOL '#'

#define DELAY_SECONDS 0
#define DELAY_NANOSECOND 10000000
#define START_FALL_DELAY 70
#define NUMBER_NEW_LEVEL 600

#define MOVEMENT_SIDEWAY game->action == Left || game->action == Right
#define MOVEMENT_DOWN game->action == Down
#define FIELD_BOUNDARIES \
  game->player.new_p_x + j >= WIDTH_FIELD + 1 || game->player.new_p_x + j <= 0
#define END_FIELD game->player.new_p_y + i >= HEIGHT_FIELD + 1
#define OTHER_BLOCKS \
  game->game_info.field[(game->player.new_p_y + i - 1) % HEIGHT_FIELD][game->player.new_p_x + j - 1]

#define POSITION_FIGURE [player.old_p_y + i - 1][player.old_p_x + j - 1]

#define SQUARE \
  game->game_info.next[1][1] && game->game_info.next[1][2] && game->game_info.next[2][1]

extern int nanosleep(const struct timespec *req, struct timespec *rem);

#endif  // TETRIS_H