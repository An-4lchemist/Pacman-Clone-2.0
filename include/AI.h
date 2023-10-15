#ifndef PACMAN_AI_H
#define PACMAN_AI_H

#include "Map_Object.h"

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}

class AI {
public:
    static std::tuple<int, int> get_move_rand(const Map_Object *map, int curX, int curY, int preX, int preY);

    static std::tuple<int, int> get_move_BFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                             int preX, int preY, std::vector<std::tuple<int, int>> &path);

    static std::tuple<int, int> get_move_DFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                             int preX, int preY, std::vector<std::tuple<int, int>> &path);

    static std::tuple<int, int> get_move_GBFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                             int preX, int preY, std::vector<std::tuple<int, int>> &path);

    static std::tuple<int, int> get_move_AStar(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                              int preX, int preY, std::vector<std::tuple<int, int>> &path);

};


#endif //PACMAN_AI_H
