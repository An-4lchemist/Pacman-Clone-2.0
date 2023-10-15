#include "AI.h"

std::tuple<int, int> AI::get_move_rand(const Map_Object *map, int curX, int curY, int preX, int preY) {
    auto moves = map->get_moves(curX, curY);

    auto move_ptr = std::find(moves.begin(), moves.end(),
                              std::tuple<int, int>(preX, preY));
    if (move_ptr != moves.end()) {
        moves.erase(move_ptr);
    }
    if (moves.size() == 1) return moves[0];
    return *select_randomly(moves.begin(), moves.end());
}

std::tuple<int, int> AI::get_move_BFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                      int preX, int preY, std::vector<std::tuple<int, int>> &path) {
    if (map->is_wall(tarX, tarY))
        return get_move_rand(map, curX, curY, preX, preY);

    auto goal = std::make_tuple(tarX, tarY);
    auto start = std::make_tuple(curX, curY);
    auto prev = std::make_tuple(preX, preY);

    if (goal == start) return get_move_rand(map, curX, curY, preX, preY);

    std::map<std::tuple<int, int>, std::tuple<int, int>> parent;
    std::list<std::tuple<int, int>> explored;
    std::list<std::tuple<int, int>> frontier;

    explored.push_back(start);
    parent[start] = std::make_tuple(-1, -1);
    auto children = map->get_moves(curX, curY);
    for (auto child: children) {
        if (child != prev) {
            frontier.push_back(child);
            parent[child] = start;
        }
    }

    path.clear();

    while (!frontier.empty()) {
        auto node = frontier.front();
        frontier.pop_front();

        if (node == goal) {
            while (parent[node] != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(node);
//            std::cout << "BFS Explored: " << explored.size() << std::endl;
            return node;
        }

        explored.push_back(node);
        children = map->get_moves(node);
        for (auto child: children) {
            if (std::find(explored.begin(), explored.end(), child) == explored.end()) {
                frontier.push_back(child);
                parent[child] = node;
            }
        }
    }

    std::cout << "something went wrong!" << std::endl;
    return get_move_rand(map, curX, curY, preX, preY);
}

std::tuple<int, int> AI::get_move_DFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                      int preX, int preY, std::vector<std::tuple<int, int>> &path) {
    if (map->is_wall(tarX, tarY))
        return get_move_rand(map, curX, curY, preX, preY);

    auto goal = std::make_tuple(tarX, tarY);
    auto start = std::make_tuple(curX, curY);
    auto prev = std::make_tuple(preX, preY);

    if (goal == start) return get_move_rand(map, curX, curY, preX, preY);

    std::map<std::tuple<int, int>, std::tuple<int, int>> parent;
    std::list<std::tuple<int, int>> explored;
    std::list<std::tuple<int, int>> frontier;

    explored.push_back(start);
    parent[start] = std::make_tuple(-1, -1);
    auto children = map->get_moves(curX, curY);
    for (auto child: children) {
        if (child != prev) {
            frontier.push_back(child);
            parent[child] = start;
        }
    }

    path.clear();

    while (!frontier.empty()) {
        auto node = frontier.back();
        frontier.pop_back();

        if (node == goal) {
            while (parent[node] != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(node);
//            std::cout << "DFS Explored: " << explored.size() << std::endl;
            return node;
        }

        explored.push_back(node);
        children = map->get_moves(node);
        for (auto child: children) {
            if (std::find(explored.begin(), explored.end(), child) == explored.end()) {
                frontier.push_back(child);
                parent[child] = node;
            }
        }
    }

    std::cout << "something went wrong!" << std::endl;
    return get_move_rand(map, curX, curY, preX, preY);
}

std::tuple<int, int> AI::get_move_GBFS(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                       int preX, int preY, std::vector<std::tuple<int, int>> &path) {
    if (map->is_wall(tarX, tarY))
        return get_move_rand(map, curX, curY, preX, preY);

    auto goal = std::make_tuple(tarX, tarY);
    auto start = std::make_tuple(curX, curY);
    auto prev = std::make_tuple(preX, preY);

    if (goal == start) return get_move_rand(map, curX, curY, preX, preY);

    std::map<std::tuple<int, int>, std::tuple<int, int>> parent;
    std::list<std::tuple<int, int>> explored;
    std::list<std::tuple<int, int>> frontier;

    auto heuristic_fn = [&goal, &map](std::tuple<int, int> n) -> int {

        int y = abs(std::get<1>(n) - std::get<1>(goal));
        int x1 = abs(std::get<0>(n) - std::get<0>(goal));
        int x2 = abs(std::get<0>(n) - std::get<0>(goal) - map->cols + 1);
        int x3 = abs(std::get<0>(n) - std::get<0>(goal) + map->cols - 1);

        return std::min({x1, x2, x3}) + y;
    };

    auto compareNodes = [&heuristic_fn](std::tuple<int, int> n1, std::tuple<int, int> n2) -> bool {
        return (heuristic_fn(n1) < heuristic_fn(n2));
    };

    explored.push_back(start);
    parent[start] = std::make_tuple(-1, -1);
    auto children = map->get_moves(curX, curY);
    for (auto child: children) {
        if (child != prev) {
            frontier.push_back(child);
            parent[child] = start;
        }
    }

    path.clear();

    while (!frontier.empty()) {
        frontier.sort(compareNodes);
        auto node = frontier.front();
        frontier.pop_front();

        if (node == goal) {
            while (parent[node] != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(node);
//            std::cout << "GBS Explored: " << explored.size() << std::endl;
            return node;
        }

        explored.push_back(node);
        children = map->get_moves(node);
        for (auto child: children) {
            if (std::find(explored.begin(), explored.end(), child) == explored.end()) {
                frontier.push_back(child);
                parent[child] = node;
            }
        }
    }

    std::cout << "something went wrong!" << std::endl;
    return get_move_rand(map, curX, curY, preX, preY);
}

std::tuple<int, int> AI::get_move_AStar(const Map_Object *map, int tarX, int tarY, int curX, int curY,
                                        int preX, int preY, std::vector<std::tuple<int, int>> &path) {
    if (map->is_wall(tarX, tarY))
        return get_move_rand(map, curX, curY, preX, preY);

    auto goal = std::make_tuple(tarX, tarY);
    auto start = std::make_tuple(curX, curY);
    auto prev = std::make_tuple(preX, preY);

    if (goal == start) return get_move_rand(map, curX, curY, preX, preY);

    std::map<std::tuple<int, int>, std::tuple<int, int>> parent;
    std::map<std::tuple<int, int>, int> cost;
    std::list<std::tuple<int, int>> explored;
    std::list<std::tuple<int, int>> frontier;

    auto heuristic_fn = [&goal, &map](std::tuple<int, int> n) -> int {

        int y = abs(std::get<1>(n) - std::get<1>(goal));
        int x1 = abs(std::get<0>(n) - std::get<0>(goal));
        int x2 = abs(std::get<0>(n) - std::get<0>(goal) - map->cols + 1);
        int x3 = abs(std::get<0>(n) - std::get<0>(goal) + map->cols - 1);

        return std::min({x1, x2, x3}) + y;
    };

    auto compareNodes = [&heuristic_fn, &cost](std::tuple<int, int> n1, std::tuple<int, int> n2) -> bool {
        return (cost[n1] + heuristic_fn(n1)) < (cost[n2] + heuristic_fn(n2));
    };

    explored.push_back(start);
    parent[start] = std::make_tuple(-1, -1);
    cost[start] = 0;
    auto children = map->get_moves(curX, curY);
    for (auto child: children) {
        if (child != prev) {
            frontier.push_back(child);
            parent[child] = start;
            cost[child] = cost[start] + 1;
        }
    }

    path.clear();

    while (!frontier.empty()) {
        frontier.sort(compareNodes);
        auto node = frontier.front();
        frontier.pop_front();

        if (node == goal) {
            while (parent[node] != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(node);
//            std::cout << " A* Explored: " << explored.size() << std::endl;
            return node;
        }

        explored.push_back(node);
        children = map->get_moves(node);
        for (auto child: children) {
            int new_cost = cost[node] + 1;
            
            if (std::find(frontier.begin(), frontier.end(), child) == frontier.end()) {
                auto ptr2 = std::find(explored.begin(), explored.end(), child);
                if (ptr2 == explored.end()){
                    cost[child] = new_cost;
                    parent[child] = node;
                    frontier.push_back(child);
                } else {
                    if (new_cost < cost[child]){
                        cost[child] = new_cost;
                        parent[child] = node;
                        frontier.push_back(child);
                        explored.erase(ptr2);
                    }
                }
            } else {
                if (new_cost < cost[child]) {
                    cost[child] = new_cost;
                    parent[child] = node;
                }
            }
        }
    }

    std::cout << "something went wrong!" << std::endl;
    return get_move_rand(map, curX, curY, preX, preY);
}
