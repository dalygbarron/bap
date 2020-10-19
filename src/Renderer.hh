#ifndef RENDERER_H
#define RENDERER_H

#include "Atlas.hh"
#include "Vec.hh"

/**
 * Does rendering stuff in a nice way and adds nice tools for it.
 */
class Renderer {
    public:
        Atlas const &atlas;

        /**
         * Creates the renderer.
         * @param renderer is the sdl renderer thingy.
         * @param atlas    is the texture atlas for sprite drawing.
         * @param guiBackground is the sprite for gui panel backgrounds.
         * @param guiSelect     is the sprite for gui selection overlay thing.
         * @param font          is the sprite for the font sheet.
         * @param guiBorderSize is the thickness of the border on panels.
         */
        Renderer(
            SDL_Renderer &renderer,
            Atlas const &atlas,
            SDL_Rect guiBackground,
            SDL_Rect guiSelect,
            SDL_Rect font,
            int guiBorderSize
        );

        /**
         * Draws a panel of some description within the given bounds.
         * @param bounds    is the bounds the panel fits within.
         * @return the area inside the border.
         */
        SDL_Rect panel(SDL_Rect bounds) const;

        /**
         * Writes some text on the screen wrapped within the given bounds.
         * @param bounds is the bounds to fit the text in.
         * @param text   is the text to write.
         */
        void text(SDL_Rect bounds, char const *text) const;

        /**
         * Draws a sprite on the screen at the given point by it's middle.
         * @param pos    is the midpoint of the sprite on the screen.
         * @param sprite is the sprite to draw from the renderer's atlas.
         */
        void sprite(Vec pos, SDL_Rect const &sprite) const;

    private:
        SDL_Renderer &renderer;
        SDL_Rect background;
        SDL_Rect select;
        SDL_Rect font;
        int borderSize;
};

#endif
