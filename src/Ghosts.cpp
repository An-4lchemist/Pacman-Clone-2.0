#include "Ghosts.h"

Ghost_1::Ghost_1(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer)
        : Ghost_Object(IMG_G1_NORM_PATH, x_index, y_index, jail_time, w, h, Renderer) {
    color = {215, 40, 79, 255};
}

Ghost_2::Ghost_2(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer)
        : Ghost_Object(IMG_G2_NORM_PATH, x_index, y_index, jail_time, w, h, Renderer) {
    color = {166, 215, 40, 255};
}

Ghost_3::Ghost_3(int x_index, int y_index, int jail_time, int w, int h, SDL_Renderer *Renderer)
        : Ghost_Object(IMG_G3_NORM_PATH, x_index, y_index, jail_time, w, h, Renderer) {
    color = {40, 215, 176, 255};
}

std::tuple<int, int> Ghost_1::get_next_move(const Map_Object *map, const Pacman *player) {
    switch (State) {
        case JAILED:
            return {};
        case CHASE:
            return AI::get_move_AStar(map, player->curIndex.x, player->curIndex.y,
                                    curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
//            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        case SCATTER:
            return AI::get_move_AStar(map, 1, 1, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
        case FRIGHT:
            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        default:
            return {};
    }
}

std::tuple<int, int> Ghost_2::get_next_move(const Map_Object *map, const Pacman *player) {
    std::tuple<int, int> target;
    switch (State) {
        case JAILED:
            return {};
        case CHASE:

            switch (player->cur_dir) {
                case LEFT:
                    target = std::make_tuple(player->curIndex.x - 4, player->curIndex.y);
                    break;
                case RIGHT:
                    target = std::make_tuple(player->curIndex.x + 4, player->curIndex.y);
                    break;
                case UP:
                    target = std::make_tuple(player->curIndex.x, player->curIndex.y - 4);
                    break;
                case DOWN:
                    target = std::make_tuple(player->curIndex.x, player->curIndex.y + 4);
                    break;
            }

            target = map->get_nearest_move(target);

            return AI::get_move_AStar(map, std::get<0>(target), std::get<1>(target),
                                      curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
//            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        case SCATTER:
            return AI::get_move_AStar(map, 26, 1, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
        case FRIGHT:
            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        default:
            return {};
    }
}

std::tuple<int, int> Ghost_3::get_next_move(const Map_Object *map, const Pacman *player) {
    switch (State) {
        case JAILED:
            return {};
        case CHASE:
            if (std::sqrt((std::pow(player->curIndex.x - curIndex.x, 2) + std::pow(player->curIndex.y - curIndex.y, 2))) > 8)
                return AI::get_move_AStar(map, player->curIndex.x, player->curIndex.y,
                                          curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
//            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        case SCATTER:
            return AI::get_move_AStar(map, 1, 29, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y, path);
        case FRIGHT:
            return AI::get_move_rand(map, curIndex.x, curIndex.y, prevIndex.x, prevIndex.y);
        default:
            return {};
    }
}
