#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "board.h"
#include "key.h"

Board* new_board(void){
  /*
  Creates a board object and sets the internal arrays to NULL

  if there is no memory, returns NULL
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
      Key* possible_key = get_unlocked_piece_at_location(board_to_free, x, y);
      if(possible_key != NULL){
        free_key(possible_key);
      }
    }
  }

  free(board_to_free);
}

void set_unlocked_piece_at_location(Board* board, int x, int y, Key* piece){
  /*
  Sets the piece at the location to the passed key

  if there is already a key there, it frees it and replaces it
  */
  if(!is_location_in_bounds(x, y)){
    return;
  }

  Key* possible_key = get_unlocked_piece_at_location(board, x, y);

  if(possible_key != NULL){
    free_key(possible_key);
    board->unlocked_keys[x][y] = NULL;
  }

  board->unlocked_keys[x][y] = piece;
}
void set_locked_piece_at_location(Board* board, int x, int y, Key* piece){
  /*
  Sets the piece at the location to the passed key

  if there is already a key there, it frees it and replaces it
  */
  if(!is_location_in_bounds(x, y)){
    return;
  }

  Key* possible_key = get_locked_piece_at_location(board, x, y);
  if(possible_key != NULL){
    free_key(possible_key);
    board->locked_keys[x][y] = NULL;
  }

  board->locked_keys[x][y] = piece;
}

Key* get_unlocked_piece_at_location(Board* board, int x, int y){
  /*
  Gets the unlocked piece at the location

  returns NULL if there is no key there
  */
  if(!is_location_in_bounds(x, y)){
    return NULL;
  }

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
  if(!is_location_in_bounds(x, y)){
    return NULL;
  }

  if(board->locked_keys[x][y] == NULL){
    return NULL;
  }else{
    return board->locked_keys[x][y];
  }
}

void remove_unlocked_piece_at_location(Board* board, int x, int y){
  /*
  Removes and frees the unlocked piece at the location
  */
  Key* possible_key = get_unlocked_piece_at_location(board, x, y);
  if(possible_key != NULL){
    set_unlocked_piece_at_location(board, x, y, NULL);
    free_key(possible_key);
  }
}

void remove_locked_piece_at_location(Board* board, int x, int y){
  /*
  Removes and frees the unlocked piece at the location
  */
  Key* possible_key = get_locked_piece_at_location(board, x, y);
  if(possible_key != NULL){
    set_locked_piece_at_location(board, x, y, NULL);
    free_key(possible_key);
  }
}


Key* pop_unlocked_piece_at_location(Board* board, int x, int y){
  /*
  Removes the unlocked key at the given location and returns that key

  if there is no Key, returns NULL
  */
  Key* piece = get_unlocked_piece_at_location(board, x, y);
  set_unlocked_piece_at_location(board, x, y, NULL);
  return piece;
}

Key* pop_locked_piece_at_location(Board* board, int x, int y){
  /*
  Removes the locked key at the given location and returns that key

  if there is no Key, returns NULL
  */
  Key* piece = get_locked_piece_at_location(board, x, y);
  set_unlocked_piece_at_location(board, x, y, NULL);
  return piece;
}


bool is_location_in_bounds(int x, int y){
  /*
  returns whether the given location is within an 8x8 grid
  */

  return (x < 8 && y < 8 && x >= 0 && y >= 0);
}

bool is_unlocked_piece_at_location(Board* board, int x, int y){
  if(get_unlocked_piece_at_location(board, x, y) != NULL){
    return true;
  }else{
    return false;
  }
}

bool is_locked_piece_at_location(Board* board, int x, int y){
  if(get_locked_piece_at_location(board, x, y) != NULL){
    return true;
  }else{
    return false;
  }
}

