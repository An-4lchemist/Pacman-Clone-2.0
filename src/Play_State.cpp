#include "Play_State.h"
#include "Screen_States.h"

Play_State::Play_State(SDL_Renderer *Renderer) : Game_State(Renderer) {
    Map = new Map_Object(25, 25, Renderer);
    DashBoard = new Info_Object(Map->cell_width * Map->cols, Map->cell_height * Map->rows, Map->cell_width, Renderer);
    restart(true);
}

void Play_State::restart(bool newLevel) {
    bool fasterrrrrr = false;
    if (newLevel) {
        DashBoard->level++;
        if (DashBoard->level >= 3){
            fasterrrrrr = true;
        }
        delete Pellets;
        Pellets = new Pellets_Object(8, Map->cell_width, Map->cell_height, Map->get_pellets_loc(), Renderer);
        delete Pow_Pellets;
        Pow_Pellets = new Pow_Pellets_Object(20, Map->cell_width, Map->cell_height,
                                             Map->get_pow_pellets_loc(), Renderer);
    } else {
        DashBoard->lives--;
    }
    delete Player;
    Player = new Pacman(13, 23, Map->cell_width, Map->cell_height, Renderer);
    for (auto &ghost: Ghosts) {
        delete ghost;
        ghost = nullptr;
    }
    Ghosts.clear();
    Ghosts.push_back(new Ghost_1(0, 1, 10, Map->cell_width, Map->cell_height, Renderer));
    Ghosts.push_back(new Ghost_2(1, 0, 18, Map->cell_width, Map->cell_height, Renderer));
    Ghosts.push_back(new Ghost_3(2, 1, 25, Map->cell_width, Map->cell_height, Renderer));

    if (fasterrrrrr){
        for (auto ghost: Ghosts){
            ghost->scatter_time = 1;
            ghost->jail_time = 5;
            ghost->norm_move_speed = 12;
        }
    }
}

Game_State *Play_State::handle_input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_K:
                    K_Pressed = true;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_K:
                    if (K_Pressed) {
                        dev_mode = !dev_mode;
                    }
                    K_Pressed = false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    Map->dev_mode = dev_mode;
    Pow_Pellets->dev_mode = dev_mode;
    Player->dev_mode = dev_mode;
    for (auto &ghost: Ghosts) {
        ghost->dev_mode = dev_mode;
    }

    Player->handle_input(event);

    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_P:
                case SDL_SCANCODE_ESCAPE:
                    old_playState = this;
                    return new Pause_State(Renderer);
                default:
                    return nullptr;
            }
        default:
            return nullptr;
    }
}

Game_State *Play_State::update() {

    switch (Player->State) {
        case Pacman::ALIVE:
            Player->update(Map);
            for (auto &ghost: Ghosts) {
                ghost->update(Map, Player);
            }
            for (auto &ghost: Ghosts) {
                if (SDL_HasIntersection(ghost->hitbox, Player->hitbox)) {
                    switch (ghost->State) {
                        case Ghost_Object::JAILED:
                            break;
                        case Ghost_Object::CHASE:
                        case Ghost_Object::SCATTER:
                            Player->transition(Pacman::DEAD);
                            break;
                        case Ghost_Object::FRIGHT:
                            DashBoard->score += 500;
                            ghost->transition(Ghost_Object::JAILED);
                            break;
                    }
                }
            }
            if (Pellets->update(Player->hitbox)) {
                DashBoard->score += 100;
            }
            if (Pow_Pellets->update(Player->hitbox)) {
                for (auto &ghost: Ghosts) {
                    if (ghost->State != Ghost_Object::JAILED) {
                        ghost->transition(Ghost_Object::FRIGHT);
                    }
                }
            }
            break;
        case Pacman::DEAD:
            Player->update(Map);
            if (Player->death_done) {
                if (DashBoard->lives == 1) {
                    return new Menu_State(Renderer);
                } else {
                    restart(false);
                }
            }
            break;
    }

    if (Pellets->pellets.empty()) {
        restart(true);
    }

    return nullptr;
}

void Play_State::draw() {
    Map->draw();
    Pellets->draw();
    Pow_Pellets->draw();
    if (Player->State != Pacman::DEAD) {
        for (auto &ghost: Ghosts) {
            ghost->draw();
        }
    }
    Player->draw();
    DashBoard->draw();
}

Play_State::~Play_State() {
    delete Map;
    delete DashBoard;
    delete Pellets;
    delete Pow_Pellets;
    delete Player;
    for (auto &ghost: Ghosts) {
        delete ghost;
    }
}
