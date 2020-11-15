#ifndef BATCH_H
#define BATCH_H

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
        Batch(SDL_Texture *texture);

        /**
         * Adds a texture
        add(SDL_Rect src, SDL_Rect dst);

    private:
        std::vector<SDL_Rect> items;

};

#endif
