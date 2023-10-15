#include "Character_Object.h"

Character_Object::Character_Object(SDL_Rect rect, SDL_Renderer *Renderer) : Renderer(Renderer) {
    hitbox = new SDL_Rect(rect);
    texture = nullptr;
}

bool Character_Object::move(Character_Object::pos_Index_int pos) {
    if (hitbox->x == pos.x * hitbox->w && hitbox->y == pos.y * hitbox->h) {
        overheadDist = {};
        motionFrame.current = 0;
        return false;
    } else if (motionFrame.current == motionFrame.limit) {
        hitbox->x = (pos.x * hitbox->w);
        hitbox->y = (pos.y * hitbox->h);
        overheadDist = {};
        motionFrame.current = 0;
        return false;
    } else {
        float dist_x =
                ((float) pos.x * (float) hitbox->w - (float) hitbox->x) /
                (float) (motionFrame.limit - motionFrame.current)
                + overheadDist.x;
        float dist_y =
                ((float) pos.y * (float) hitbox->h - (float) hitbox->y) /
                (float) (motionFrame.limit - motionFrame.current)
                + overheadDist.y;

        hitbox->x += (int) dist_x;
        hitbox->y += (int) dist_y;

        overheadDist.x = dist_x - (float) (int) dist_x;
        overheadDist.y = dist_y - (float) (int) dist_y;

        motionFrame.current++;
        return true;
    }
}

bool Character_Object::move(Character_Object::pos_Index_float pos) {
    if (hitbox->x == (int) pos.x * hitbox->w && hitbox->y == (int) pos.y * hitbox->h) {
        overheadDist = {};
        motionFrame.current = 0;
        return false;
    } else if (motionFrame.current == motionFrame.limit) {
        hitbox->x = (int) (pos.x * (float) hitbox->w);
        hitbox->y = (int) (pos.y * (float) hitbox->h);
        overheadDist = {};
        motionFrame.current = 0;
        return false;
    } else {
        float dist_x =
                (pos.x * (float) hitbox->w - (float) hitbox->x) /
                (float) (motionFrame.limit - motionFrame.current)
                + overheadDist.x;
        float dist_y =
                (pos.y * (float) hitbox->h - (float) hitbox->y) /
                (float) (motionFrame.limit - motionFrame.current)
                + overheadDist.y;

        hitbox->x += (int) dist_x;
        hitbox->y += (int) dist_y;

        overheadDist.x = dist_x - (float) (int) dist_x;
        overheadDist.y = dist_y - (float) (int) dist_y;

        motionFrame.current++;
        return true;
    }
}

void Character_Object::anim_adv_row(int row_len) {
    animFrame.current++;
    if (animFrame.current == animFrame.limit) {
        animFrame.current = 0;
        curTexture.row = (curTexture.row + 1) % row_len;
    }
}

void Character_Object::anim_adv_col(int col_len) {
    animFrame.current++;
    if (animFrame.current == animFrame.limit) {
        animFrame.current = 0;
        curTexture.col = (curTexture.col + 1) % col_len;
    }
}

void Character_Object::anim_adv_mat(int row_len, int col_len) {
    animFrame.current++;
    if (animFrame.current == animFrame.limit) {
        animFrame.current = 0;
        curTexture.col++;
        if (curTexture.col == col_len) {
            curTexture.col = 0;
            curTexture.row = (curTexture.row + 1) % row_len;
        }
    }
}

void Character_Object::draw_rect() const {
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Renderer, hitbox);
}

void Character_Object::draw_texture() const {
    SDL_Rect *srcRect = new SDL_Rect{curTexture.col * 48, curTexture.row * 48, 48, 48};
    SDL_Rect *dstRect = new SDL_Rect{hitbox->x - (hitbox->w / 2),
                                     hitbox->y - (hitbox->h / 2),
                                     hitbox->w * 2, hitbox->h * 2};
    SDL_RenderCopy(Renderer, texture, srcRect, dstRect);
    delete srcRect;
    delete dstRect;
}

Character_Object::~Character_Object() {
    delete hitbox;
    SDL_DestroyTexture(texture);
}
