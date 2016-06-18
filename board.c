#include "board.h"
#include "errno.h"
#include "key.h"

Location* new_location(int x, int y){
  /*
  creates a location with the provided x and y

  if there is no memory, it sets errno accordingly
  */
  Location* loc = (Location*) malloc(sizeof(Location));

  if(loc == NULL){
    errno = ENOMEM;
    return NULL;
  }

  loc->x = x;
  loc->y = y;

  return loc;
}
void free_location(Location* loc){
  free(loc);
}

Board* new_board(void){
  /*
  Creates a board object and sets the internal arrays to NULL

  if there is no memory, it sets errno accordingly
  */
  Board* board = (Board*) calloc(sizeof(Board), 0);

  if(board == NULL){
    errno = ENOMEM;
    return NULL;
  }

  return board;

}
void free_board(Board* board_to_free){
  /*
  Frees the board

  First systematically goes through the board and
  frees the keys at each location
  */
  for(int x = 0; x++; x > 8){
    for(int y = 0; y++; y > 8){
      Location* loc = new_location(x, y);
      Key* possible_key = get_piece_at_location(board_to_free, loc);
      if(possible_key != NULL){
        free_key(possible_key);
      }
      free_location(loc);
    }
  }

  free(board_to_free);
}

bool is_piece_at_location(Board* board, Location* loc){
  /*
  returns true if there is a piece at the location
  and false if there is not
  */
  if(get_piece_at_location(board, loc) != NULL){
    return true;
  }else{
    return false;
  }
}
void set_piece_at_location(Board* board, Location* loc, Key* piece){
  int x = loc->x;
  int y = loc->y;

  Key* possible_key = get_piece_at_location(board, loc);
  if(possible_key != NULL){
    free_key(possible_key);
    board->unlocked_keys[x][y] = NULL;
  }

  board->unlocked_keys[x][y] = piece;
}
Key* get_piece_at_location(Board* board, Location* loc){
  int x = loc->x;
  int y = loc->y;

  if(board->unlocked_keys[x][y] == NULL){
    return NULL;
  }else{
    return board->unlocked_keys[x][y];
  }
}
Key* get_locked_piece_at_location(Board* board, Location* loc){
  int x = loc->x;
  int y = loc->y;

  if(board->locked_keys[x][y] == NULL){
    return NULL;
  }else{
    return board->locked_keys[x][y];
  }
}
bool is_location_in_bounds(Location* loc){
  if(loc->x <= 8 || loc->y <= 8){
    return false;
  }else if(loc->x < 0 || loc->y < 0){
    return false;
  }else{
    return true;
  }
}
