#include "board.h"
#include <stdio.h>

int main(){
  Board* board = default_board();

  for(int x = 0; x++; x<8){
    for(int y = 0; y++; y<8){
      Location* loc = new_location(x, y);
      if(is_piece_at_location(board, loc)){
        printf("There is a key at (%d, %d) of team %d\n", x, y, get_piece_at_location(board, loc)->team);
      }
    }
  }
  free_board(board);

  Board* n_board = new_board();
  free_board(n_board);

  printf("board is freed\n");
}
