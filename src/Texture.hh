#ifndef TEXTURE_H
#define TEXTURE_H

#include "gl.hh"

/**
 * Stores an opengl texture with some info about it.
 */
class Texture {
    public:
        GLuint const glTexture;
        unsigned int const width;
        unsigned int const height;

        /**
         * DEletes the shiet.
         */
        ~Texture();

        /**
         * Loads a texture in from a file.
         * @param file is the name of the file.
         * @return the loaded texture or null if it couldn't do it.
         */
        static Texture *loadTexture(char const *file);

    private:
        /**
         * Creates the texture by providing the inner gl texture, the width,
         * and the height.
         * @param glTexture is the actual opengl handle to the texture.
         * @param width     is the width of the image.
         * @param height    is the height of the image.
         */
        Texture(GLuint glTexture, unsigned int width, unsigned int height);
};

#endif
