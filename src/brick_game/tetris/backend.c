#include "backend.h"

#include "../../gui/cli/frontend.h"
#include "tetris.h"

int** random_figures(TetGame game) {
  srand(time(NULL));
  int random_fig = rand() % 7;

  return game.figures[random_fig].figure;
}

void copying_array(int** copied_array, int** copying_array, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      copied_array[i][j] = copying_array[i][j];
    }
  }
}

void falling_figure(TetGame* game, bool* hold) {
  nanosleep(&game->time_delay, NULL);

  if (game->fall_delay-- <= 0) {
    game->action = Down;
    game->fall_delay = game->game_info.speed;
    *hold = true;
  }
}

bool control(int key, TetGame* game) {
  bool answer = true;

  if (key == ERR) {
    answer = false;
    game->action = NoKey;

  } else {
    if (key == KEY_UP) {
      game->action = Up;
    } else if (key == KEY_DOWN) {
      game->action = Down;
    } else if (key == KEY_LEFT) {
      game->action = Left;
    } else if (key == KEY_RIGHT) {
      game->action = Right;
    } else if (key == 'q') {
      game->action = Terminate;
    } else if (key == 'z') {
      game->action = Action;
    } else if (key == 'p') {
      game->action = Pause;
    } else if (key == 's') {
      game->action = Start;
    }
    game->fall_delay++;
  }

  return answer;
}

void userInput(TetGame* game, bool hold) {
  if (hold) {
    switch (game->action) {
      case Down:
        game->player.new_p_y++;
        game->fall_delay = game->game_info.speed;
        break;
      case Left:
        game->player.new_p_x--;
        break;
      case Right:
        game->player.new_p_x++;
        break;
      case Action:
        if (game->player.rotate_fig) {
          rotation_fig(game);
        }
        break;

      default:
        break;
    }
  }
}

int collision_check(TetGame* game, bool hold, bool rotation) {
  int answer = 0;

  if (hold) {
    bool cycle = true;

    for (int i = 0; i < SIZE_FIGURES && cycle; i++) {
      for (int j = 0; j < SIZE_FIGURES && cycle; j++) {
        if (game->player.fig[i][j] == 1 && (FIELD_BOUNDARIES || OTHER_BLOCKS)) {
          game->player.new_p_x = game->player.old_p_x;
          cycle = false;
          answer = 1;
        }

        if (!rotation && game->player.fig[i][j] == 1 &&
            (END_FIELD || OTHER_BLOCKS)) {
          cycle = false;
          answer = 2;
        }
      }
    }
  }

  return answer;
}

void save_field(Object player, GameInfo_t* game_info) {
  for (int i = 0; i < SIZE_FIGURES; i++) {
    for (int j = 0; j < SIZE_FIGURES; j++) {
      if (player.fig[i][j] == 1) {
        game_info->field POSITION_FIGURE = player.fig[i][j];
      }
    }
  }
}

int spawn_figure(TetGame* game) {
  int status = TETRIS_MOVEMENT;

  game->player.old_p_x = START_POS_X;
  game->player.old_p_y = START_POS_Y;
  game->player.new_p_x = START_POS_X;
  game->player.new_p_y = START_POS_Y;

  game->player.rotate_fig = true;
  if (SQUARE) {
    game->player.rotate_fig = false;
  }

  copying_array(game->player.fig, game->game_info.next, SIZE_FIGURES,
                SIZE_FIGURES);
  copying_array(game->game_info.next, random_figures(*game), SIZE_FIGURES,
                SIZE_FIGURES);

  if (collision_check(game, true, false)) {
    status = TETRIS_GAMEOVER;
  }

  return status;
}

void full_row(TetGame* game) {
  int number_lines = 0;
  int** another_array = {0};
  another_array = memory_matrices(another_array, HEIGHT_FIELD, WIDTH_FIELD);

  for (int i = HEIGHT_FIELD - 1, n = HEIGHT_FIELD - 1; i > -1; i--) {
    bool full_r = true;

    for (int j = WIDTH_FIELD - 1; j > -1; j--) {
      another_array[n][j] = game->game_info.field[i][j];

      if (game->game_info.field[i][j] == 0) {
        full_r = false;
      }
    }

    if (!full_r) {
      n--;
    } else {
      number_lines++;
    }
  }

  if (number_lines) {
    scoring(game, number_lines);
  }

  copying_array(game->game_info.field, another_array, HEIGHT_FIELD,
                WIDTH_FIELD);
  cleaning_matrices(another_array, HEIGHT_FIELD);
}

void scoring(TetGame* game, int number_lines) {
  if (number_lines == 1) {
    game->game_info.score += 100;
  } else if (number_lines == 2) {
    game->game_info.score += 300;
  } else if (number_lines == 3) {
    game->game_info.score += 700;
  } else if (number_lines == 4) {
    game->game_info.score += 1500;
  }

  if (game->game_info.score > game->game_info.high_score) {
    game->game_info.high_score = game->game_info.score;
  }

  while (game->game_info.level < 10 &&
         game->game_info.score >= game->game_info.level * NUMBER_NEW_LEVEL) {
    game->game_info.level++;
    game->game_info.speed -= 5;
    game->fall_delay = game->game_info.speed;
  }
}

void rotation_fig(TetGame* game) {
  int** another_array = {0};
  another_array = memory_matrices(another_array, SIZE_FIGURES, SIZE_FIGURES);
  copying_array(another_array, game->player.fig, SIZE_FIGURES, SIZE_FIGURES);
  cleaning_player(game->player);

  for (int i = 0, n = SIZE_FIGURES - 1; i < SIZE_FIGURES; i++, n--) {
    for (int j = 0; j < SIZE_FIGURES; j++) {
      game->player.fig[j][n] = another_array[i][j];
    }
  }

  if (collision_check(game, true, true)) {
    copying_array(game->player.fig, another_array, SIZE_FIGURES, SIZE_FIGURES);
  }

  cleaning_matrices(another_array, SIZE_FIGURES);
}

void field_clearing(int** field) {
  for (int i = 0; i < HEIGHT_FIELD; i++) {
    for (int j = 0; j < WIDTH_FIELD; j++) {
      field[i][j] = 0;
    }
  }
}

int status_check(TetGame* game, bool hold) {
  int status = TETRIS_MOVEMENT;
  bool cycle = true;

  if (hold && game->action == Pause) {
    attron(A_BLINK);
    mvprintw(2, 4, "PAUSE");
    status = TETRIS_PAUSE;
    cycle = false;
  }

  while (cycle) {
    if (collision_check(game, hold, false) == 2) {
      status = TETRIS_ATTACHINC;

    } else {
      cleaning_player(game->player);
      game->player.old_p_x = game->player.new_p_x;
      game->player.old_p_y = game->player.new_p_y;
    }

    if (game->action != Up || status == TETRIS_ATTACHINC) {
      cycle = false;
    }

    else {
      game->player.new_p_y++;
    }
  }

  return status;
}
