#ifndef BATCH_H
#define BATCH_H

#include "Texture.hh"
#include <SDL2/SDL.h>
#include <vector>

/**
 * batches draws of stuff from a texture.
 */
class Batch {
    public:
        static unsigned int const ITEM_BUFFER = 0;
        static unsigned int const TEXTURE_BUFFER = 1;
        static unsigned int const N_BUFFER = 2;

        /**
         * Creates the batch by setting the texture that it uses.
         * @param texture is the texture.
         */
        Batch(Texture *texture, int max);

        /**
         * Deletes the buffers and stuff.
         */
        ~Batch();

        /**
         * Starts a new frame.
         */
        void clear();

        /**
         * Draws a nice sprite centred for you.
         * @param x        is the x position to draw.
         * @param y        is the y position to draw.
         * @param sprite   is the sprite to draw.
         */
        void draw(int x, int y, SDL_Rect const &sprite);

        /**
         * Draws a sprite and stretches it to the given bounds.
         * @param destination is the rectangle to draw it to.
         * @param sprite is the sprite to draw.
         */
        void draw(SDL_Rect const &dst, SDL_Rect const &src);

        /**
         * Actually draws the content of this batch onto the screen.
         */
        void render();

    private:
        Texture const *texture;
        int const max;
        GLfloat *items;
        GLfloat *textureItems;
        int n = 0;
        GLuint buffers[Batch::N_BUFFER];
        GLuint vao;
};

#endif
