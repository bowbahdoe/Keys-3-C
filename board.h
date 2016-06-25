#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "key.h"

/*
Defines the structure which is the board

While we could make it dynamically expand and contract,
128 pointers is reasonable to expect to fit in memory
and greatly simplifies implementation
*/
typedef struct {
    Key* unlocked_keys[8][8];
    Key* locked_keys[8][8];
} Board;

/*
First we define the methods necissary for
creating and freeing the board in memory
*/
Board* new_board(void);
void free_board(Board* board_to_free);

/*
Then we get to the getters and setters,
which in this case abstract the specifics of the structure
and are used internally in the rest of the functions herein defined

Though we could just use the structure and access members directly,
this approach was chosen so we could have uniformity in how pieces are
retrieved
*/

void set_unlocked_piece_at_location  (Board* board, int x, int y, Key* piece);
void set_locked_piece_at_location    (Board* board, int x, int y, Key* piece);
Key* get_unlocked_piece_at_location  (Board* board, int x, int y);
Key* get_locked_piece_at_location    (Board* board, int x, int y);

/*
And helpers for removing a piece at the location
*/
void remove_unlocked_piece_at_location (Board* board, int x, int y);
void remove_locked_piece_at_location   (Board* board, int x, int y);

/*
These helpers create a key at the location and implicitly allocate
the space for that object
*/
void new_piece_at_location          (Board* board, int x, int y, Team team, Orientation orientation, bool is_locked);
void new_unlocked_piece_at_location (Board* board, int x, int y, Team team, Orientation orientation);
void new_locked_piece_at_location   (Board* board, int x, int y, Team team, Orientation orientation);

/*
removes keys from the location and returns the removed key
*/
Key* pop_unlocked_piece_at_location (Board* board, int x, int y);
Key* pop_locked_piece_at_location   (Board* board, int x, int y);

bool is_location_in_bounds(int x, int y);

/*
Gets information about a location on the board.
*/
bool is_unlocked_piece_at_location        (Board* board, int x, int y);
bool is_locked_piece_at_location          (Board* board, int x, int y);
bool is_unlocked_gold_piece_at_location   (Board* board, int x, int y);
bool is_unlocked_silver_piece_at_location (Board* board, int x, int y);
bool is_locked_gold_piece_at_location     (Board* board, int x, int y);
bool is_locked_silver_piece_at_location   (Board* board, int x, int y);


/*
User-side actions that can be taken, including locking and unlocking pieces
and moving pieces around
*/
void lock_piece_at_location   (Board* board, int x, int y);
void unlock_piece_at_location (Board* board, int x, int y);
void move_piece_to_location   (Board* board, int orig_x, int orig_y, int new_x, int new_y);

/*
Creates the default gameboard for the game
*/
Board* default_board(void);

#endif
