#include "Game_State.h"
#include "Play_State.h"

Game_State *Game_State::old_playState = nullptr;


void Game_State::exit_on_input(Game_State *state) {
    if (dynamic_cast<Play_State *>(state) == nullptr)
        delete state;
}
