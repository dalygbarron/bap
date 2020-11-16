#include "Config.hh"
#include "Util.hh"
#include "csv.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <iostream>

SDL_Renderer *Config::renderer = NULL;
std::string song = "";
Mix_Music *music = NULL;

bool Config::init(SDL_Renderer &renderer) {
    Config::renderer = &renderer;
    return true;
}

void Config::playSong(char const *file) {
    if (!music || strcmp(song.c_str(), file) != 0) {
        if (music) Mix_FreeMusic(music);
        music = Mix_LoadMUS(file);
        if (music) {
            Mix_PlayMusic(music, -1);
            song = file;
        } else {
            SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Couldn't load music '%s'",
                file
            );
        }
    }
}
