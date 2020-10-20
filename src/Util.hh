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

    /**
     * Returns the lower of two options.
     * @param a is the first option.
     * @param b is the second option.
     * @return the lower of a and b.
     */
    int min(int a, int b);

    /**
     * Returns the higher of two options.
     * @param a is the first option.
     * @param b is the second option.
     * @return the higher of a and b.
     */
    int max(int a, int b);

    /**
     * Tells you if the given character is whitespace.
     * @param c is the character to check.
     * @return true if it is whitespace.
     */
    bool white(char c);
};

#endif
