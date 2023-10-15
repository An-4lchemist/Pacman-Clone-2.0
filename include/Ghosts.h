#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

#include "Ghost_Object.h"
#include "AI.h"

#define IMG_G1_NORM_PATH (char *) "resources/Images/Play/ghost_1_chase.png"
#define IMG_G2_NORM_PATH (char *) "resources/Images/Play/ghost_2_chase.png"
#define IMG_G3_NORM_PATH (char *) "resources/Images/Play/ghost_3_chase.png"

class Ghost_1 : public Ghost_Object {
public:

    Ghost_1(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer);

    ~Ghost_1() override = default;

    std::tuple<int, int> get_next_move(const Map_Object *map, const Pacman *player) override;
};

class Ghost_2 : public Ghost_Object {
public:

    Ghost_2(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer);

    ~Ghost_2() override = default;

    std::tuple<int, int> get_next_move(const Map_Object *map, const Pacman *player) override;
};

class Ghost_3 : public Ghost_Object {
public:

    Ghost_3(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer);

    ~Ghost_3() override = default;

    std::tuple<int, int> get_next_move(const Map_Object *map, const Pacman *player) override;
};


#endif //PACMAN_GHOSTS_H
