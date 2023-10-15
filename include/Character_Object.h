#ifndef PACMAN_CHARACTER_OBJECT_H
#define PACMAN_CHARACTER_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
#include "Map_Object.h"

class Character_Object {
public:
    bool dev_mode = false;
    SDL_Color color{};

    SDL_Rect *hitbox;
    SDL_Texture *texture;
    SDL_Renderer *Renderer;

    enum Dirs {
        LEFT, RIGHT, UP, DOWN
    };
    enum Dirs cur_dir{};

    bool is_moving = false;

    struct pos_Index_int {
        int x;
        int y;
    } curIndex{};
    struct pos_Index_float {
        float x;
        float y;
    } overheadDist{};
    struct query_Texture {
        int row;
        int col;
    } curTexture{};
    struct frames {
        int limit;
        int current;
    } motionFrame{}, animFrame{};

    Character_Object(SDL_Rect rect, SDL_Renderer *Renderer);

    void draw_rect() const;

    void draw_texture() const;

    bool move(struct pos_Index_int pos);

    bool move(struct pos_Index_float pos);

    void anim_adv_row(int row_len);

    void anim_adv_col(int col_len);

    void anim_adv_mat(int row_len, int col_len);

    virtual ~Character_Object();
};

#endif //PACMAN_CHARACTER_OBJECT_H
