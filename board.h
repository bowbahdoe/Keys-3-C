#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "key.h"

typedef struct{
  int x;
  int y;
} Location;

Location* new_location(int x, int y);
void free_location(Location* loc);

typedef struct{
  Key* unlocked_keys[8][8];
  Key* locked_keys[8][8];
} Board;

Board* new_board(void);
void free_board(Board* board_to_free);

bool is_piece_at_location(Board* board, Location* loc);
void set_piece_at_location(Board* board, Location* loc, Key* piece);
Key* get_piece_at_location(Board* board, Location* loc);
Key* get_locked_piece_at_location(Board* board, Location* loc);
bool is_location_in_bounds(Location* loc);


#endif
