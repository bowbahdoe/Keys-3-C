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
#include "game.h"

static Board gb;
static Key gold_1;
static Key gold_2;
static Key gold_3;
static Key silver_1;
static Key silver_2;
static Key silver_3;
static Key* key_store;
static GameState gs;

static void inititalize_data(void){
    /*
    sets the data for all structures to be as they should be for
    the start of a game
    */
    
    gold_1.team = gold;
    gold_2.team = gold;
    gold_3.team = gold;
    gold_1.orientation = north;
    gold_2.orientation = north;
    gold_3.orientation = north;
    
    silver_1.team = silver;
    silver_2.team = silver;
    silver_3.team = silver;
    silver_1.orientation = south;
    silver_2.orientation = south;
    silver_3.orientation = south;
    
    key_store = NULL;
    for(int i = 0; i<8; i++){
        for(int e = 0; e<8; e++){
            gb.unlocked_keys[i][e] = NULL;
            gb.locked_keys[i][e] = NULL;
        }
    }

    gb.unlocked_keys[1][0] = &gold_1;
    gb.unlocked_keys[3][0] = &gold_2;
    gb.unlocked_keys[5][0] = &gold_3;
    
    gb.unlocked_keys[2][7] = &silver_1;
    gb.unlocked_keys[4][7] = &silver_2;
    gb.unlocked_keys[6][7] = &silver_3;
    
    gs.current_state = gold_play;
}

/*
Begin Functions for handling the game board
*/
static inline bool is_in_bounds(int x, int y){
    /*
    returns whether the given location is within an 8x8 grid
    */

    return (x < 8 && y < 8 && x >= 0 && y >= 0);
}

static inline bool is_unlocked_piece_at_loc(int x, int y){
    /*
    returns whether there is an unlocked piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.unlocked_keys[x][y] != NULL));

}
static bool is_unlocked_gold_piece_at_loc(int x, int y){
    /*
    returns whether there is an unlocked gold piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.unlocked_keys[x][y] != NULL) &&
            (gb.unlocked_keys[x][y]->team == gold));
}
static inline bool is_unlocked_silver_piece_at_loc(int x, int y){
    /*
    returns whether there is an unlocked silver piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.unlocked_keys[x][y] != NULL) &&
            (gb.unlocked_keys[x][y]->team == silver));
}
static inline bool is_locked_piece_at_loc(int x, int y){
    /*
    returns whether there is an locked piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.locked_keys[x][y] != NULL));
}

static inline bool is_locked_gold_piece_at_loc(int x, int y){
    /*
    returns whether there is an locked gold piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.locked_keys[x][y] != NULL) &&
            (gb.locked_keys[x][y]->team == gold));
}
static inline bool is_locked_silver_piece_at_loc(int x, int y){
    /*
    returns whether there is an locked silver piece at the given location
    */
    return (is_in_bounds(x, y) &&
            (gb.locked_keys[x][y] != NULL) &&
            (gb.locked_keys[x][y]->team == silver));

}

void lock_piece_at_loc(int x, int y){
    /*
    locks the piece at the location.
    
    If there is already a locked piece there, does nothing
    */
    if(gb.locked_keys[x][y] == NULL){
        gb.locked_keys[x][y] = gb.unlocked_keys[x][y];
        gb.unlocked_keys[x][y] = NULL;
    }
}

void move_piece_to_location(int orig_x, int orig_y, int new_x, int new_y){
    if(is_unlocked_piece_at_loc(orig_x, orig_y) &&
       !is_unlocked_piece_at_loc(new_x,new_y))
    {
        Key* moving_piece = gb.unlocked_keys[orig_x][orig_y];
        gb.unlocked_keys[new_x][new_y] = moving_piece;
    }
}

/*
Begin Functions for handling game state
*/

bool 
is_in_respawn_points(Team team, int x, int y){
    switch(team){
        case gold:
            return ((y == 0) && (x == 1 || x == 3 || x == 5));
        case silver:
            return ((y == 7) && (x == 2 || x == 4 || x == 6));
        default:
            return false;
    }
}

bool 
is_in_allowed_movements(int x, int y){
    /*
    returns whether the currently selected key
    can move to the given spot
    
    if it isnt a movement turn, returns false
    */
    
    if(gs.current_state != silver_piece_selected &&
       gs.current_state != gold_piece_selected)
       return false;
       
    int piece_x = gs.selected_piece_x;
    int piece_y = gs.selected_piece_y;
    Key* piece = gb.unlocked_keys[piece_x][piece_y];

    while(is_in_bounds(piece_x, piece_y)){
        switch (piece->orientation) {
            case north:
                piece_y += 1;
                break;
            case northeast:
                piece_x += 1;
                piece_y += 1;
                break;
            case east:
                piece_x += 1;
                break;
            case southeast:
                piece_x += 1;
                piece_y -= 1;
                break;
            case south:
                piece_y -= 1;
                break;
            case southwest:
                piece_x -= 1;
                piece_y -= 1;
                break;
            case west:
                piece_x -= 1;
                break;
            case northwest:
                piece_x -= 1;
                piece_y += 1;
                break;
            default:
                return false;
        }
        if(is_unlocked_piece_at_loc(x, y)){
            if (gb.unlocked_keys[x][y]->team == piece->team){
                return false;
            }
        }
        if(piece_x == x && piece_y == y){
            return true;
        }
    }

    return false;
}

