GameState* new_GameState(void){
  GameState* gamestate = (Board*) malloc(sizeof(GameState));

  if(errno == ENOMEM){
    return NULL;
  }

  gamestate->
  return gamestate;

}
void free_GameState(GameState* gamestate_to_free){
  free_board(gamestate_to_free->gameboard);
  free(gamestate_to_free);
}

char* get_board_as_JSON(void);
void handle_click(GameState* gamestate, int x, int y){
  switch(gamestate->state){
    case gold_play:
      if(is_unlocked_gold_piece_at_location(gamestate->gameboard, x, y)){
        gamestate->state = gold_piece_selected
        gamestate->selected_piece_x = x;
        gamestate->selected_piece_y = y;
      }
    case gold_respawning:
    case gold_piece_selected:
    case silver_play:
      if(is_unlocked_silver_piece_at_location(gamestate->gameboard, x, y)){
        gamestate->state = gold_piece_selected
        gamestate->selected_piece_x = x;
        gamestate->selected_piece_y = y;
      }
    case silver_respawning:
    case silver_piece_selected:
  }
}
