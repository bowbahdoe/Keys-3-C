#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "key.h"

typedef struct{
  Key* unlocked_keys[8][8];
  Key* locked_keys[8][8];
} Board;

Board* new_board(void);
void free_board(Board* board_to_free);

bool is_piece_at_location(Board* board, int x, int y);
void set_piece_at_location(Board* board,int x, int y, Key* piece);
Key* get_piece_at_location(Board* board, int x, int y);
Key* get_locked_piece_at_location(Board* board, int x, int y);
bool is_location_in_bounds(int x, int y);

Board* default_board(void);

#endif
