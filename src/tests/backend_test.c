#include "stdio.h"
#include "tests.h"

START_TEST(random_figures_test) {
  TetGame game = init_tet_game();

  for (int test = 0; test < 10; test++) {
    int **array = random_figures(game);

    int n = 0;
    int cycle = 1;

    for (int i = 0; i < SIZE_FIGURES && cycle; i++) {
      for (int j = 0; j < SIZE_FIGURES && cycle; j++) {
        if (array[i][j] != game.figures[n].figure[i][j]) {
          i = 0;
          j = -1;
          n++;
        }
        if (n >= NUMBER_FIGURES) {
          cycle = 0;
        }
      }
    }
    ck_assert_int_eq(cycle, 1);
  }

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(copying_array_test) {
  TetGame game = init_tet_game();
  int **array = {0};
  array = memory_matrices(array, SIZE_FIGURES, SIZE_FIGURES);

  copying_array(array, game.figures[5].figure, SIZE_FIGURES, SIZE_FIGURES);

  int cycle = 1;
  for (int i = 0; i < SIZE_FIGURES && cycle; i++) {
    for (int j = 0; j < SIZE_FIGURES && cycle; j++) {
      if (array[i][j] != game.figures[5].figure[i][j]) {
        cycle = 0;
      }
    }
  }
  ck_assert_int_eq(cycle, 1);

  cleaning_tet_game(&game);
  cleaning_matrices(array, SIZE_FIGURES);
}

END_TEST

START_TEST(collision_check_test) {
  TetGame game = init_tet_game();

  int answer = 0;

  answer = collision_check(&game, true, false);
  ck_assert_int_eq(answer, 0);

  game.player.new_p_x = 12;

  answer = collision_check(&game, true, false);
  ck_assert_int_eq(answer, 1);

  game.player.new_p_y = 30;

  answer = collision_check(&game, true, false);
  ck_assert_int_eq(answer, 2);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(save_field_test) {
  TetGame game = init_tet_game();

  save_field(game.player, &game.game_info);

  int cycle = 1;
  int bloc = 0;

  for (int i = 0; i < HEIGHT_FIELD && cycle; i++) {
    for (int j = 0; j < WIDTH_FIELD && cycle; j++) {
      if (game.game_info.field[i][j] == 1) {
        bloc++;
      }
      if (bloc > 4) {
        cycle = 0;
      }
    }
  }

  if (bloc != 4) {
    cycle = 0;
  }

  ck_assert_int_eq(cycle, 1);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(spawn_figure_test) {
  TetGame game = init_tet_game();

  game.player.old_p_x = 9;
  game.player.old_p_y = 19;
  game.player.new_p_x = 9;
  game.player.new_p_y = 19;

  copying_array(game.game_info.next, game.figures[5].figure, SIZE_FIGURES,
                SIZE_FIGURES);

  spawn_figure(&game);

  ck_assert_int_eq(game.player.old_p_x, START_POS_X);
  ck_assert_int_eq(game.player.old_p_y, START_POS_Y);
  ck_assert_int_eq(game.player.new_p_x, START_POS_X);
  ck_assert_int_eq(game.player.new_p_y, START_POS_Y);

  int cycle = 1;
  for (int i = 0; i < SIZE_FIGURES && cycle; i++) {
    for (int j = 0; j < SIZE_FIGURES && cycle; j++) {
      if (game.player.fig[i][j] != game.figures[5].figure[i][j]) {
        cycle = 0;
      }
    }
  }

  ck_assert_int_eq(cycle, 1);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(full_row_test) {
  TetGame game = init_tet_game();

  for (int i = 0; i < WIDTH_FIELD; i++) {
    game.game_info.field[19][i] = 1;
  }

  full_row(&game);

  ck_assert_int_eq(game.game_info.score, 100);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(scoring_test) {
  TetGame game = init_tet_game();

  scoring(&game, 2);
  ck_assert_int_eq(game.game_info.score, 300);

  scoring(&game, 3);
  ck_assert_int_eq(game.game_info.score, 1000);

  scoring(&game, 4);
  ck_assert_int_eq(game.game_info.score, 2500);

  ck_assert_int_eq(game.game_info.level, 5);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(rotation_fig_test) {
  TetGame game = init_tet_game();

  copying_array(game.player.fig, game.figures[0].figure, SIZE_FIGURES,
                SIZE_FIGURES);

  rotation_fig(&game);

  int cycle = 1;
  for (int i = 0, n = SIZE_FIGURES - 1; i < SIZE_FIGURES && cycle; i++, n--) {
    for (int j = 0; j < SIZE_FIGURES && cycle; j++) {
      if (game.player.fig[j][n] != game.figures[0].figure[i][j]) {
        cycle = 0;
      }
    }
  }
  ck_assert_int_eq(cycle, 1);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(status_check_test) {
  TetGame game = init_tet_game();

  game.action = Pause;
  ck_assert_int_eq(status_check(&game, true), TETRIS_PAUSE);

  ck_assert_int_eq(status_check(&game, false), TETRIS_MOVEMENT);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(control_test) {
  TetGame game = init_tet_game();

  control(ERR, &game);
  ck_assert_int_eq(game.action, NoKey);
  userInput(&game, true);

  control(KEY_UP, &game);
  ck_assert_int_eq(game.action, Up);
  userInput(&game, true);

  control(KEY_DOWN, &game);
  ck_assert_int_eq(game.action, Down);
  userInput(&game, true);

  control(KEY_LEFT, &game);
  ck_assert_int_eq(game.action, Left);
  userInput(&game, true);

  control(KEY_RIGHT, &game);
  ck_assert_int_eq(game.action, Right);
  userInput(&game, true);

  control('q', &game);
  ck_assert_int_eq(game.action, Terminate);
  userInput(&game, true);

  control('z', &game);
  ck_assert_int_eq(game.action, Action);
  userInput(&game, true);

  control('p', &game);
  ck_assert_int_eq(game.action, Pause);
  userInput(&game, true);

  control('s', &game);
  ck_assert_int_eq(game.action, Start);
  userInput(&game, true);

  cleaning_tet_game(&game);
}

END_TEST

START_TEST(falling_figure_test) {
  TetGame game = init_tet_game();

  bool hold = false;

  int i = 0;
  for (; !hold; i++) {
    falling_figure(&game, &hold);
  }

  ck_assert_int_eq(i, 71);

  cleaning_tet_game(&game);
}

END_TEST

Suite *backend_test() {
  Suite *s;
  TCase *tc_random_figures_test, *tc_copying_array_test,
      *tc_collision_check_test, *tc_save_field_test, *tc_spawn_figure_test,
      *tc_full_row_test, *tc_scoring_test, *tc_rotation_fig_test,
      *tc_status_check_test, *tc_control_test, *tc_falling_figure_test;

  s = suite_create("backend_test");

  tc_random_figures_test = tcase_create("random_figures_test");
  tcase_add_test(tc_random_figures_test, random_figures_test);
  suite_add_tcase(s, tc_random_figures_test);

  tc_copying_array_test = tcase_create("copying_array_test");
  tcase_add_test(tc_copying_array_test, copying_array_test);
  suite_add_tcase(s, tc_copying_array_test);

  tc_collision_check_test = tcase_create("collision_check_test");
  tcase_add_test(tc_collision_check_test, collision_check_test);
  suite_add_tcase(s, tc_collision_check_test);

  tc_save_field_test = tcase_create("save_field_test");
  tcase_add_test(tc_save_field_test, save_field_test);
  suite_add_tcase(s, tc_save_field_test);

  tc_spawn_figure_test = tcase_create("spawn_figure_test");
  tcase_add_test(tc_spawn_figure_test, spawn_figure_test);
  suite_add_tcase(s, tc_spawn_figure_test);

  tc_full_row_test = tcase_create("full_row_test");
  tcase_add_test(tc_full_row_test, full_row_test);
  suite_add_tcase(s, tc_full_row_test);

  tc_scoring_test = tcase_create("scoring_test");
  tcase_add_test(tc_scoring_test, scoring_test);
  suite_add_tcase(s, tc_scoring_test);

  tc_rotation_fig_test = tcase_create("rotation_fig_test");
  tcase_add_test(tc_rotation_fig_test, rotation_fig_test);
  suite_add_tcase(s, tc_rotation_fig_test);

  tc_status_check_test = tcase_create("status_check_test");
  tcase_add_test(tc_status_check_test, status_check_test);
  suite_add_tcase(s, tc_status_check_test);

  tc_control_test = tcase_create("control_test");
  tcase_add_test(tc_control_test, control_test);
  suite_add_tcase(s, tc_control_test);

  tc_falling_figure_test = tcase_create("falling_figure_test");
  tcase_add_test(tc_falling_figure_test, falling_figure_test);
  suite_add_tcase(s, tc_falling_figure_test);

  return s;
}
