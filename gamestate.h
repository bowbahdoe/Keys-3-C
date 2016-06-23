#include "board.h"
#include "key.h"
typedef enum{
  gold_play,
  gold_respawning,
  gold_piece_selected,
  gold_win,
  silver_play,
  silver_respawning,
  silver_piece_selected,
  silver_win
} State;

typedef struct{
  State current_state;
  Board* gameboard;
  int selected_piece_x;
  int selected_piece_y;
} GameState;

GameState* new_GameState(void);
void free_GameState(GameState* gamestate_to_free);

char* get_board_as_JSON(void);
bool is_in_respawn_points(Team team, int x, int y);
void handle_click(GameState* gamestate, int x, int y);
