#include "frontend.h"

void print_overlay() {
  highlight(0, 0, 21, 11);
  highlight(0, 11, 21, 20);
  mvprintw(2, 15, "NEXT");
  mvprintw(8, 13, "RECORD");
  mvprintw(11, 14, "SCORE");
  mvprintw(14, 14, "LEVEL");
}

void print_start() {
  highlight(5, 0, 14, 11);
  mvprintw(6, 2, "TETRIS");
  mvprintw(8, 2, "s-start");
  mvprintw(9, 2, "q-exit");
}

void print_game_over() {
  highlight(5, 0, 14, 11);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 10; j++) {
      mvprintw(6 + i, 1 + j, " ");
    }
  }
  mvprintw(6, 2, "GAMEOVER");
  mvprintw(8, 2, "s-rest");
  mvprintw(9, 2, "q-exit");
}

void highlight(int x_1, int y_1, int x_2, int y_2) {
  for (int i = 0; i < y_2 - y_1; i++) {
    mvprintw(x_1, y_1 + i, HIGHLIGHT_SYMBOL);
  }
  for (int i = 0; i < y_2 - y_1; i++) {
    mvprintw(x_2, y_1 + i, HIGHLIGHT_SYMBOL);
  }
  for (int i = 0; i < x_2 - x_1; i++) {
    mvprintw(x_1 + i, y_1, HIGHLIGHT_SYMBOL);
  }
  for (int i = 0; i < x_2 - x_1 + 1; i++) {
    mvprintw(x_1 + i, y_2, HIGHLIGHT_SYMBOL);
  }
}

void print_fig(int **fig, int row, int col, int p_y, int p_x, char symbol,
               bool cover_with) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (fig[i][j] == 1) {
        mvprintw(p_y + i, p_x + j, "%c", symbol);
      } else if (cover_with) {
        mvprintw(p_y + i, p_x + j, "%c", ' ');
      }
    }
  }

  refresh();
}

void print_player(Object player) {
  print_fig(player.fig, SIZE_FIGURES, SIZE_FIGURES, player.new_p_y,
            player.new_p_x, BRICK_SYMBOL, false);
}

void cleaning_player(Object player) {
  print_fig(player.fig, SIZE_FIGURES, SIZE_FIGURES, player.old_p_y,
            player.old_p_x, ' ', false);
}

void print_game_info(GameInfo_t game_info) {
  print_fig(game_info.field, HEIGHT_FIELD, WIDTH_FIELD, 1, 1, BRICK_SYMBOL,
            true);
  print_fig(game_info.next, SIZE_FIGURES, SIZE_FIGURES, 3, 14, BRICK_SYMBOL,
            true);

  mvprintw(9, 13, "%6d", game_info.high_score);
  mvprintw(12, 13, "%6d", game_info.score);
  mvprintw(15, 13, "%6d", game_info.level);
}

void game_screen() {
  initscr();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  print_start();
}