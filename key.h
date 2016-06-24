#ifndef _KEY_H
#define _KEY_H

#include <stdbool.h>

/*
Since a key needs to represent
it's direction, we define an enum for that

InvalidDirection is used by later functions,
and a key should never be set with that direction
*/
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

/*
There is no real need for an invalid team, so
that is not defined, unlike for direction

That being said, the team enum is needed to seperate the keys
*/
typedef enum {
  gold,
  silver
} Team;

/*
Structure to define a key
*/
typedef struct {
  Team team;
  Orientation orientation;
  bool is_locked;
} Key;

/*
While we make a constructor, we intend the internals of this
structure to be accessed directly, as the internals are unlikely
to change, and the syntactic overhead added by the encapsulation approach
is not worth it in this case
*/

Key* new_key(Team team, Orientation orientation, bool is_locked);
void free_key(Key* key);

#endif
