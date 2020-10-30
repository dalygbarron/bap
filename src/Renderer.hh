#ifndef RENDERER_H
#define RENDERER_H

#include "Atlas.hh"
#include "Vec.hh"

/**
 * Does rendering stuff in a nice way and adds nice tools for it.
 */
namespace Renderer {
    /**
     * Draws a border in the given bounds rather than around it.
     * @param renderer is the real sdl renderer.
     * @param bounds   is the bounds to fit it in. If you make this too small
     *                 then it will render nothing at all.
     * @param sprite   is the image to draw the border with, it is one of
     *                 those 9patch things but we do not use the middle.
     * @param width    is the width of the borders on the 9patch.
     * @return the inner bounds of the border which will have 0 width and
     *         height if you make it too small for it's thickness.
     */
    SDL_Rect border(
        SDL_Renderer *renderer,
        SDL_Rect bounds,
        SDL_Rect sprite,
        int width
    );

    /**
     * Draws a rectangle with an image tiled in it starting from the top
     * left corner.
     * @param renderer is the real sdl renderer.
     * @param bounds   is the bounds to draw it in.
     * @param sprite   is the pic to tile.
     */
    void rect(SDL_Renderer *renderer, SDL_Rect bounds, SDL_Rect sprite);

    /**
     * Writes some text on the screen using a custom font.
     * @param renderer is the real sdl renderer.
     * @param pos      is the top left at which to draw.
     * @param text     is the text to write.
     * @param font     is the font sheet to draw with.
     */
    void text(
        SDL_Renderer *renderer,
        Vec pos,
        char const *text,
        SDL_Rect font
    );

    /**
     * Draws a sprite on the screen at the given point by it's middle.
     * @param renderer is the real sdl renderer.
     * @param bounds   is the midpoint of the sprite on the screen.
     * @param sprite   is the sprite to draw from the renderer's atlas.
     */
    void sprite(
        SDL_Renderer *renderer,
        SDL_Rect const &bounds,
        SDL_Rect const &sprite
    );
};

#endif
