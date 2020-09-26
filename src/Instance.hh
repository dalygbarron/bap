#ifndef INSTANCE_H
#define INSTANCE_H

#include "Vec.hh"

/**
 * Instance of something that exists in 2d space. Basically it's like that
 * flyweight pattern and this is the fly, it can be for either bullets or
 * freaks. Also, since these are often going to be pooled, it cannot have any
 * constant fields.
 */
template <class T> class Instance {
    public:
        bool alive;
        Vec position;
        Vec velocity;
        Vec accelerator;
        T const *model;

        /**
         * Does basic physics update as in makes it move and nothing else. If
         * you want to make it that it collides bounces off the world or
         * whatever like a character then probably check that before this step,
         * but if you want it to hit stuff and kill it or blow up like a bullet
         * check it's collisions after this step I guess.
         * @param delta is the timestep.
         */
        void update(float delta) {
            Vec velocityPresent = this->velocity;
            Vec acceleratorPresent = this->accelerator;
            velocityPresent.mult(delta);
            acceleratorPresent.mult(delta);
            this->position.add(velocityPresent);
            this->velocity.add(acceleratorPresent);
        };
};

#endif
