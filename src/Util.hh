#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/**
 * Contains some utility stuff.
 */
namespace Util {
    /**
     * Loads in a texture for enjoyment.
     * @param file     is the name of the file to load.
     * @param renderer is the renderer graphics object thingy.
     * @return the created texture in the case that it was ok, otherwise it
     *         will fail.
     */
    SDL_Texture *loadTexture(char const *file, SDL_Renderer &renderer);

    /**
     * Reads you a whole file.
     * @param file is the file to read.
     * @return a string object of the file so no ownership shit to deal with.
     */
    std::string readWholeFile(char const *file);
};

#endif
