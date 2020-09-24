#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>

/**
 * Contains some utility stuff.
 */
namespace Util {
    /**
     * Loads in a texture for enjoyment.
     * @param file is the name of the file to load.
     * @return the created texture in the case that it was ok, otherwise it
     *         will fail.
     */
    SDL_Texture *loadTexture(char const *file);
};

#endif
