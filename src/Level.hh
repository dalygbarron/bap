#ifndef LEVEL_H
#define LEVEL_H

#include "Graphics.hh"
#include <SDL2/SDL.h>

/**
 * A nice platforming level.
 */
class Level {
    public:
        static const int TILESET_WIDTH = 8;
        const int width;
        const int height;
        const SDL_Rect bounds;

        /**
         * Creates an empty level with a tileset and size.
         * @param width  is the width of the level.
         * @param height is the height of the level.
         * @param bounds is the level's tileset.
         */
        Level(int width, int height, SDL_Rect bounds);
        
        /**
         * Deletes the level's tiles again.
         */
        ~Level();

        /**
         * Draw the back and mid layers.
         * @param renderer is used to do the rendering.
         */
        void render(Graphics const &graphics);

    private:
        uint8_t *back;
        uint8_t *mid;
        uint8_t *front;
};

#endif
