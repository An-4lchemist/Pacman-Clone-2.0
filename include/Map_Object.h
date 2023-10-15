#ifndef PACMAN_MAP_OBJECT_H
#define PACMAN_MAP_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#define MAP_PATH "resources/Maps/map_1.txt"
#define IMG_MAP_PATH (char *) "resources/Images/Play/map.png"

class Map_Object {
public:
    bool dev_mode = false;
    SDL_Color color{89, 40, 215, 255};
    std::vector<SDL_Rect *> walls;

    SDL_Texture *texture;
    SDL_Renderer *Renderer;

    int cell_width;
    int cell_height;
    int rows{};
    int cols{};
    std::vector<std::vector<int>> env_layout;

    Map_Object(int w, int h, SDL_Renderer *Renderer);

    void draw();

    bool is_wall(int col, int row) const;

    std::tuple<int, int> get_nearest_move(std::tuple<int, int> node) const;

    std::vector<std::tuple<int, int>> get_moves(int x_index, int y_index) const;

    std::vector<std::tuple<int, int>> get_moves(std::tuple<int, int> node) const;

    std::vector<std::tuple<int, int>> get_pellets_loc() const;

    std::vector<std::tuple<int, int>> get_pow_pellets_loc() const;

    void read_map(const std::string &Fname);

    void create_map();

    ~Map_Object();
};


#endif //PACMAN_MAP_OBJECT_H
