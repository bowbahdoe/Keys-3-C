#include "key.h"
#include "errno.h"

Key* new_key(Team team, Orientation orientation, bool is_locked){
  Key* key = (Key*) malloc(sizeof(Key));

  if(key == NULL){
    errno = ENOMEM;
    return NULL;
  }

  key->team = team;
  key->orientation = orientation;
  key->is_locked = is_locked;
}

void free_key(Key* key){
  free(key);
}
