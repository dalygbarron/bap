#include "Util.hh"
#include "Screen.hh"
#include "janet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif
#include <stdio.h>

int const SCREEN_WIDTH = 768;
int const SCREEN_HEIGHT = 480;
int const  FPS_RATE = 5000;
char const *PIC_FILE = "assets/coom.png";
char const *SPRITE_FILE = "assets/cooxr.csv";
char const *FREAK_FILE = "assets/freaks.csv";
char const *BULLET_FILE = "assets/bullets.csv";

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
        SDL_Renderer *realRenderer;
        Renderer *renderer;
        Screen *screen;
};

/**
 * Loads in a sack.
 * @param renderer   is the renderer which is needed to load textures.
 * @param picFile    is the path to the game's texture atlas picture.
 * @param atlasFile  is the path to the file that describes the game's sprites.
 * @param freakFile  is the path to the file that contains the game's freaks.
 * @param bulletFile is the path to the file that contains the game's bullets.
 * @return the sack unless it was unable to load the texture which I think it
 *         the only thing that absolutely has to succeed. If other stuff fucks
 *         up it will just run without it and crash later lol.
 */
Sack *loadSack(
    SDL_Renderer &renderer,
    char const *picFile,
    char const *atlasFile,
    char const *freakFile,
    char const *bulletFile
) {
    SDL_Texture *texture = Util::loadTexture(picFile, renderer);
    if (!texture) return NULL;
    Atlas *atlas = new Atlas(*texture);
    atlas->loadSprites(atlasFile);
    Sack *sack = new Sack(atlas);
    sack->loadFreaks(freakFile);
    sack->loadBullets(bulletFile);
    return sack;
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
        if (event.type == SDL_QUIT) program->running = false;
    }
    int currentTime = SDL_GetTicks();
    program->updateTimer += currentTime - program->time;
    program->fpsTimer += currentTime - program->time;
    program->time = currentTime;
    while (program->updateTimer >= program->screen->getTimestep()) {
        program->screen->update();
        program->updateTimer -= program->screen->getTimestep();
    }
    if (program->fpsTimer >= FPS_RATE) {
        SDL_LogInfo(
            SDL_LOG_CATEGORY_APPLICATION,
            "%.1f fps\n",
            (float)(program->iteration - program->startIteration) /
                (FPS_RATE / 1000)
        );
        program->startIteration = program->iteration;
        program->fpsTimer = 0;
    }
    // SDL_RenderClear(&renderer);
    program->screen->render(*program->renderer);
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
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
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
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    janet_init();
    Sack *sack = loadSack(
        *renderer,
        PIC_FILE,
        SPRITE_FILE,
        FREAK_FILE,
        BULLET_FILE
    );
    if (!sack) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't load sack\n"
        );
        return 1;
    }
    BlankScreen *start = new BlankScreen(*sack, "assets/wren/talk.wren");
    ProgramState *program = new ProgramState();
    program->renderer = new Renderer(
        *renderer,
        *sack->atlas,
        sack->atlas->getSprite("panel"),
        sack->atlas->getSprite("select"),
        sack->atlas->getSprite("font"),
        5
    );
    program->realRenderer = renderer;
    program->running = true;
    program->time = SDL_GetTicks();
    program->updateTimer = 0;
    program->fpsTimer = 0;
    program->startIteration = 0;
    program->iteration = 0;
    program->screen = start;
    #ifdef __EMSCRIPTEN__
    // Receives a function to call and some user data to provide it.
    emscripten_set_main_loop_arg(loop, program, 0, false);
    #else
    while (program->running) {
        loop(program);
        // TODO: not go too fast when vsync ain't there for us.
        // SDL_Delay(time_to_next_frame());
    }
    #endif
    janet_deinit();
    return 0;
}
