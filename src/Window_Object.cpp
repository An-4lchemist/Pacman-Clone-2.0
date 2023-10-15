#include "Window_Object.h"

Window_Object::Window_Object(char *Title, char *Logo, int Screen_Width, int Screen_Height) {
    Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width, Screen_Height, 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

    SDL_Surface *surface = IMG_Load(Logo);
    SDL_SetWindowIcon(Window, surface);
    SDL_FreeSurface(surface);
}

void Window_Object::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            close_Window = true;
            break;
        default:
            break;
    }
}

void Window_Object::clear_background() const {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Renderer);
}

void Window_Object::swap_buffer() const {
    SDL_RenderPresent(Renderer);
}

Window_Object::~Window_Object() {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
}
