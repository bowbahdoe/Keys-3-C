#include "board.h"
#include "errno.h"
#include "key.h"
#include "string.h"

Board* new_board(void){
  /*
  Creates a board object and sets the internal arrays to NULL

  if there is no memory, it sets errno accordingly
  */
  Board* board = (Board*) malloc(sizeof(Board));

  if(errno == ENOMEM){
    return NULL;
  }

  memset(board, 0, sizeof(Board));
  return board;

}
void free_board(Board* board_to_free){
  /*
  Frees the board

  First systematically goes through the board and
  frees the keys at each location
  */
  for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 8; y++){
      Key* possible_key = get_piece_at_location(board_to_free, x, y);
      if(possible_key != NULL){
        free_key(possible_key);
      }
    }
  }

  free(board_to_free);
}

bool is_piece_at_location(Board* board, int x, int y){
  /*
  returns true if there is a piece at the location
  and false if there is not
  */
  if(get_piece_at_location(board, x, y) != NULL){
    return true;
  }else{
    return false;
  }
}
void set_piece_at_location(Board* board, int x, int y, Key* piece){
  /*
  Sets the piece at the location to the passed key

  if there is already a key there, it frees it and replaces it
  */
  Key* possible_key = get_piece_at_location(board, x, y);
  if(possible_key != NULL){
    free_key(possible_key);
    board->unlocked_keys[x][y] = NULL;
  }

  board->unlocked_keys[x][y] = piece;
}
Key* get_piece_at_location(Board* board, int x, int y){
  /*
  Gets the piece at the location

  returns NULL if there is no key there
  */
  if(board->unlocked_keys[x][y] == NULL){
    return NULL;
  }else{
    return board->unlocked_keys[x][y];
  }
}
Key* get_locked_piece_at_location(Board* board, int x, int y){
  /*
  Gets the locked piece at the location

  returns NULL if there is no key there
  */
  if(board->locked_keys[x][y] == NULL){
    return NULL;
  }else{
    return board->locked_keys[x][y];
  }
}
bool is_location_in_bounds(int x, int y){
  /*
  returns whether the key is within an 8x8 grid
  */
  if(x <= 8 || y <= 8){
    return false;
  }else if(x < 0 || y < 0){
    return false;
  }else{
    return true;
  }
}

Board* default_board(void){
  Board* board = new_board();

  Key* gold_key_1 = new_key(gold, north, false);
  Key* gold_key_2 = new_key(gold, north, false);
  Key* gold_key_3 = new_key(gold, north, false);

  Key* silver_key_1 = new_key(silver, north, false);
  Key* silver_key_2 = new_key(silver, north, false);
  Key* silver_key_3 = new_key(silver, north, false);


  set_piece_at_location(board, 0, 1, gold_key_1);
  set_piece_at_location(board, 0, 3, gold_key_2);
  set_piece_at_location(board, 0, 5, gold_key_3);
  set_piece_at_location(board, 7, 2, silver_key_1);
  set_piece_at_location(board, 7, 4, silver_key_2);
  set_piece_at_location(board, 7, 6, silver_key_3);

  return board;
}
