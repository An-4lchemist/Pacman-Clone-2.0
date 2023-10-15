#include "Pacman.h"

Pacman::Pacman(int x_index, int y_index, int w, int h, SDL_Renderer *renderer)
        : Character_Object(SDL_Rect{x_index * w, y_index * h, w, h}, renderer) {

    SDL_Surface *surface = IMG_Load(IMG_PAC_ALI_PATH);
    Alive_Texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load(IMG_PAC_DEA_PATH);
    Dead_Texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);

    color = {255, 255, 255, 255};
    curIndex.x = x_index;
    curIndex.y = y_index;

    transition(ALIVE);
}

void Pacman::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dir_to_move = UP;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dir_to_move = LEFT;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dir_to_move = DOWN;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dir_to_move = RIGHT;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Pacman::transition(Pacman::States state) {
    State = state;
    switch (State) {
        case ALIVE:
            texture = Alive_Texture;
            motionFrame = {motion_speed, 0};
            animFrame = {alive_anim_speed, 0};
            curTexture = {};
            break;
        case DEAD:
            texture = Dead_Texture;
            animFrame = {dead_anim_speed, 0};
            curTexture = {};
            break;
    }
}

void Pacman::update(const Map_Object *map) {
    switch (State) {
        case ALIVE:
            if (!is_moving) {
                switch (dir_to_move) {
                    case LEFT:
                        if (!map->is_wall((int) curIndex.x - 1, (int) curIndex.y)) {
                            cur_dir = LEFT;
                        }
                        break;
                    case RIGHT:
                        if (!map->is_wall((int) curIndex.x + 1, (int) curIndex.y)) {
                            cur_dir = RIGHT;
                        }
                        break;
                    case UP:
                        if (!map->is_wall((int) curIndex.x, (int) curIndex.y - 1)) {
                            cur_dir = UP;
                        }
                        break;
                    case DOWN:
                        if (!map->is_wall((int) curIndex.x, (int) curIndex.y + 1)) {
                            cur_dir = DOWN;
                        }
                        break;
                }
                switch (cur_dir) {
                    case LEFT:
                        if (curIndex.x - 1 == -1) {
                            curIndex.x = 28;
                            hitbox->x = (int) curIndex.x * hitbox->w;
                        }
                        if (!map->is_wall((int) curIndex.x - 1, (int) curIndex.y)) {
                            curIndex.x--;
                        }
                        break;
                    case RIGHT:
                        if (curIndex.x + 1 == 28) {
                            curIndex.x = -1;
                            hitbox->x = (int) curIndex.x * hitbox->w;
                        }
                        if (!map->is_wall((int) curIndex.x + 1, (int) curIndex.y)) {
                            curIndex.x++;
                        }
                        break;
                    case UP:
                        if (!map->is_wall((int) curIndex.x, (int) curIndex.y - 1)) {
                            curIndex.y--;
                        }
                        break;
                    case DOWN:
                        if (!map->is_wall((int) curIndex.x, (int) curIndex.y + 1)) {
                            curIndex.y++;
                        }
                        break;
                }
            }
            is_moving = move(curIndex);
            break;
        case DEAD:
            break;
    }
    switch (State) {
        case ALIVE:
            if (is_moving) {
                anim_adv_row(aliveTexture.row);
                curTexture.col = (int) cur_dir;
            } else {
                curTexture.row = 2;
            }
            break;
        case DEAD:
            anim_adv_mat(deadTexture.row, deadTexture.col);
            if (curTexture.row == 4 && curTexture.col == 0) {
                death_done = true;
            }
            break;
    }
}

void Pacman::draw() {
    if (dev_mode) {
        Character_Object::draw_rect();
    } else {
        Character_Object::draw_texture();
    }
}

Pacman::~Pacman() {
    SDL_DestroyTexture(Alive_Texture);
    SDL_DestroyTexture(Dead_Texture);
}
