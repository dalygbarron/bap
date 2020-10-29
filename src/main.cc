#include "Util.hh"
#include "Screen.hh"
#include "Config.hh"
#include "janet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#include <stdio.h>

/**
 * Gotta do this shit for emscripten, annoying I know.
 */
class ProgramState {
    public:
        bool running;
        int time;
        int updateTimer;
        int fpsTimer;
        int startIteration;
        int iteration;
        SDL_Renderer *renderer;
        Screen *screens[Config::SCREEN_STACK_MAX];

        /**
         * Gives you the current screen on top of the stack.
         * @return the top screen.
         */
        Screen *current() {
            if (this->screen >= 0) return this->screens[this->screen];
            return NULL;
        }
};

/**
 * The main loop of the program.
 * @param data is meant to be a program state object which contains all the
 *             variables the loop needs between iterations.
 */
void loop(void *data) {
    struct ProgramState *program = (ProgramState *)data;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            program->running = false;
            return;
        }
    }
    int currentTime = SDL_GetTicks();
    program->updateTimer += currentTime - program->time;
    program->fpsTimer += currentTime - program->time;
    program->time = currentTime;
    int step = program->current()->getTimestep();
    while (program->updateTimer >= step) {
        Screen::TransferOperation operation = program->current()->update();
        program->updateTimer -= step;
        switch (operation.type) {
            case Screen::TransferOperation::POP:
                delete program->screens[program->screen];
                program->screen--;
                step = program->current()->getTimestep();
                break;
            case Screen::TransferOperation::PUSH:
                program->screen++;
                program->screens[program->screen] = operation.next;
                step = operation.next->getTimestep();
                break;
            case Screen::TransferOperation::REPLACE:
                delete program->screens[program->screen];
                program->screens[program->screen] = operation.next;
                step = operation.next->getTimestep();
                break;
            case Screen::TransferOperation::NONE:
                break;
        }
        if (program->screen < 0) {
            program->running = false;
            return;
        }
    }
    if (program->fpsTimer >= Config::FPS_RATE) {
        SDL_LogInfo(
            SDL_LOG_CATEGORY_APPLICATION,
            "%.1f fps\n",
            (float)(program->iteration - program->startIteration) /
                (Config::FPS_RATE / 1000)
        );
        program->startIteration = program->iteration;
        program->fpsTimer = 0;
    }
    SDL_RenderClear(program->realRenderer);
    program->current()->render(*program->renderer);
    SDL_RenderPresent(program->realRenderer);
    program->iteration++;
}

/**
 * The start of the program.
 * @param argc is the number of arguments.
 * @param argv is the list of arguments.
 * @return the return code of the program.
 */
int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL could not initialise because: %s\n",
            SDL_GetError()
        );
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "BAP",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "Window couldn't be created because: %s",
            SDL_GetError()
        );
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL_image couldn't init because: %s",
            IMG_GetError()
        );
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL_Mixer couldn't init because: %s",
            Mix_GetError()
        );
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
	window,
	-1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't start renderer because: %s\n",
            SDL_GetError()
        );
        return 1;
    }
    SDL_RenderSetLogicalSize(
        renderer,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT
    );
    if (!Config::init(*renderer)) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't init config\n"
        );
        return 1;
    }
    janet_init();
    Screen::initScripting();
    char const *message = "you are a nerd";
    BlankScreen *start = new BlankScreen(
        "script/init.janet",
        0,
        NULL
    );
    ProgramState *program = new ProgramState();
    program->renderer = new Renderer(*renderer);
    program->realRenderer = renderer;
    program->running = true;
    program->time = SDL_GetTicks();
    program->updateTimer = 0;
    program->fpsTimer = 0;
    program->startIteration = 0;
    program->iteration = 0;
    program->screens[0] = start;
    program->screen = 0;
    while (program->running) {
        loop(program);
        #ifndef __EMSCRIPTEN__
        SDL_Delay(10);
        #endif
    }
    return 0;
}
