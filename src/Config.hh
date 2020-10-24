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
    int const SCREEN_WIDTH = 768;
    int const SCREEN_HEIGHT = 480;
    int const SCREEN_STACK_MAX = 16;
    float const  FPS_RATE = 5000;
    char const *PIC_FILE = "assets/coom.png";
    char const *SPRITE_FILE = "assets/cooxr.csv";
    Atlas *atlas;
    std::vector<Freak> freaks;
    std::vector<Bullet> bullets;

    /**
     * Initialises the config and loads stuff from files etc etc.
     */
    bool init();

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
};

#endif
