#ifndef BATCH_H
#define BATCH_H

#include "gl.hh"
#include <SDL2/SDL.h>
#include <vector>

/**
 * batches draws of stuff from a texture.
 */
class Batch {
    public:
        /**
         * A sprite to be drawn on the screen at a certai nspot.
         */
        class Sprite {
            public:
                SDL_Rect src;
                SDL_Rect dst;
        };

        /**
         * Creates the batch by setting the texture that it uses.
         * @param texture is the texture.
         */
        Batch(GLuint texture);

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
        void draw(SDL_Rect const &destination, SDL_Rect const &sprite);

        /**
         * Actually draws the content of this batch onto the screen.
         */
        void render();

    private:
        std::vector<SDL_Rect> items;
        GLuint texture;
        GLuint vao;
        GLuint vbo;
};

#endif
