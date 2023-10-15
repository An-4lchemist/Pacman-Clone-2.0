#include "Ghost_Object.h"

Ghost_Object::Ghost_Object(char *img_path, int x_index, int y_index, int jail_time, int w, int h,
                           SDL_Renderer *Renderer)
        : Character_Object(SDL_Rect{0, 0, w, h}, Renderer),
          jail_time_left(jail_time) {

    SDL_Surface *surface = IMG_Load(img_path);
    Normal_Texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load(IMG_G_FRIGHT_PATH);
    Fright_Texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);

    jailIndex.x = (float) (x_index * 2 + 11.6);
    jailIndex.y = (float) (y_index + 13.5);

    transition(JAILED);
}

void Ghost_Object::transition(Ghost_Object::States state) {
    State = state;
    switch (State) {
        case JAILED:
            texture = Normal_Texture;
            if (jail_time_left == 0) jail_time_left = jail_time;
            motionFrame = {jail_move_speed, 0};
            animFrame = {anim_speed, 0};
            curIndex = {13, 11};
            curTexture = {};
            prevIndex = curIndex;
            hitbox->x = (int) (jailIndex.x * (float) hitbox->w);
            hitbox->y = (int) (jailIndex.y * (float) hitbox->h);
            path.clear();
            break;
        case SCATTER:
            scatter_time_left = scatter_time;
        case CHASE:
            texture = Normal_Texture;
            prevIndex = {};
            if (!is_moving) {
                hitbox->x = curIndex.x * hitbox->w;
                hitbox->y = curIndex.y * hitbox->h;
            }
            motionFrame.limit = norm_move_speed;
            curTexture = {};
            chase_time_left = chase_time;
            path.clear();
            break;
        case FRIGHT:
            texture = Fright_Texture;
            std::tie(curIndex, prevIndex) = std::make_tuple(prevIndex, curIndex);
            motionFrame.current = motionFrame.limit - motionFrame.current;
            curTexture = {};
            fright_time_left = fright_time;
            path.clear();
            break;
    }
}

void Ghost_Object::update(const Map_Object *map, const Pacman *player) {
    switch (State) {
        case JAILED:
            if (!is_moving) {
                jail_time_left--;
                if (jail_time_left == 0) {
                    transition(CHASE);
                }
            }
            break;
        case CHASE:
            chase_time_left--;
            if (chase_time_left == 0) {
                transition(SCATTER);
            }
            break;
        case SCATTER:
            scatter_time_left--;
            if (scatter_time_left == 0) {
                transition(CHASE);
            }
            break;
        case FRIGHT:
            fright_time_left--;
            if (fright_time_left == 0) {
                transition(CHASE);
            }
            break;
    }
    switch (State) {
        case JAILED:
            if (!is_moving) {
                if (jailIndex.y == 13.5) {
                    jailIndex.y++;
                    cur_dir = DOWN;
                } else {
                    jailIndex.y--;
                    cur_dir = UP;
                }
            }
            is_moving = move(jailIndex);
            break;
        case CHASE:
        case SCATTER:
        case FRIGHT:
            if (!is_moving) {
                int new_x, new_y;
                std::tie(new_x, new_y) = get_next_move(map, player);

                prevIndex = curIndex;
                if (new_x == 0 && curIndex.x == 27) {
                    curIndex.x = -1;
                    hitbox->x = curIndex.x * hitbox->w;
                    prevIndex = {27, curIndex.y};
                } else if (new_x == 27 && curIndex.x == 0) {
                    curIndex.x = 28;
                    hitbox->x = curIndex.x * hitbox->w;
                    prevIndex = {0, curIndex.y};
                }
                if (new_x < curIndex.x) {
                    cur_dir = LEFT;
                    curIndex.x--;
                } else if (new_x > curIndex.x) {
                    cur_dir = RIGHT;
                    curIndex.x++;
                } else if (new_y < curIndex.y) {
                    cur_dir = UP;
                    curIndex.y--;
                } else if (new_y > curIndex.y) {
                    cur_dir = DOWN;
                    curIndex.y++;
                }
            }
            is_moving = move(curIndex);
            break;
    }
    switch (State) {
        case JAILED:
        case CHASE:
        case SCATTER:
            anim_adv_row(normTexture.row);
            curTexture.col = (int) cur_dir;
            break;
        case FRIGHT:
            if (fright_time_left <= 150) {
                anim_adv_mat(frightTexture.row, frightTexture.col);
            } else {
                anim_adv_col(frightTexture.col);
            }
            break;
    }
}

void Ghost_Object::draw() {
    if (dev_mode) {
        Character_Object::draw_rect();

        SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, 100);
        auto rect = new SDL_Rect{0, 0, hitbox->w, hitbox->h};
        for (auto &node: path) {
            rect->x = std::get<0>(node) * hitbox->w;
            rect->y = std::get<1>(node) * hitbox->h;
            SDL_RenderFillRect(Renderer, rect);
        }
        delete rect;
    } else {
        Character_Object::draw_texture();
    }
}

Ghost_Object::~Ghost_Object() {
    SDL_DestroyTexture(Normal_Texture);
    SDL_DestroyTexture(Fright_Texture);
}