bool is_unlocked_gold_piece_at_location(Board* board, int x, int y){
  if(is_unlocked_piece_at_location(board, x, y)){
    Key* piece = get_unlocked_piece_at_location(board, x, y);
    switch(piece->team){
      case gold:
        return true;
      case silver:
        return false;
      default:
        return false;
    }
  }else{
    return false;
  }
}
bool is_unlocked_silver_piece_at_location(Board* board, int x, int y){
  if(is_unlocked_piece_at_location(board, x, y)){
    Key* piece = get_unlocked_piece_at_location(board, x, y);
    switch(piece->team){
      case gold:
        return false;
      case silver:
        return true;
      default:
        return false;
    }
  }else{
    return false;
  }
}

bool is_locked_gold_piece_at_location(Board* board, int x, int y){
  if(is_locked_piece_at_location(board, x, y)){
    Key* piece = get_locked_piece_at_location(board, x, y);
    switch(piece->team){
      case gold:
        return true;
      case silver:
        return false;
      default:
        return false;
    }
  }else{
    return false;
  }
}

bool is_locked_silver_piece_at_location(Board* board, int x, int y){
  if(is_unlocked_piece_at_location(board, x, y)){
    Key* piece = get_unlocked_piece_at_location(board, x, y);
    switch(piece->team){
      case gold:
        return false;
      case silver:
        return true;
      default:
        return false;
    }
  }else{
    return false;
  }
}



void lock_piece_at_location(Board* board, int x, int y){
  if(is_unlocked_piece_at_location(board, x, y)){
    get_unlocked_piece_at_location(board, x, y)->is_locked = true;
  }
  if(is_locked_piece_at_location(board, x, y)){
    remove_locked_piece_at_location(board, x, y);
  }

  Key* piece = pop_unlocked_piece_at_location(board, x, y);
  set_locked_piece_at_location(board, x, y, piece);

}

void unlock_piece_at_location(Board* board, int x, int y){
  if(is_locked_piece_at_location(board, x, y)){
    get_locked_piece_at_location(board, x, y)->is_locked = true;
  }
  if(is_unlocked_piece_at_location(board, x, y)){
    remove_unlocked_piece_at_location(board, x, y);
  }

  Key* piece = pop_locked_piece_at_location(board, x, y);
  set_unlocked_piece_at_location(board, x, y, piece);
}


void move_piece_to_location(Board* board, int orig_x, int orig_y, int new_x, int new_y){
  if(is_unlocked_piece_at_location(board, orig_x, orig_y)){
    if(is_unlocked_piece_at_location(board, new_x, new_y)){
      free_key(get_unlocked_piece_at_location(board, new_x, new_y));
      set_unlocked_piece_at_location(board, new_x, new_y, NULL);
    }
    Key* moving_piece = get_unlocked_piece_at_location(board, orig_x, orig_y);
    set_unlocked_piece_at_location(board, new_x, new_y, moving_piece);
    set_unlocked_piece_at_location(board, orig_x, orig_y, NULL);
  }

}

Board* default_board(void){
  /*
  Makes a new board in memory and fills it with
  6 keys, 3 of each team, at their designated spots
  */

  Board* board = new_board();

  Key* gold_key_1 = new_key(gold, north, false);
  Key* gold_key_2 = new_key(gold, north, false);
  Key* gold_key_3 = new_key(gold, north, false);

  Key* silver_key_1 = new_key(silver, north, false);
  Key* silver_key_2 = new_key(silver, north, false);
  Key* silver_key_3 = new_key(silver, north, false);


  set_unlocked_piece_at_location(board, 0, 1, gold_key_1);
  set_unlocked_piece_at_location(board, 0, 3, gold_key_2);
  set_unlocked_piece_at_location(board, 0, 5, gold_key_3);
  set_unlocked_piece_at_location(board, 7, 2, silver_key_1);
  set_unlocked_piece_at_location(board, 7, 4, silver_key_2);
  set_unlocked_piece_at_location(board, 7, 6, silver_key_3);

  return board;
}
