#ifndef PACMAN_GHOST_OBJECT_H
#define PACMAN_GHOST_OBJECT_H

#include "Pacman.h"

#define IMG_G_FRIGHT_PATH (char *) "resources/Images/Play/ghost_evade.png"

class Ghost_Object : public Character_Object {
public:
    std::vector<std::tuple<int, int>> path;

    SDL_Texture *Normal_Texture;
    struct query_Texture normTexture = {2, 4};
    SDL_Texture *Fright_Texture;
    struct query_Texture frightTexture = {2, 2};
    int anim_speed = 8;

    enum States {
        JAILED, CHASE, SCATTER, FRIGHT
    } State = JAILED;

    int jail_time_left;
    int jail_time = 10;
    int jail_move_speed = 20;
    struct pos_Index_float jailIndex{};

    int norm_move_speed = 15;
    struct pos_Index_int prevIndex{};

    int chase_time_left{};
    int chase_time = 1000;

    int scatter_time_left{};
    int scatter_time = 450;

    int fright_time_left{};
    int fright_time = 450;

    Ghost_Object(char *img_path, int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer);

    void transition(States state);

    void update(const Map_Object *map, const Pacman *player);

    void draw();

    virtual std::tuple<int, int> get_next_move(const Map_Object *map, const Pacman *player) = 0;

    ~Ghost_Object() override;
};


#endif //PACMAN_GHOST_OBJECT_H
