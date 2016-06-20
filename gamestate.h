#include "board.h"
typedef enum{
  gold_play,
  gold_respawning,
  gold_piece_selected,
  silver_play,
  silver_respawning,
  silver_piece_selected,
} State;

typedef struct{
  State current_state;
  Board* gameboard;
  int gamestate->selected_piece_x;
  int gamestate->selected_piece_y;
} GameState;

GameState* new_GameState(void);
void free_GameState(void);

char* get_board_as_JSON(void);
void handle_click(int x, int y);
