#ifndef INSTANCEABLE_H
#define INSTANCEABLE_H

#include <SDL2/SDL.h>

/**
 * Represents a type of thing that can be made into a flyweight instance.
 */
class Instanceable {
    public:
        /**
         * Updates an instance like it is an instance of this thingy.
         * @param delta    is the time step.
         * @param instance is the instance to update.
         */
        virtual template <class T> void update(
            float delta,
            Instance<T> *instance
        ) const = 0;

        /**
         * Renders an instance like is an instance of this thingy.
         * @param renderer is the renderer to render with.
         * @param atlas    is the texture atlas.
         * @param instance is the instance to render.
         */
        virtual template <class T> void render(
            SDL_Renderer &renderer,
            Atlas const &atlas,
            Instance<T> *instance
        ) const = 0;
};

#endif
