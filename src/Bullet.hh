#ifndef BULLET_H
#define BULLET_H

#include "Instance.hh"
#include "Atlas.hh"
#include <SDL2/SDL.h>
#include <string>

class Bullet {
    public:
        /**
         * Creates a bullet by giving it it's stuff.
         * @param name is the name of the bullet.
         * @param sprite is the bullet's sprte.
         * @param speed is the speed at which the bullet moves.
         */
        Bullet(std::string name, SDL_Rect sprite, float speed);

        /**
         * Gives you the name of the bullet.
         * @return the name.
         */
        std::string getName() const;

        /**
         * Gives you the sprite.
         * @return a copy of the sprite rect.
         */
        SDL_Rect getSprite() const;

        /**
         * Gives you the speed.
         * @return the speed.
         */
        float getSpeed() const;

        /**
         * Renders an instance onto the screen somewhere.
         * @param atlas    is the sprite atlas which also draws stuff.
         * @param instance is the instance to draw.
         */
        void render(
            SDL_Renderer &renderer,
            Atlas const &atlas,
            Instance<Bullet> const &instance
        ) const;

    private:
        std::string name;
	SDL_Rect sprite;
        float speed;
};

#endif
