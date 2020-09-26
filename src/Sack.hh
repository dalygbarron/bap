#ifndef SACK_H
#define SACK_H

#include "Atlas.hh"
#include "Freak.hh"
#include "Bullet.hh"
#include <vector>


/**
 * Holds all the general configuration bits that the game has to load in like
 * the list of enemies and bullets, and the spritesheet.
 */
class Sack {
    public:
        std::vector<Freak> freaks;
        std::vector<Bullet> bullets;
        Atlas const &atlas;

        /**
         * Creates the sack and sets the atlas.
         * @param atlas is the thingy with the sprites.
         */
        Sack(Atlas const &atlas);
};

#endif
