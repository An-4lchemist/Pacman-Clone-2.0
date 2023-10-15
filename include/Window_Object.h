#ifndef PACMAN_WINDOW_OBJECT_H
#define PACMAN_WINDOW_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

class Window_Object {
public:
    SDL_Window *Window = nullptr;
    SDL_Renderer *Renderer = nullptr;
    bool close_Window = false;

    Window_Object(char *Title, char *Logo, int Screen_Width, int Screen_Height);

    ~Window_Object();

    void handle_input(SDL_Event event);

    void clear_background() const;

    void swap_buffer() const;
};


#endif //PACMAN_WINDOW_OBJECT_H
