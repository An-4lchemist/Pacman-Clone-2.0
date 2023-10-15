#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "Character_Object.h"

#define IMG_PAC_ALI_PATH (char *) "resources/Images/Play/pacman_alive.png"
#define IMG_PAC_DEA_PATH (char *) "resources/Images/Play/pacman_dead.png"

class Pacman final : public Character_Object {
public:
    SDL_Texture *Alive_Texture;
    struct query_Texture aliveTexture = {3, 4};
    int alive_anim_speed = 5;

    SDL_Texture *Dead_Texture;
    struct query_Texture deadTexture = {5, 3};
    int dead_anim_speed = 9;

    enum Dirs dir_to_move = LEFT;

    int motion_speed = 15;
    enum States {
        ALIVE, DEAD
    } State = ALIVE;

    bool death_done = false;

    Pacman(int x_index, int y_index, int w, int h, SDL_Renderer *renderer);

    void handle_input(SDL_Event event);

    void transition(States state);

    void update(const Map_Object *map);

    void draw();

    ~Pacman() final;
};


#endif //PACMAN_PACMAN_H
