#include "Window_Object.h"
#include "Screen_States.h"

#define TITLE (char *) "Pacman"
#define LOGO_PATH (char *) "Images/Play/pacman_logo.png"
#define SCREEN_WIDTH 975
#define SCREEN_HEIGHT 775
#define MS_PER_UPDATE 17

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Event event;
    Window_Object *Window = new Window_Object(TITLE, LOGO_PATH, SCREEN_WIDTH, SCREEN_HEIGHT);
    Game_State *State = new Menu_State(Window->Renderer);
    Game_State *newState;

    double previous = SDL_GetTicks();
    double lag = 0.0;
    bool game_over_condition = false;

    while (!game_over_condition) {
        // time
        double current = SDL_GetTicks();
        double dt = current - previous;
        previous = current;
        lag += dt;

        // input
        SDL_PollEvent(&event);

        // handle input
        Window->handle_input(event);
        newState = State->handle_input(event);
        if (newState != nullptr) {
            Game_State::exit_on_input(State);
            State = newState;
        }                                                      

        // update
        while (lag >= MS_PER_UPDATE) {
            newState = State->update();
            if (newState != nullptr) {
                delete State;
                State = newState;
            }
            lag -= MS_PER_UPDATE;
        }

        // draw
        Window->clear_background();
        State->draw();
        Window->swap_buffer();

        // update condition for while loop
        game_over_condition = State->exit_game || Window->close_Window;
    }

    delete Game_State::old_playState;
    delete State;
    delete Window;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();

    return 0;
}
