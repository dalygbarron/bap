#include "Util.hh"
#include "Config.hh"
#include "Renderer.hh"
#include "janet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#include <stdio.h>

SDL_Renderer *renderer;

Janet drawBorder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *sprite = janet_unwrap_tuple(argv[1]);
    float width = janet_unwrap_number(argv[1]);
    Renderer::border(
        renderer,
        {
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1])),
            static_cast<int>(janet_unwrap_number(border[2])),
            static_cast<int>(janet_unwrap_number(border[3]))
        },
        {
            static_cast<int>(janet_unwrap_number(sprite[0])),
            static_cast<int>(janet_unwrap_number(sprite[1])),
            static_cast<int>(janet_unwrap_number(sprite[2])),
            static_cast<int>(janet_unwrap_number(sprite[3]))
        },
        width
    );
    return janet_wrap_nil();
}

Janet drawRect(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *sprite = janet_unwrap_tuple(argv[1]);
    Renderer::rect(
        renderer,
        {
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1])),
            static_cast<int>(janet_unwrap_number(border[2])),
            static_cast<int>(janet_unwrap_number(border[3]))
        },
        {
            static_cast<int>(janet_unwrap_number(sprite[0])),
            static_cast<int>(janet_unwrap_number(sprite[1])),
            static_cast<int>(janet_unwrap_number(sprite[2])),
            static_cast<int>(janet_unwrap_number(sprite[3]))
        }
    );
    return janet_wrap_nil();
}

Janet drawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *font = janet_unwrap_tuple(argv[1]);
    Renderer::text(
        renderer,
        Vec(
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1]))
        ),
        (char *)janet_unwrap_string(argv[2]),
        {
            static_cast<int>(janet_unwrap_number(font[0])),
            static_cast<int>(janet_unwrap_number(font[1])),
            static_cast<int>(janet_unwrap_number(font[2])),
            static_cast<int>(janet_unwrap_number(font[3]))
        }
    );
    return janet_wrap_nil();
}

Janet getSprite(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char const *name = (char const *)janet_getcstring(argv, 0);
    SDL_Rect sprite = Config::getAtlas()->getSprite(name);
    Janet list[4];
    list[0] = janet_wrap_integer(sprite.x);
    list[1] = janet_wrap_integer(sprite.y);
    list[2] = janet_wrap_integer(sprite.w);
    list[3] = janet_wrap_integer(sprite.h);
    return janet_wrap_tuple(janet_tuple_n(list, 4));
}

Janet getScreenDimensions(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    Janet items[2];
    items[0] = janet_wrap_integer(Config::SCREEN_WIDTH);
    items[1] = janet_wrap_integer(Config::SCREEN_HEIGHT);
    return janet_wrap_tuple(janet_tuple_n(items, 2));
}

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
        JanetFiber *script;
};

/**
 * Loads in the scripting functions yeet.
 */
void initScripting() {
    JanetReg const cFunctions[] = {
        {"draw-rect", drawRect, "(screen/draw-rect)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-border", drawBorder, "(screen/draw-border)\nDraws a border at the given place with the given sprite and width."},
        {"draw-text", drawText, "(screen/draw-text)\nDraws some text."},
        {"get-sprite", getSprite, "(screen/get-sprite)\nGives you the bounds of a sprite in a tuple like (x y w h)"},
        {"get-screen-dimensions", getScreenDimensions, "(screen/get-screen-dimensions)\nGives you the dimensions of the screen like (w h)"},
        {NULL, NULL, NULL}
    };
    JanetTable *env = janet_core_env(NULL);
    janet_cfuns(env, "screen", cFunctions);
}

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
    program->fpsTimer += currentTime - program->time;
    program->time = currentTime;
    JanetFiberStatus status = janet_fiber_status(program->script);
    if (status != JANET_STATUS_DEAD && status != JANET_STATUS_ERROR) {
        Janet out;
        janet_continue(program->script, janet_wrap_nil(), &out);
        status = janet_fiber_status(program->script);
        if (status != JANET_STATUS_ALIVE && status != JANET_STATUS_PENDING) {
            janet_stacktrace(program->script, out);
        }
    }
    if (program->fpsTimer >= Config::FPS_RATE) {
        printf(
            "%.2f fps\n",
            (float)(program->iteration - program->startIteration) /
                (Config::FPS_RATE / 1000)
        );
        program->startIteration = program->iteration;
        program->fpsTimer = 0;
    }
    SDL_RenderPresent(renderer);
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
        printf("SDL could not initialise because: %s\n", SDL_GetError());
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
        printf("Window couldn't be created because: %s", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image couldn't init because: %s", IMG_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer couldn't init because: %s", Mix_GetError());
    }
    renderer = SDL_CreateRenderer(
	window,
	-1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        printf("Couldn't start renderer because: %s\n", SDL_GetError());
        return 1;
    }
    SDL_RenderSetLogicalSize(
        renderer,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT
    );
    if (!Config::init(*renderer)) {
        printf("Couldn't init config\n");
        return 1;
    }
    janet_init();
    initScripting();
    ProgramState *program = new ProgramState();
    program->script = Util::loadFiber("script/init.janet");
    program->running = true;
    program->time = SDL_GetTicks();
    program->updateTimer = 0;
    program->fpsTimer = 0;
    program->startIteration = 0;
    program->iteration = 0;
    while (program->running && program->script) {
        loop(program);
        #ifndef __EMSCRIPTEN__
        SDL_Delay(10);
        #endif
    }
    return 0;
}
