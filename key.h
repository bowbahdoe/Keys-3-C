#ifndef _KEY_H
#define _KEY_H


#include <stdbool.h>
#include <stdlib.h>

typedef enum {
  north,
  northeast,
  east,
  southeast,
  south,
  southwest,
  west,
  northwest
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

Key* new_key(Team team, Orientation orientation, bool is_locked);
void free_key(Key* key);

#endif
