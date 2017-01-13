/*
 * Keys: A board game technically
 * Copyright (C) 2016 Ethan McCue
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#include <stdlib.h>
#include <check.h>
#include "../game.c"

START_TEST (test_bounds)
{
    ck_assert(is_in_bounds(0, 0) == true);
    ck_assert(is_in_bounds(1, 1) == true);
    ck_assert(is_in_bounds(7, 7) == true);
    ck_assert(is_in_bounds(8, 1) == false);
    ck_assert(is_in_bounds(1, 8) == false);
    ck_assert(is_in_bounds(-1, 8) == false);
    ck_assert(is_in_bounds(-1, 0) == false);
}
END_TEST

START_TEST(test_is_in_respawn_points)
{
    ck_assert(is_in_respawn_points(gold, 1, 0) == true);
    ck_assert(is_in_respawn_points(gold, 3, 0) == true);
    ck_assert(is_in_respawn_points(gold, 5, 0) == true);
    
    ck_assert(is_in_respawn_points(silver, 2, 7) == true);
    ck_assert(is_in_respawn_points(silver, 4, 7) == true);
    ck_assert(is_in_respawn_points(silver, 6, 7) == true);
    
    ck_assert(is_in_respawn_points(silver, 1, 7) == false);
    ck_assert(is_in_respawn_points(silver, 1, -7) == false);
    ck_assert(is_in_respawn_points(silver, 1, 3) == false);
    
    ck_assert(is_in_respawn_points(gold, 1, 3) == false);
    ck_assert(is_in_respawn_points(gold, 1, 5) == false);
    ck_assert(is_in_respawn_points(gold, 4, 3) == false);
    
}
END_TEST

START_TEST (test_initialize_data)
{
    inititalize_data();
    
    ck_assert(gold_1.team == gold);
    ck_assert(gold_2.team == gold);
    ck_assert(gold_3.team == gold);
    ck_assert(gold_1.orientation == north);
    ck_assert(gold_2.orientation == north);
    ck_assert(gold_3.orientation == north);
    
    ck_assert(silver_1.team == silver);
    ck_assert(silver_2.team == silver);
    ck_assert(silver_3.team == silver);
    ck_assert(silver_1.orientation == south);
    ck_assert(silver_2.orientation == south);
    ck_assert(silver_3.orientation == south);
    
    ck_assert(key_store == NULL);


    ck_assert(gb.unlocked_keys[1][0] == &gold_1);
    ck_assert(gb.unlocked_keys[3][0] == &gold_2);
    ck_assert(gb.unlocked_keys[5][0] == &gold_3);
    
    
    ck_assert(gb.unlocked_keys[2][7] == &silver_1);
    ck_assert(gb.unlocked_keys[4][7] == &silver_2);
    ck_assert(gb.unlocked_keys[6][7] == &silver_3);
    
    
    ck_assert(gb.unlocked_keys[0][0] == NULL);
    ck_assert(gb.unlocked_keys[0][1] == NULL);
    ck_assert(gb.unlocked_keys[0][2] == NULL);
    ck_assert(gb.unlocked_keys[0][3] == NULL);
    ck_assert(gb.unlocked_keys[0][4] == NULL);
    ck_assert(gb.unlocked_keys[0][5] == NULL);
    ck_assert(gb.unlocked_keys[0][6] == NULL);
    ck_assert(gb.unlocked_keys[0][7] == NULL);
    
    ck_assert(gb.unlocked_keys[1][1] == NULL);
    ck_assert(gb.unlocked_keys[1][2] == NULL);
    ck_assert(gb.unlocked_keys[1][3] == NULL);
    ck_assert(gb.unlocked_keys[1][4] == NULL);
    ck_assert(gb.unlocked_keys[1][5] == NULL);
    ck_assert(gb.unlocked_keys[1][6] == NULL);
    ck_assert(gb.unlocked_keys[1][7] == NULL);
    
    ck_assert(gb.unlocked_keys[2][0] == NULL);
    ck_assert(gb.unlocked_keys[2][1] == NULL);
    ck_assert(gb.unlocked_keys[2][2] == NULL);
    ck_assert(gb.unlocked_keys[2][3] == NULL);
    ck_assert(gb.unlocked_keys[2][4] == NULL);
    ck_assert(gb.unlocked_keys[2][5] == NULL);
    ck_assert(gb.unlocked_keys[2][6] == NULL);
    
    ck_assert(gb.unlocked_keys[3][1] == NULL);
    ck_assert(gb.unlocked_keys[3][2] == NULL);
    ck_assert(gb.unlocked_keys[3][3] == NULL);
    ck_assert(gb.unlocked_keys[3][4] == NULL);
    ck_assert(gb.unlocked_keys[3][5] == NULL);
    ck_assert(gb.unlocked_keys[3][6] == NULL);
    ck_assert(gb.unlocked_keys[3][7] == NULL);
    
    ck_assert(gb.unlocked_keys[4][0] == NULL);
    ck_assert(gb.unlocked_keys[4][1] == NULL);
    ck_assert(gb.unlocked_keys[4][2] == NULL);
    ck_assert(gb.unlocked_keys[4][3] == NULL);
    ck_assert(gb.unlocked_keys[4][4] == NULL);
    ck_assert(gb.unlocked_keys[4][5] == NULL);
    ck_assert(gb.unlocked_keys[4][6] == NULL);
    
    ck_assert(gb.unlocked_keys[5][1] == NULL);
    ck_assert(gb.unlocked_keys[5][2] == NULL);
    ck_assert(gb.unlocked_keys[5][3] == NULL);
    ck_assert(gb.unlocked_keys[5][4] == NULL);
    ck_assert(gb.unlocked_keys[5][5] == NULL);
    ck_assert(gb.unlocked_keys[5][6] == NULL);
    ck_assert(gb.unlocked_keys[5][7] == NULL);
    
    ck_assert(gb.unlocked_keys[6][0] == NULL);
    ck_assert(gb.unlocked_keys[6][1] == NULL);
    ck_assert(gb.unlocked_keys[6][2] == NULL);
    ck_assert(gb.unlocked_keys[6][3] == NULL);
    ck_assert(gb.unlocked_keys[6][4] == NULL);
    ck_assert(gb.unlocked_keys[6][5] == NULL);
    ck_assert(gb.unlocked_keys[6][6] == NULL);
    
    ck_assert(gb.unlocked_keys[7][0] == NULL);
    ck_assert(gb.unlocked_keys[7][1] == NULL);
    ck_assert(gb.unlocked_keys[7][2] == NULL);
    ck_assert(gb.unlocked_keys[7][3] == NULL);
    ck_assert(gb.unlocked_keys[7][4] == NULL);
    ck_assert(gb.unlocked_keys[7][5] == NULL);
    ck_assert(gb.unlocked_keys[7][6] == NULL);
    ck_assert(gb.unlocked_keys[7][7] == NULL);

    
    ck_assert(gs.current_state == gold_play);
}
END_TEST

START_TEST(test_is_unlocked_piece_at_loc)
{
    inititalize_data();

    ck_assert(!is_unlocked_piece_at_loc(6, 1));
    ck_assert(!is_unlocked_piece_at_loc(0, 0));
    ck_assert(!is_unlocked_piece_at_loc(-1, 1));
    ck_assert(!is_unlocked_piece_at_loc(0, 20));
    
    ck_assert(is_unlocked_piece_at_loc(1, 0));
    ck_assert(is_unlocked_piece_at_loc(3, 0));
    ck_assert(is_unlocked_piece_at_loc(5, 0));
    ck_assert(is_unlocked_piece_at_loc(2, 7));
    ck_assert(is_unlocked_piece_at_loc(4, 7));
    ck_assert(is_unlocked_piece_at_loc(6, 7));
}
END_TEST

START_TEST(test_is_unlocked_gold_piece_at_loc)
{
    inititalize_data();

    ck_assert(!is_unlocked_gold_piece_at_loc(6, 1));
    ck_assert(!is_unlocked_gold_piece_at_loc(0, 0));
    ck_assert(!is_unlocked_gold_piece_at_loc(-1, 1));
    ck_assert(!is_unlocked_gold_piece_at_loc(0, 20));
    
    ck_assert(is_unlocked_gold_piece_at_loc(1, 0));
    ck_assert(is_unlocked_gold_piece_at_loc(3, 0));
    ck_assert(is_unlocked_gold_piece_at_loc(5, 0));
    
    ck_assert(!is_unlocked_gold_piece_at_loc(2, 7));
    ck_assert(!is_unlocked_gold_piece_at_loc(4, 7));
    ck_assert(!is_unlocked_gold_piece_at_loc(6, 7));
}
END_TEST

START_TEST(test_is_unlocked_silver_piece_at_loc)
{
    inititalize_data();

    ck_assert(!is_unlocked_silver_piece_at_loc(6, 1));
    ck_assert(!is_unlocked_silver_piece_at_loc(0, 0));
    ck_assert(!is_unlocked_silver_piece_at_loc(-1, 1));
    ck_assert(!is_unlocked_silver_piece_at_loc(0, 20));
    
    ck_assert(!is_unlocked_silver_piece_at_loc(1, 0));
    ck_assert(!is_unlocked_silver_piece_at_loc(3, 0));
    ck_assert(!is_unlocked_silver_piece_at_loc(5, 0));
    
    ck_assert(is_unlocked_silver_piece_at_loc(2, 7));
    ck_assert(is_unlocked_silver_piece_at_loc(4, 7));
    ck_assert(is_unlocked_silver_piece_at_loc(6, 7));
}
END_TEST

START_TEST(test_lock_piece_at_loc)
{
    inititalize_data();
    Team t;
    
    ck_assert(gb.unlocked_keys[1][0] != NULL);
    t = gb.unlocked_keys[1][0]->team;
    
    lock_piece_at_loc(1,0);
    
    ck_assert(gb.locked_keys[1][0] != NULL);
    ck_assert(gb.unlocked_keys[1][0] == NULL);
    t = gb.locked_keys[1][0]->team;


    ck_assert(gb.unlocked_keys[2][7] != NULL);
    t = gb.unlocked_keys[2][7]->team;
    
    lock_piece_at_loc(2,7);
    
    ck_assert(gb.locked_keys[2][7] != NULL);
    ck_assert(gb.unlocked_keys[2][7] == NULL);
    ck_assert(t = gb.locked_keys[2][7]->team);
    
    ck_assert(gb.unlocked_keys[0][0] == NULL);
    lock_piece_at_loc(0, 0);
    ck_assert(gb.unlocked_keys[0][0] == NULL);
    ck_assert(gb.locked_keys[0][0] == NULL);
    
    lock_piece_at_loc(1, 0);
    ck_assert(gb.locked_keys[1][0] != NULL);
    ck_assert(gb.unlocked_keys[1][0] == NULL);

    // TODO Add test case for overlapping pieces
}
END_TEST

START_TEST(test_get_orientation_indicated)
{
    ck_assert(get_orientation_indicated(1,1,0,0) == northeast);
    ck_assert(get_orientation_indicated(1,1,0,1) == east);
    // TODO add all directions
}
END_TEST

Suite * game_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Game");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_bounds);
    tcase_add_test(tc_core, test_initialize_data);
    tcase_add_test(tc_core, test_is_in_respawn_points);
    tcase_add_test(tc_core, test_is_unlocked_piece_at_loc);
    tcase_add_test(tc_core, test_is_unlocked_gold_piece_at_loc);
    tcase_add_test(tc_core, test_is_unlocked_silver_piece_at_loc);
    tcase_add_test(tc_core, test_lock_piece_at_loc);
    tcase_add_test(tc_core, test_get_orientation_indicated);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = game_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}