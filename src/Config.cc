#include "Config.hh"
#include "Util.hh"
#include "csv.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <iostream>

std::string song = "";
Mix_Music *music = NULL;
Atlas *atlas;

bool Config::init(SDL_Renderer &renderer) {
    SDL_Texture *texture = Util::loadTexture("assets/coom.png", renderer);
    if (!texture) {
        return false;
    }
    atlas = new Atlas(*texture);
    atlas->loadSprites("assets/cooxr.csv");
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

Atlas *Config::getAtlas() {
    return atlas;
}
