/*
 * Keys: A board game technically
 * Copyright (C) 2016 Ethan McCue
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
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

typedef enum{
    Nothing,
    GoldNorth_Nothing,
    GoldNorthEast_Nothing,
    GoldEast_Nothing,
    GoldSouthEast_Nothing,
    GoldSouth_Nothing,
    GoldSouthWest_Nothing,
    GoldWest_Nothing,
    GoldNorthWest_Nothing,
    SilverNorth_Nothing,
    SilverNorthEast_Nothing,
    SilverEast_Nothing,
    SilverSouthEast_Nothing,
    SilverSouth_Nothing,
    SilverSouthWest_Nothing,
    SilverWest_Nothing,
    SilverNorthWest_Nothing,
    GoldNorth_Silver,
    GoldNorthEast_Silver,
    GoldEast_Silver,
    GoldSouthEast_Silver,
    GoldSouth_Silver,
    GoldSouthWest_Silver,
    GoldWest_Silver,
    GoldNorthWest_Silver,
    SilverNorth_Gold,
    SilverNorthEast_Gold,
    SilverEast_Gold,
    SilverSouthEast_Gold,
    SilverSouth_Gold,
    SilverSouthWest_Gold,
    SilverWest_Gold,
    SilverNorthWest_Gold,
}SquareState;