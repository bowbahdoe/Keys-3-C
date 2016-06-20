#include "board.h"
#include <stdio.h>

int main(){
  Board* board = default_board();

  for(int x = 0;x<8 ;x++ ){
    for(int y = 0;y<8;  y++){
      if(is_unlocked_piece_at_location(board, x, y)){
        printf("There is a key at (%d, %d) of team %d\n", x, y, get_unlocked_piece_at_location(board, x, y)->team);
      }else{
        printf("There is no key at (%d, %d)\n", x, y);
      }
    }
  }

  free_board(board);

  Board* n_board = new_board();
  free_board(n_board);

  printf("board is freed\n");
}
