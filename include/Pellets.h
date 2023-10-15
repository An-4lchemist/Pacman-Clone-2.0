#ifndef PACMAN_PELLETS_H
#define PACMAN_PELLETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#define IMG_PELLET_PATH (char *) "resources/Images/Play/pellet.png"

class Pellets_Object {
public:
    std::vector<SDL_Rect *> pellets;
    SDL_Color color{248, 176, 144, 255};
    SDL_Renderer *Renderer;

    Pellets_Object(int size, int cw, int ch, const std::vector<std::tuple<int, int>> &locs, SDL_Renderer *Renderer);

    bool update(const SDL_Rect *rect);

    virtual void draw();

    virtual ~Pellets_Object();
};

class Pow_Pellets_Object final: public Pellets_Object{
public:
    bool dev_mode = false;
    SDL_Texture *texture;

    Pow_Pellets_Object(int size, int cw, int ch, const std::vector<std::tuple<int, int>> &locs,
                       SDL_Renderer *renderer);

    void draw() final;

    ~Pow_Pellets_Object() final;
};

#endif //PACMAN_PELLETS_H
