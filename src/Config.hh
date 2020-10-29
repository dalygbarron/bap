#ifndef CONFIG_H
#define CONFIG_H

#include "Atlas.hh"
#include "Freak.hh"
#include "Bullet.hh"
#include <vector>

/**
 * Stores all the global shiet. Yeah I know the nerds, geeks, degenerates and 
 * cuckold fetishists of the world say that global state is banned but that is
 * because they have aspberger's disorder and it makes them do things they
 * cannot truly explain. Well of course the high ranking ones have little
 * manufactured explanations much like politicians do but they are made of
 * glass.
 */
namespace Config {
    constexpr int const SCREEN_WIDTH = 768;
    constexpr int const SCREEN_HEIGHT = 480;
    constexpr int const SCREEN_STACK_MAX = 8;
    constexpr float const  FPS_RATE = 5000;
    constexpr float const UPDATE_RATE = 0.02f;

    /**
     * Initialises the config and loads stuff from files etc etc.
     */
    bool init(SDL_Renderer &renderer);

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
     * Plays a song unless it is already playing.
     * @param name is the name of the song which is used to tell if it is
     *             playing.
     */
    void playSong(char const *name);

    /**
     * Gives you the atlas.
     * @return the atlas.
     */
    Atlas *getAtlas();
};

#endif
