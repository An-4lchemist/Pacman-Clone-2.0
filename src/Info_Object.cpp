#include "Info_Object.h"

Info_Object::Info_Object(int x_pos, int h, int w_player, SDL_Renderer *Renderer)
        : Renderer(Renderer), w_player(w_player) {

    level = 0;
    score = 0;
    lives = 4;

    rect = new SDL_Rect{x_pos, 0, w_player * 2 * 4, h};

    font = TTF_OpenFont(FONT_PATH, 24);

    SDL_Surface *surface = IMG_Load(IMG_LOGO_PATH);
    life_texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
}

void Info_Object::draw_str(const std::string &msg, int x, int y) const {
    int w, h;
    auto surface = TTF_RenderText_Solid(font, msg.c_str(), color);
    auto texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    auto dstRect = new SDL_Rect{x, y, w, h};
    SDL_RenderCopy(Renderer, texture, nullptr, dstRect);
    delete dstRect;
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Info_Object::draw() const {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Renderer, rect);

    draw_str("Level", rect->x + 10, 0);
    draw_str(std::to_string(level), rect->x + 10, 50);
    draw_str("Score", rect->x + 10, 100);
    draw_str(std::to_string(score), rect->x + 10, 150);

    auto dstRect = new SDL_Rect{(rect->x + 10), (rect->h - 10) - w_player * 2, w_player * 2, w_player * 2};
    for (int i = 0; i < lives; i++) {
        SDL_RenderCopy(Renderer, life_texture, nullptr, dstRect);
        dstRect->x += w_player * 2;
    }
    delete dstRect;
}

Info_Object::~Info_Object() {
    delete rect;
    TTF_CloseFont(font);
    SDL_DestroyTexture(life_texture);
}
