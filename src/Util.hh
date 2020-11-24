#ifndef UTIL_H
#define UTIL_H

#include "gl.hh"
#include "janet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/**
 * Contains some utility stuff.
 */
namespace Util {
    /**
     * Converts some text into a shader.
     * @param type is the type of shader.
     * @param src  is the source code of the shader.
     * @return the id of the created shader or 0 on error.
     */
    GLuint createShader(GLenum type, char const *src);

    /**
     * Creates a shader program with a vertex shader and a fragment shader.
     * @param vertex   is the vertex shader.
     * @param fragment is the fragment shader.
     * @return the id of the program created unless it's 0 which means fail.
     */
    GLuint createShaderProgram(GLuint vertex, GLuint fragment);

    /**
     * Loads in a texture for enjoyment.
     * @param file     is the name of the file to load.
     * @return the id of the texture in the case that it was ok, otherwise it
     *         will fail.
     */
    GLuint loadTexture(char const *file);

    /**
     * Reads you a whole file.
     * @param file is the file to read.
     * @return a string object of the file so no ownership shit to deal with.
     */
    std::string readWholeFile(char const *file);

    /**
     * Loads you a nice fiber and starts it up for you. Essentially you pass
     * a script and the thing that the script evaluates to should be a function
     * that can be turned into a fiber.
     * @param path is the path to the file to load the diber from.
     * @return a pointer to the fiber.
     */
    JanetFiber *loadFiber(char const *path);

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

    /**
     * Tells you the dimensions of the screen. Obviously please don't call this
     * until you have initialised opengl and co.
     * @return a rectangle that depicts where the window is on the screen and
     *         it's dimensions.
     */
    SDL_Rect getScreen();
};

#endif
