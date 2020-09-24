#include "View.hh"
#include "Util.hh"
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDl could not initialise because: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "Brexit",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window couldn't be created because: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture texture = Util::loadTexture("picture.png");
    View view(*window, *texture);
    SDL_FillRect(
        view.screenSurface,
        NULL,
        SDL_MapRGB(view.screenSurface->format, 0x87, 0xaa, 0xff)
    );
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
