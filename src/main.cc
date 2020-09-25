#include "Util.hh"
#include "Screen.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 480;
const int FPS_RATE = 5000;

/**
 * Loads in the texture atlas thingy that the game is going to use.
 * @param renderer  is the renderer which is needed to load textures.
 * @param picFile   is the path to the picture for the atlas.
 * @param atlasFile is the path to the file that defines where each sprite is.
 * @return the created atlas, unless it fucked up in which case it will return
 *         null.
 */
Atlas *loadAtlas(
    SDL_Renderer &renderer,
    std::string picFile,
    std::string atlasFile
) {
    SDL_Texture *texture = Util::loadTexture(picFile.c_str(), renderer);
    if (texture) {
        Atlas *atlas = new Atlas(*texture);
        atlas->addSprite("nerd", {0, 0, 30, 40});
        return atlas;
    }
    return NULL;
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
	    printf(
                "FPS: %f\n",
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
        printf("SDl could not initialise because: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Brexit Simulator",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (window == NULL) {
        printf("Window couldn't be created because: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
	printf("SDL_image couldn't init because: %s\n", IMG_GetError());
	return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
	window,
	-1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (renderer == NULL) {
	printf("Couldn't start renderer because: %s\n", SDL_GetError());
	return 1;
    }
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    Atlas *atlas = loadAtlas(*renderer, "picture.png", "nerd.xml");
    TestScreen *start = new TestScreen(*atlas, 768);
    body(*renderer, start);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
