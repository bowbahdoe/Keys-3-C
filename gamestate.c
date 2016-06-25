#include <stdlib.h>
#include <errno.h>
#include "gamestate.h"

GameState* new_GameState(void){
    GameState* gamestate = (GameState*) malloc(sizeof(GameState));

    if(errno == ENOMEM){
        return NULL;
    }

    gamestate->gameboard = default_board();
    gamestate->current_state = gold_play;
    return gamestate;
}
void free_GameState(GameState* gamestate_to_free){
    free_board(gamestate_to_free->gameboard);
    free(gamestate_to_free);
}

bool is_in_respawn_points(Team team, int x, int y){
    switch(team){
        case gold:
            return ((y == 0) && (x == 1 || x == 3 || x == 5));
        case silver:
            return ((y == 7) && (x == 2 || x == 4 || x == 6));
        default:
            return false;
  }
}

bool is_in_allowed_movements(GameState* g, int x, int y){
    int piece_x = g->selected_piece_x;
    int piece_y = g->selected_piece_y;
    Key* piece = get_unlocked_piece_at_location(g->gameboard, piece_x, piece_y);
    Board* board = g->gameboard;

    while(is_location_in_bounds(piece_x, piece_y)){
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
        if(is_unlocked_piece_at_location(board, x, y)){
            if (get_unlocked_piece_at_location(board, x, y)->team == piece->team){
                return false;
            }
        }
        if(piece_x == x && piece_y == y){
            return true;
        }
    }

    return false;
}


bool is_in_allowed_rotations(GameState* g, int x, int y){
    int piece_x = g->selected_piece_x;
    int piece_y = g->selected_piece_y;

    for(int x_modifier = -1; x_modifier<2;x_modifier++){
        for(int y_modifier = -1; y_modifier<2;y_modifier++){
            if(y_modifier != 0 || x_modifier != 0){
                if(piece_x + x_modifier == x && piece_y + y_modifier == y
                   && is_location_in_bounds(x, y)
                   && !is_in_allowed_movements(g, x, y))
                {
                    return true;
                }
            }
        }
    }

    return false;

}

Orientation get_orientation_indicated_by_point(int x, int y, int piece_x, int piece_y){
    if (x == piece_x && piece_y + 1 == y){
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

static void gold_play_action(GameState* g, int x, int y){
    /*
    Handles input in the case of it being gold's turn w/
    no piece selected
    */
    if(is_unlocked_gold_piece_at_location(g->gameboard, x, y)){
        g->current_state = gold_piece_selected;
        g->selected_piece_x = x;
        g->selected_piece_y = y;
    }
}

static void silver_play_action(GameState* g, int x, int y){
    /*
    Handles input in the case of it being silver's turn w/
    no piece selected
    */
    if(is_unlocked_silver_piece_at_location(g->gameboard, x, y)){
        g->current_state = silver_piece_selected;
        g->selected_piece_x = x;
        g->selected_piece_y = y;
    }
}

static void gold_respawning_action(GameState* g, int x, int y){
    if(is_in_respawn_points(gold, x, y) && (!is_unlocked_piece_at_location(g->gameboard, x, y))){
        new_unlocked_piece_at_location(g->gameboard, x, y, gold, north);
        g->current_state = silver_play;
    }
    if(is_locked_gold_piece_at_location(g->gameboard, x, y)){
        remove_locked_piece_at_location(g->gameboard, x, y);
        g->current_state = gold_respawning;
    }
}

static void silver_respawning_action(GameState* g, int x, int y){
    if(is_in_respawn_points(silver, x, y) && (!is_unlocked_piece_at_location(g->gameboard, x, y))){
        new_unlocked_piece_at_location(g->gameboard, x, y, silver, south);
        g->current_state = silver_play;
    }
    if(is_locked_silver_piece_at_location(g->gameboard, x, y)){
        remove_locked_piece_at_location(g->gameboard, x, y);
        g->current_state = silver_respawning;
    }
}

static void gold_piece_selected_action(GameState* g, int x, int y){
    if(is_in_allowed_movements(g, x, y))
    {

        if(is_locked_gold_piece_at_location(g->gameboard, x, y)){
            g->current_state = gold_respawning;
        }else{
            g->current_state = silver_play;
        }
        if(is_unlocked_silver_piece_at_location(g->gameboard, x, y)){
            lock_piece_at_location(g->gameboard, x, y);
        }
        move_piece_to_location(g->gameboard, g->selected_piece_x, g->selected_piece_y, x, y);
    }
    else if(is_in_allowed_rotations(g, x, y))
    {
        Orientation new_orientation = get_orientation_indicated_by_point(x, y,
                                                                         g->selected_piece_x,
                                                                         g->selected_piece_y);
        Key* gold_piece = get_unlocked_piece_at_location(g->gameboard, x, y);
        gold_piece->orientation = new_orientation;
        g->current_state = silver_play;
    }
}

static void silver_piece_selected_action(GameState* g, int x, int y){
    if(is_in_allowed_movements(g, x, y))
    {

        if(is_locked_silver_piece_at_location(g->gameboard, x, y)){
            g->current_state = silver_respawning;
        }else{
            g->current_state = gold_play;
        }

        if(is_unlocked_gold_piece_at_location(g->gameboard, x, y)){
            lock_piece_at_location(g->gameboard, x, y);
        }
        move_piece_to_location(g->gameboard, g->selected_piece_x, g->selected_piece_y, x, y);
    }
    else if(is_in_allowed_rotations(g, x, y))
    {
        Orientation new_orientation = get_orientation_indicated_by_point(x, y,
                                                                         g->selected_piece_x,
                                                                         g->selected_piece_y);
        Key* silver_piece = get_unlocked_piece_at_location(g->gameboard, x, y);
        silver_piece->orientation = new_orientation;
        g->current_state = gold_play;
    }
}
char* get_board_as_JSON(void);
void handle_click(GameState* gamestate, int x, int y){
    switch(gamestate->current_state){
        case gold_play:
            gold_play_action(gamestate, x, y);
            break;
        case gold_respawning:
            gold_respawning_action(gamestate, x, y);
            break;
        case gold_piece_selected:
            gold_piece_selected_action(gamestate, x, y);
            break;
        case gold_win:
            break;
        case silver_play:
            silver_play_action(gamestate, x, y);
            break;
        case silver_respawning:
            silver_respawning_action(gamestate, x, y);
            break;
        case silver_piece_selected:
            silver_piece_selected_action(gamestate, x, y);
            break;
        case silver_win:
            break;
    }
}
