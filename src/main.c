#include "brick_game/tetris/backend.h"
#include "brick_game/tetris/fsm.h"
#include "brick_game/tetris/tetris.h"
#include "gui/cli/frontend.h"

int main() {
  TetGame game = init_tet_game();
  game_screen();

  bool hold = false;

  while (game.action != Terminate) {
    hold = control(getch(), &game);

    switch (game.status) {
      case TETRIS_START:
        if (game.action == Start) {
          print_overlay();
          print_game_info(game.game_info);
          game.status = TETRIS_MOVEMENT;
        }
        break;
      case TETRIS_MOVEMENT:
        print_player(game.player);
        falling_figure(&game, &hold);
        userInput(&game, hold);
        game.status = status_check(&game, hold);
        break;
      case TETRIS_ATTACHINC:
        save_field(game.player, &game.game_info);
        full_row(&game);
        game.status = TETRIS_SPAWN;
        break;
      case TETRIS_SPAWN:
        game.status = spawn_figure(&game);
        print_game_info(game.game_info);
        break;
      case TETRIS_PAUSE:
        if (game.action == Pause) {
          attroff(A_BLINK);
          mvprintw(2, 4, "     ");
          game.status = TETRIS_MOVEMENT;
        }
        break;
      case TETRIS_GAMEOVER:
        print_game_over();
        game.game_info.score = 0;
        game.game_info.level = 1;
        game.game_info.speed = START_FALL_DELAY;

        if (game.action == Start) {
          field_clearing(game.game_info.field);
          print_game_info(game.game_info);
          game.status = TETRIS_MOVEMENT;
        }

        break;
    }
  }
  save_record(game.game_info.high_score);

  endwin();

  cleaning_tet_game(&game);

  return 0;
}
