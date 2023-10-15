#include "Pellets.h"

Pellets_Object::Pellets_Object(int size, int cw, int ch, const std::vector<std::tuple<int, int>> &locs,
                               SDL_Renderer *Renderer) : Renderer(Renderer) {
    for (auto loc: locs) {
        pellets.push_back(new SDL_Rect{
                std::get<0>(loc) * cw + (cw - size) / 2,
                std::get<1>(loc) * ch + (ch - size) / 2,
                size, size
        });
    }
}

bool Pellets_Object::update(const SDL_Rect *rect) {
    int pos = 0;
    bool collided = false;
    for (auto &pellet: pellets) {
        if (SDL_HasIntersection(pellet, rect)) {
            delete pellet;
            collided = true;
            break;
        }
        pos++;
    }
    if (collided) pellets.erase(pellets.begin() + pos);
    return collided;
}

void Pellets_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
    for (auto rect: pellets) {
        SDL_RenderFillRect(Renderer, rect);
    }
}

Pellets_Object::~Pellets_Object() {
    for (auto &rect: pellets) {
        delete rect;
        rect = nullptr;
    }
    pellets.clear();
}

Pow_Pellets_Object::Pow_Pellets_Object(int size, int cw, int ch, const std::vector<std::tuple<int, int>> &locs,
                                       SDL_Renderer *renderer) : Pellets_Object(size, cw, ch, locs, renderer) {
    SDL_Surface *surface = IMG_Load(IMG_PELLET_PATH);
    texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
}

void Pow_Pellets_Object::draw() {
    if (dev_mode) {
        Pellets_Object::draw();
    } else {
        for (auto rect: pellets) {
            SDL_RenderCopy(Renderer, texture, nullptr, rect);
        }
    }
}

Pow_Pellets_Object::~Pow_Pellets_Object() {
    SDL_DestroyTexture(texture);
}
