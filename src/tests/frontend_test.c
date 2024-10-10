#include "stdio.h"
#include "tests.h"

START_TEST(print_overlay_test) { print_overlay(); }

END_TEST

START_TEST(print_start_test) { print_start(); }

END_TEST

START_TEST(print_game_over_test) { print_game_over(); }

END_TEST

START_TEST(print_player_test) {
  TetGame game = init_tet_game();

  print_player(game.player);

  cleaning_tet_game(&game);
}

START_TEST(print_game_info_test) {
  TetGame game = init_tet_game();

  print_game_info(game.game_info);

  cleaning_tet_game(&game);
}

Suite *frontend_test() {
  Suite *s;
  TCase *tc_print_overlay_test, *tc_print_start_test, *tc_print_game_over_test,
      *tc_print_player_test, *tc_print_game_info_test;

  s = suite_create("frontend_test");

  tc_print_overlay_test = tcase_create("print_overlay_test");
  tcase_add_test(tc_print_overlay_test, print_overlay_test);
  suite_add_tcase(s, tc_print_overlay_test);

  tc_print_start_test = tcase_create("print_start_test");
  tcase_add_test(tc_print_start_test, print_start_test);
  suite_add_tcase(s, tc_print_start_test);

  tc_print_game_over_test = tcase_create("print_game_over_test");
  tcase_add_test(tc_print_game_over_test, print_game_over_test);
  suite_add_tcase(s, tc_print_game_over_test);

  tc_print_player_test = tcase_create("print_player_test");
  tcase_add_test(tc_print_player_test, print_player_test);
  suite_add_tcase(s, tc_print_player_test);

  tc_print_game_info_test = tcase_create("print_game_info_test");
  tcase_add_test(tc_print_game_info_test, print_game_info_test);
  suite_add_tcase(s, tc_print_game_info_test);

  return s;
}
