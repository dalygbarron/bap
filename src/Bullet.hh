#ifndef BULLET_H
#define BULLET_H

#include "Instanceable.hh"
#include <SDL2/SDL.h>

class Bullet: public Instanceable {
    public:
        /**
         * Creates a bullet by giving it it's stuff.
         * @param name is the name of the bullet.
         * @param sprite is the bullet's sprte.
         * @param speed is the speed at which the bullet moves.
         */
        Bullet(std::string name, SDL_Rect sprite, float speed);

        virtual void update(float delta, Instance<Bullet> *instance) override;
        
        virtual void render(
            SDL_Renderer &renderer,
            SDL_Texture &texture,
            Instance<Bullet> *instance
        ) override;

    private:
        std::string name;
	SDL_Rect sprite;
        float speed;
};

#endif
