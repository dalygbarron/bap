#include "Util.hh"
#include "Screen.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int const SCREEN_WIDTH = 768;
int const SCREEN_HEIGHT = 480;
int const  FPS_RATE = 5000;
char const *PIC_FILE = "assets/coom.png";
char const *SPRITE_FILE = "assets/cooxr.csv";
char const *FREAK_FILE = "assets/freaks.csv";
char const *BULLET_FILE = "assets/bullets.csv";

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
 * Contains the main loop and all that jazz. You obviously have to init sdl and
 * all that first and do not even START me about reentrancy or I will shoot you
 * in the fucking face.
 * @param renderer is used to render stuff.
 * @param start    is the screen that the program starts on.
 * @return the number the program as a whole should return.
 */
int body(SDL_Renderer &renderer, Screen *start) {
    bool running = true;
    int time = SDL_GetTicks();
    int updateTimer = 0;
    int fpsTimer = 0;
    int startIteration = 0;
    int iteration = 0;
    while (running) {
	SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
	    if (event.type == SDL_QUIT) running = false;
	}
	int currentTime = SDL_GetTicks();
	updateTimer += currentTime - time;
	fpsTimer += currentTime - time;
	time = currentTime;
	while (updateTimer >= start->getTimestep()) {
            start->update();
	    updateTimer -= start->getTimestep();
	}
	if (fpsTimer >= FPS_RATE) {
            SDL_LogInfo(
                SDL_LOG_CATEGORY_APPLICATION,
                "%.1f fps\n",
                (float)(iteration - startIteration) / (FPS_RATE / 1000)
            );
	    startIteration = iteration;
	    fpsTimer = 0;
	}
	//SDL_RenderClear(&renderer);
	start->render(renderer);
	SDL_RenderPresent(&renderer);
	iteration++;
    }
    return 0;
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
            "Window couldn't be created because: %s\n",
            SDL_GetError()
        );
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogCritical(
            SDL_LOG_CATEGORY_APPLICATION,
            "SDL_image couldn't init because: %s\n",
            IMG_GetError()
        );
        return 1;
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
    TestScreen *start = new TestScreen(*sack, 768);
    body(*renderer, start);
    delete sack;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
