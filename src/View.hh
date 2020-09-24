#ifndef VIEW_H
#define VIEW_H

#include <SDL2/SDL.h>

/**
 * Keeps track of the window and all that jazz.
 */
class View {
    public:
        /**
         * Secret constructor that gives you those thingies which are needed.
         * @param window the window that the view uses.
         * @param atlas  is the texture atlas that all the textures are in.
         */
        View(SDL_Window &window, SDL_Texture &atlas);

        SDL_Window &window;
        SDL_Surface *screenSurface;
        SDL_Texture &atlas;

    private:
};


#endif
