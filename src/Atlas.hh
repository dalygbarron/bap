#ifndef ATLAS_H
#define ATLAS_H

#include <SDL2/SDL.h>
#include <map>

/**
 * Stores nice pictures for you to enjoy.
 */
class Atlas {
    public:
        /**
         * Creates the atlas but does not populate it's nice sprites.
         * @param texture is the pic that the atlas is of.
         */
        Atlas(SDL_Texture &texture);

        /**
         * Loads in sprites from a file yeeach.
         * @param file is the path to the file to load them from.
         */
        void loadSprites(char const *file);

        /**
         * Adds a sprite to the atlas.
         * @param name   is the name of the sprite.
         * @param sprite is the outline of the sprite.
         */
        void addSprite(char const *name, SDL_Rect sprite);

        /**
         * Gives you a sprite from the atlas.
         * @param name is the name of the sprite to get.
         * @return the sprite or something empty if you gave a wrong name.
         */
        SDL_Rect getSprite(char const *name) const;

        /**
         * Gives you the width of the texture.
         * @return the width.
         */
        int getWidth() const;

        /**
         * Gives you the height of the texture.
         * @return the height.
         */
        int getHeight() const;

        /**
         * Draws a nice sprite centred for you.
         * @param renderer is the renderer to draw with.
         * @param x        is the x position to draw.
         * @param y        is the y position to draw.
         * @param sprite   is the sprite to draw.
         */
        void draw(
            SDL_Renderer &renderer,
            int x,
            int y,
            SDL_Rect const &sprite
        ) const;

    private:
        std::map<std::string, SDL_Rect> sprites;
        SDL_Texture &texture;
        int width;
        int height;
};

#endif