bool 
is_in_allowed_rotations(int x, int y){
    /*
    returns if the given point is within the allowed rotations
    of the selected piece
    
    if it isnt a movement turn, returns false
    */
    
    if(gs.current_state != silver_piece_selected &&
       gs.current_state != gold_piece_selected)
       return false;

    const int piece_x = gs.selected_piece_x;
    const int piece_y = gs.selected_piece_y;


    /*
    Premature Optimization
    */
    #define upleft    (piece_x - 1 == x && piece_y + 1 == y)
    #define up        (piece_x     == x && piece_y + 1 == y)
    #define upright   (piece_x + 1 == x && piece_y + 1 == y)
    #define right     (piece_x + 1 == x && piece_y     == y)
    #define downright (piece_x + 1 == x && piece_y - 1 == y)
    #define down      (piece_x     == x && piece_y - 1 == y)
    #define downleft  (piece_x - 1 == x && piece_y - 1 == y)
    #define left      (piece_x - 1 == x && piece_y     == y)
    
    return (is_in_bounds(x, y)
            && !is_in_allowed_movements(x, y)
            && (upleft || up || upright || right 
                || downright || down || downleft || left));
    
    #undef upleft
    #undef up
    #undef upright
    #undef right
    #undef downright
    #undef down
    #undef downleft
    #undef left
}

static Orientation 
get_orientation_indicated(int x, int y, int piece_x, int piece_y){
    if (piece_x == x && piece_y + 1 == y){
        return north;
    }else if (piece_x + 1 == x && piece_y + 1 == y){
        return northeast;
    }else if (piece_x + 1 == x && piece_y == y){
        return east;
    }else if (piece_x + 1 == x && piece_y - 1 == y){
        return southeast;
    }else if (piece_x == x && piece_y - 1 == y){
        return south;
    }else if (piece_x == x - 1 && piece_y - 1 == y){
        return southwest;
    }else if (piece_x == x - 1 && piece_y == y){
        return west;
    }else if (piece_x == x - 1 && piece_y + 1 == y){
        return northwest;
    }else{
        return InvalidDirection;
    }
}

static void gold_play_action(int x, int y){
    /*
    Handles input in the case of it being gold's turn w/
    no piece selected
    */
    if(is_unlocked_gold_piece_at_loc(x, y)){
        gs.current_state = gold_piece_selected;
        gs.selected_piece_x = x;
        gs.selected_piece_y = y;
    }
}

static void silver_play_action(int x, int y){
    /*
    Handles input in the case of it being silver's turn w/
    no piece selected
    */
    if(is_unlocked_silver_piece_at_loc(x, y)){
        gs.current_state = silver_piece_selected;
        gs.selected_piece_x = x;
        gs.selected_piece_y = y;
    }
}

/*static void gold_respawning_action(int x, int y){
    if(is_in_respawn_points(gold, x, y) && (!is_unlocked_piece_at_loc(x, y))){
        new_unlocked_piece_at_location(g->gameboard, x, y, gold, north);
        g->current_state = silver_play;
    }
    if(is_locked_gold_piece_at_location(g->gameboard, x, y)){
        remove_locked_piece_at_location(g->gameboard, x, y);
        g->current_state = gold_respawning;
    }
}*/

static void gold_piece_selected_action(int x, int y){
    if(is_in_allowed_movements(x, y)){
        if(is_locked_gold_piece_at_loc(x, y)){
            gs.current_state = gold_respawning;
        }else{
            gs.current_state = silver_play;
        }
        
        if(is_unlocked_silver_piece_at_loc(x, y)){
            lock_piece_at_loc(x, y);
        }
        move_piece_to_location(gs.selected_piece_x, gs.selected_piece_y, x, y);
    }

    else if(is_in_allowed_rotations(x, y)){
        Key* gold_piece = gb.unlocked_keys[gs.selected_piece_x]
                                          [gs.selected_piece_y];
        gold_piece->orientation = get_orientation_indicated(x, y,
                                                            gs.selected_piece_x,
                                                            gs.selected_piece_y);
        gs.current_state = silver_play;
    }
}

void handle_click(int x, int y){
    switch(gs.current_state){
        case gold_play:
            gold_play_action(x, y);
            break;
        case gold_respawning:
            //gold_respawning_action(x, y);
            break;
        case gold_piece_selected:
            gold_piece_selected_action(x, y);
            break;
        case gold_win:
            break;
        case silver_play:
            silver_play_action(x, y);
            break;
        case silver_respawning:
            //silver_respawning_action(x, y);
            break;
        case silver_piece_selected:
            //silver_piece_selected_action(x, y);
            break;
        case silver_win:
            break;
    }
}

void print_board(){
    for(int y = 7; y>=0; y--){
        for(int e = 7; e>=0; e--){
            handle_click(e,y);
            if(is_unlocked_gold_piece_at_loc(e,y)){
                printf("G");
                printf("%d",gb.unlocked_keys[e][y]-> orientation);
                printf(" ");
            }
            else if(is_unlocked_silver_piece_at_loc(e,y)){
                printf("S");
                printf("%d",gb.unlocked_keys[e][y]-> orientation);
                printf(" ");

            }
            else{
                printf("*  ");
            }
        }
        printf("\t\t");
        for(int x = 7; x>=0; x--){
            handle_click(x,y);
            if(is_locked_gold_piece_at_loc(x,y)){
                printf("G  ");
            }
            else if(is_locked_silver_piece_at_loc(x,y)){
                printf("S  ");

            }
            else{
                printf("*  ");
                
            }
        }
        printf("\n");
    } 
}
#ifdef debug
int main(){
    inititalize_data();
    handle_click(2,0);
    handle_click(1,0);
    printf("%d\n", gs.current_state);
    print_board();
    printf("%d\n", gs.current_state);
}
#endif