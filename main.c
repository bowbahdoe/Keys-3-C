#include "board.h"
#include "gamestate.h"
#include <stdio.h>
void print_board(Board* board){
  for(int y = 7;y>-1 ;y-- ){
    for(int x = 0;x<8;  x++){
      if(is_unlocked_gold_piece_at_location(board, x, y)){
        printf("G ");
      }else if(is_unlocked_silver_piece_at_location(board, x, y)){
      printf("S ");
      }else{
        printf("* ");
      }
    }
    printf("  ");
    for(int x = 0;x<8;  x++){
      if(is_locked_gold_piece_at_location(board, x, y)){
        printf("G ");
      }else if(is_locked_silver_piece_at_location(board, x, y)){
      printf("S ");
      }else{
        printf("* ");
      }
    }
    printf("\n");
  }
}
int main(){

  GameState* g = new_GameState();



  int x;
  int y;
  print_board(g->gameboard);
  while(1){
    printf("x: ");
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y);
    if(x==-1){break;}
    handle_click(g, x, y);
    print_board(g->gameboard);
    printf("\n%d\n",g->current_state);
  }


  Board* n_board = new_board();
  free_board(n_board);
  printf("board is freed\n");
  printf("\n");

  printf("The size of a game state is %lu\n", sizeof(GameState));
  printf("The size of a board pointer is %lu\n", sizeof(GameState*));
  printf("The size of a board is %lu\n", sizeof(Board));
  printf("The size of a board pointer is %lu\n", sizeof(Board*));
  printf("The size of a key is %lu\n", sizeof(Key));
  printf("The size of a key pointer is %lu\n", sizeof(Key*));

}
