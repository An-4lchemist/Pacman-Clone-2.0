#ifndef PACMAN_INFO_OBJECT_H
#define PACMAN_INFO_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#define FONT_PATH (char *) "resources/Fonts/pacman_font.ttf"
#define IMG_LOGO_PATH (char *) "resources/Images/Play/pacman_logo.png"

class Info_Object {
public:
    int lives;
    int score;
    int level;
    TTF_Font *font;
    SDL_Color color{255, 255, 255, 255};
    SDL_Rect *rect;
    int w_player;
    SDL_Texture *life_texture;
    SDL_Renderer *Renderer;

    Info_Object(int x_pos, int h, int w_player, SDL_Renderer *Renderer);

    void draw() const;

    void draw_str(const std::string &msg, int x, int y) const;

    ~Info_Object();
};


#endif //PACMAN_INFO_OBJECT_H
