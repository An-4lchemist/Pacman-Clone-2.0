#ifndef PACMAN_PLAY_STATE_H
#define PACMAN_PLAY_STATE_H

#include "Game_State.h"
#include "Info_Object.h"
#include "Pellets.h"
#include "Pacman.h"
#include "Ghosts.h"

class Play_State final : public Game_State {
public:
    bool K_Pressed = false;
    bool dev_mode = false;

    Map_Object *Map;
    Info_Object *DashBoard;
    Pellets_Object *Pellets{};
    Pow_Pellets_Object *Pow_Pellets{};
    Pacman *Player{};
    std::vector<Ghost_Object *> Ghosts{};


    Play_State(SDL_Renderer *Renderer);

    void restart(bool newLevel);

    Game_State *handle_input(SDL_Event event) final;

    Game_State *update() final;

    void draw() final;

    ~Play_State() final;
};


#endif //PACMAN_PLAY_STATE_H
