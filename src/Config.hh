#ifndef CONFIG_H
#define CONFIG_H

#include "gl.hh"
#include <SDL2/SDL.h>

/**
 * Stores all the global shiet. Yeah I know the nerds, geeks, degenerates and 
 * cuckold fetishists of the world say that global state is banned but that is
 * because they have aspberger's disorder and it makes them do things they
 * cannot truly explain. Well of course the high ranking ones have little
 * manufactured explanations much like politicians do but they are made of
 * glass.
 */
namespace Config {
    constexpr int const SCREEN_WIDTH = 1024;
    constexpr int const SCREEN_HEIGHT = 600;
    constexpr int const SCREEN_STACK_MAX = 8;
    constexpr float const FPS_RATE = 5000;
    constexpr float const UPDATE_RATE = 0.02f;
    extern SDL_GLContext context;
    extern SDL_Window *window;

    /**
     * Plays a song unless it is already playing.
     * @param name is the name of the song which is used to tell if it is
     *             playing.
     */
    void playSong(char const *name);
};

#endif
