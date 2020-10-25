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
std::vector<Freak> freaks;
std::vector<Bullet> bullets;

void loadFreaks(char const *file) {
    io::CSVReader<4> csv(file);
    csv.read_header(
        io::ignore_extra_column,
        "name",
        "sprite",
        "behaviour",
        "gravity"
    );
    std::string name, sprite, behaviour;
    float gravity;
    while (csv.read_row(name, sprite, behaviour, gravity)) {
        SDL_Rect actualSprite = atlas->getSprite(sprite.c_str());
        Freak::Behaviour actualBehaviour = Freak::stringToBehaviour(
            behaviour
        );
        freaks.emplace(
            freaks.begin(),
            name,
            actualSprite,
            gravity,
            actualBehaviour
        );
    }
}

void loadBullets(char const *file) {
    io::CSVReader<3> csv(file);
    csv.read_header(io::ignore_extra_column, "name", "sprite", "speed");
    std::string name;
    std::string sprite;
    float speed;
    while (csv.read_row(name, sprite, speed)) {
        SDL_Rect actualSprite = atlas->getSprite(sprite.c_str());
        bullets.emplace(
            bullets.begin(),
            name,
            actualSprite,
            speed
        );
    }
}

bool Config::init(SDL_Renderer &renderer) {
    SDL_Texture *texture = Util::loadTexture("assets/coom.png", renderer);
    if (!texture) {
        return false;
    }
    atlas = new Atlas(*texture);
    atlas->loadSprites("assets/cooxr.csv");
    ::loadFreaks("assets/freaks.csv");
    ::loadBullets("assets/bullets.csv");
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
