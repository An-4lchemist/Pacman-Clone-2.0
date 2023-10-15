#ifndef PACMAN_SCREEN_STATES_H
#define PACMAN_SCREEN_STATES_H

#include "Game_State.h"

#define IMG_MENU_PATH (char *) "resources/Images/Screens/menu_screen.png"
#define IMG_INST_PATH (char *) "resources/Images/Screens/inst_screen.png"
#define IMG_PAUS_PATH (char *) "resources/Images/Screens/paus_screen.png"

class Screen_State : public Game_State {
public:
    SDL_Texture *texture = nullptr;

    Screen_State(char *imgPath, SDL_Renderer *Renderer);

    Game_State *update() override { return nullptr; };

    Game_State *handle_input(SDL_Event event) override = 0;

    void draw() override;   

    ~Screen_State() override;
};

class Menu_State : public Screen_State {
public:
    Menu_State(SDL_Renderer *Renderer) : Screen_State(IMG_MENU_PATH, Renderer) {}

    Game_State *handle_input(SDL_Event event) final;
};

class Instruction_State : public Screen_State {
public:
    Instruction_State(SDL_Renderer *Renderer) : Screen_State(IMG_INST_PATH, Renderer) {}

    Game_State *handle_input(SDL_Event event) final;
};

class Pause_State : public Screen_State {
public:
    Pause_State(SDL_Renderer *Renderer) : Screen_State(IMG_PAUS_PATH, Renderer) {}

    Game_State *handle_input(SDL_Event event) final;
};

#endif //PACMAN_SCREEN_STATES_H
