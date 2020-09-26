#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

class Bullet {
    public:
        /**
         * Creates a bullet by giving it it's stuff.
         * @param name is the name of the bullet.
         * @param sprite is the bullet's sprte.
         * @param speed is the speed at which the bullet moves.
         */
        Bullet(std::string name, SDL_Rect sprite, float speed);

    private:
        std::string name;
	SDL_Rect sprite;
        float speed;
};

#endif
