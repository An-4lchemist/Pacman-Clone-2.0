#ifndef PACMAN_GAME_STATE_H
#define PACMAN_GAME_STATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>


class Game_State {
public:
    SDL_Renderer *Renderer = nullptr;
    bool exit_game = false;
    static Game_State *old_playState;

    static void exit_on_input(Game_State *state);

    Game_State(SDL_Renderer *Renderer) : Renderer(Renderer) {};

    virtual Game_State *handle_input(SDL_Event event) = 0;

    virtual Game_State *update() = 0;

    virtual void draw() = 0;

    virtual ~Game_State() = default;
};

#endif //PACMAN_GAME_STATE_H
