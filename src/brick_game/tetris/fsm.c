#include "fsm.h"

#include "backend.h"
#include "stdio.h"
#include "tetris.h"

int reading_file() {
  int answer = 0;

  FILE *file = fopen(FILES_NAME, "r");
  if (file != NULL) {
    while (fscanf(file, "%d", &answer) != EOF) {
    }

    fclose(file);
  }

  return answer;
}

void save_record(int score) {
  if (score > reading_file()) {
    FILE *file = fopen(FILES_NAME, "w");
    fprintf(file, "%d\n", score);

    fclose(file);
  }
}

int **memory_matrices(int **matrices, int row, int col) {
  matrices = (int **)calloc(row, sizeof(int *));

  for (int i = 0; i < row; i++) {
    matrices[i] = (int *)calloc(col, sizeof(int));
  }

  return matrices;
}

void init_templates(TetGame *game) {
  for (int i = 0; i < NUMBER_FIGURES; i++) {
    TemplateFigures fig = {};
    fig.figure = memory_matrices(fig.figure, SIZE_FIGURES, SIZE_FIGURES);

    if (i == 0) {
      INIT_ARRAY(fig.figure, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                 1, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 1) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 2) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 3) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 4) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 5) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    } else if (i == 6) {
      INIT_ARRAY(fig.figure, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0);
    }

    game->figures[i] = fig;
  }
}

void init_info(TetGame *game) {
  GameInfo_t info = {};

  info.field = memory_matrices(info.field, HEIGHT_FIELD, WIDTH_FIELD);
  info.next = memory_matrices(info.next, SIZE_FIGURES, SIZE_FIGURES);

  info.score = 0;
  info.high_score = reading_file();
  info.level = 1;
  info.speed = START_FALL_DELAY;
  info.pause = 0;

  game->game_info = info;
}

void init_object(TetGame *game) {
  Object player = {};

  player.fig = memory_matrices(player.fig, SIZE_FIGURES, SIZE_FIGURES);
  player.old_p_x = START_POS_X;
  player.old_p_y = START_POS_Y;
  player.new_p_x = START_POS_X;
  player.new_p_y = START_POS_Y;
  player.rotate_fig = true;

  game->player = player;
}

TetGame init_tet_game() {
  TetGame game;
  game.figures =
      (TemplateFigures *)calloc(NUMBER_FIGURES, sizeof(TemplateFigures));

  UserAction_t action = 0;
  game.action = action;

  Statuses status = 0;
  game.status = status;

  struct timespec time_delay = {DELAY_SECONDS, DELAY_NANOSECOND};
  game.time_delay = time_delay;

  init_templates(&game);
  init_info(&game);
  init_object(&game);

  srand(time(NULL));
  if (rand() % 7 == 3) {
    game.player.rotate_fig = false;
  }

  copying_array(game.player.fig, random_figures(game), SIZE_FIGURES,
                SIZE_FIGURES);
  copying_array(game.game_info.next, random_figures(game), SIZE_FIGURES,
                SIZE_FIGURES);

  game.fall_delay = START_FALL_DELAY;

  return game;
}

void cleaning_matrices(int **matrices, int row) {
  for (int i = 0; i < row; i++) {
    free(matrices[i]);
  }

  free(matrices);
}

void cleaning_tet_game(TetGame *game) {
  cleaning_matrices(game->game_info.field, HEIGHT_FIELD);
  cleaning_matrices(game->game_info.next, SIZE_FIGURES);
  cleaning_matrices(game->player.fig, SIZE_FIGURES);

  for (int i = 0; i < NUMBER_FIGURES; i++) {
    cleaning_matrices(game->figures[i].figure, SIZE_FIGURES);
  }

  free(game->figures);
}