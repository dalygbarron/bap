#ifndef SACK_H
#define SACK_H

#include "Atlas.hh"
#include "Freak.hh"
#include "Bullet.hh"
#include "janet.h"
#include <SDL2/SDL_mixer.h>
#include <vector>


/**
 * Holds all the general configuration bits that the game has to load in like
 * the list of enemies and bullets, and the spritesheet.
 */
class Sack {
    public:
        std::vector<Freak> freaks;
        std::vector<Bullet> bullets;
        Atlas *atlas;

        /**
         * Creates the sack and sets the atlas.
         * @param atlas is the thingy with the sprites.
         */
        Sack(Atlas *atlas);

        /**
         * Loads in freaks from a file.
         * @param file is the path to the file to load from.
         */
        void loadFreaks(char const *file);

        /**
         * Loads in bullets from a file.
         * @param file is the path to the file to load from.
         */
        void loadBullets(char const *file);

        /**
         * Plays a song unless it is already playing in which case it does
         * nothing.
         * @param file is the path to the file to play.
         */
        void playSong(char const *file) const;

        /**
         * Creates a script with the default config.
         * @param path is the path to the script file to read.
         * @return the created script.
         */
        // WrenVM *createScript(std::string path) const;

    private:
        mutable std::string song = "";
        mutable Mix_Music *music = NULL;
};

#endif
