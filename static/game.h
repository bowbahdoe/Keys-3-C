#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
typedef enum {
    north,
    northeast,
    east,
    southeast,
    south,
    southwest,
    west,
    northwest,
    InvalidDirection
} Orientation;

typedef enum {
    gold,
    silver
} Team;

typedef struct {
    Team team;
    Orientation orientation;
    bool is_locked;
} Key;

typedef struct {
    Key* unlocked_keys[8][8];
    Key* locked_keys[8][8];
} Board;

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
  int selected_piece_x;
  int selected_piece_y;
} GameState;