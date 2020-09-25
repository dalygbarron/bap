#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Uses an sdl renderer to render sprites that are all from the one texture.
 */
class Graphics {
    public:
        /**
         * Creates the graphics object.
         * @param renderer is the renderer to draw with.
         */
        Graphics(SDL_Renderer &renderer, std::string texturePath);

        /**
         * Adds a sprite to the list of sprites.
         * @param name   is the name of the sprite.
         * @param sprite is the actual shape of the sprte.
         */
        void addSprite(char const *name, SDL_Rect sprite);

        /**
         * Gives you a sprite that is saved on this graphics object.
         * @param name is the name of the sprite to get.
         * @return the shape of the sprite. If the sprite actually doesn't
         *         exist it returns something undefined and logs an error.
         */
        SDL_Rect getSprite(char const *name);

        /**
         * Draws a given sprite on the screen at the given spot.
         * @param x      is the x location to draw it at.
         * @param y      is the y location to draw it at.
         * @param sprite is what to draw from the built in texture atlas.
         */
        void draw(int x, int y, SDL_Rect sprite);

    private:
        SDL_Renderer &renderer;
        SDL_Texture &atlas;

};

#endif
