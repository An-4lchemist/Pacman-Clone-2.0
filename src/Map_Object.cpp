#include "Map_Object.h"

Map_Object::Map_Object(int w, int h, SDL_Renderer *Renderer)
        : cell_width(w), cell_height(h), Renderer(Renderer) {

    read_map(MAP_PATH);
    create_map();

    SDL_Surface *surface = IMG_Load(IMG_MAP_PATH);
    texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
}

void Map_Object::draw() {
    if (dev_mode) {
        SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
        for (auto rect: walls) {
            SDL_RenderFillRect(Renderer, rect);
        }
    } else {
        SDL_Rect *dstRect = new SDL_Rect{0, 0, cell_width * cols, cell_height * rows};
        SDL_RenderCopy(Renderer, texture, nullptr, dstRect);
        delete dstRect;
    }
}

bool Map_Object::is_wall(int col, int row) const {
    if (!((0 <= col && col < cols) && (0 <= row && row < rows))) return true;
    return (env_layout[row][col] == 1);
}

std::tuple<int, int> Map_Object::get_nearest_move(std::tuple<int, int> node) const {
    if (!is_wall(std::get<0>(node), std::get<1>(node))) {
        return node;
    } else {
        std::list<std::tuple<int, int>> frontier;
        std::vector<std::tuple<int, int>> explored;
        frontier.push_back(node);

        while (!frontier.empty()) {
            auto n1 = frontier.front();
            frontier.pop_front();

            int x_index, y_index;
            std::tie(x_index, y_index) = n1;

            if (!is_wall(x_index, y_index)) {
                return n1;
            } else {
                explored.push_back(n1);
                if (std::find(explored.begin(), explored.end(), std::make_tuple(x_index - 1, y_index)) ==
                    explored.end())
                    frontier.emplace_back(x_index - 1, y_index);
                if (std::find(explored.begin(), explored.end(), std::make_tuple(x_index + 1, y_index)) ==
                    explored.end())
                    frontier.emplace_back(x_index + 1, y_index);
                if (std::find(explored.begin(), explored.end(), std::make_tuple(x_index, y_index - 1)) ==
                    explored.end())
                    frontier.emplace_back(x_index, y_index - 1);
                if (std::find(explored.begin(), explored.end(), std::make_tuple(x_index, y_index + 1)) ==
                    explored.end())
                    frontier.emplace_back(x_index, y_index + 1);
            }
        }

        return {1, 1};
    }
}

std::vector<std::tuple<int, int>> Map_Object::get_moves(int x_index, int y_index) const {
    std::vector<std::tuple<int, int>> moves;

    if (x_index == 0 && y_index == 14) {
        moves.emplace_back(27, y_index);
        moves.emplace_back(1, y_index);
    } else if (x_index == 27 && y_index == 14) {
        moves.emplace_back(26, y_index);
        moves.emplace_back(0, y_index);
    } else {
        if (!is_wall(x_index - 1, y_index)) {
            moves.emplace_back(x_index - 1, y_index);
        }
        if (!is_wall(x_index + 1, y_index)) {
            moves.emplace_back(x_index + 1, y_index);
        }
        if (!is_wall(x_index, y_index - 1)) {
            moves.emplace_back(x_index, y_index - 1);
        }
        if (!is_wall(x_index, y_index + 1)) {
            moves.emplace_back(x_index, y_index + 1);
        }
    }
    return moves;
}

std::vector<std::tuple<int, int>> Map_Object::get_moves(std::tuple<int, int> node) const {
    return get_moves(std::get<0>(node), std::get<1>(node));
}

std::vector<std::tuple<int, int>> Map_Object::get_pellets_loc() const {
    std::vector<std::tuple<int, int>> locations;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (env_layout[i][j] == 2) {
                locations.emplace_back(j, i);
            }
        }
    }
    return locations;
}

std::vector<std::tuple<int, int>> Map_Object::get_pow_pellets_loc() const {
    std::vector<std::tuple<int, int>> locations;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (env_layout[i][j] == 3) {
                locations.emplace_back(j, i);
            }
        }
    }
    return locations;
}

void Map_Object::read_map(const std::string &fname) {
    rows = 31;
    cols = 28;

    std::fstream fp;
    fp.open(fname, std::ios::in);
    if (fp.is_open()) {
        std::string line, word;
        while (getline(fp, line)) {
            std::istringstream line_stream(line);
            std::vector<int> row_vector;
            while (std::getline(line_stream, word, ' ')) {
                row_vector.push_back(stoi(word));
                if (row_vector.size() == cols) {
                    env_layout.push_back(row_vector);
                    row_vector.clear();
                }
            }
        }
        fp.close();
    }
}

void Map_Object::create_map() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (env_layout[i][j] == 1) {
                SDL_Rect *new_Rect = new SDL_Rect;
                new_Rect->x = j * cell_width;
                new_Rect->y = i * cell_height;
                new_Rect->w = cell_width;
                new_Rect->h = cell_height;
                walls.push_back(new_Rect);
            }
        }
    }
}

Map_Object::~Map_Object() {
    SDL_DestroyTexture(texture);
    for (auto rect: walls) {
        delete rect;
    }
}
