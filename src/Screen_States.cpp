#include "Screen_States.h"
#include "Play_State.h"

Screen_State::Screen_State(char *imgPath, SDL_Renderer *Renderer) : Game_State(Renderer) {
    SDL_Surface *surface = IMG_Load(imgPath);
    texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
}

void Screen_State::draw() {
    SDL_RenderCopy(Renderer, texture, nullptr, nullptr);
}

Screen_State::~Screen_State() {
    SDL_DestroyTexture(texture);
}


Game_State *Menu_State::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                case SDL_SCANCODE_ESCAPE:
                    exit_game = true;
                    return nullptr;
                case SDL_SCANCODE_I:
                    return new Instruction_State(Renderer);
                case SDL_SCANCODE_P:
                case SDL_SCANCODE_SPACE:
                    return new Play_State(Renderer);
                default:
                    return nullptr;
            }
        default:
            return nullptr;
    }
}

Game_State *Instruction_State::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                case SDL_SCANCODE_ESCAPE:
                    if (old_playState == nullptr)
                        return new Menu_State(Renderer);
                    else
                        return new Pause_State(Renderer);
                default:
                    return nullptr;
            }
        default:
            return nullptr;
    }
}

Game_State *Pause_State::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                case SDL_SCANCODE_M:
                    delete old_playState;
                    old_playState = nullptr;
                    return new Menu_State(Renderer);
                case SDL_SCANCODE_I:
                    return new Instruction_State(Renderer);
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_SPACE:
                case SDL_SCANCODE_P:
                    return old_playState;
                default:
                    return nullptr;
            }
        default:
            return nullptr;
    }
}