#include "Sack.hh"
#include "csv.h"

Sack::Sack(Atlas *atlas, int width, int height):
    atlas(atlas),
    width(width),
    height(height)
{
    // that is all.
}

void Sack::loadFreaks(char const *file) {
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
        SDL_Rect actualSprite = this->atlas->getSprite(sprite.c_str());
        Freak::Behaviour actualBehaviour = Freak::stringToBehaviour(
            behaviour
        );
        this->freaks.emplace(
            this->freaks.begin(),
            name,
            actualSprite,
            gravity,
            actualBehaviour
        );
    }
}

void Sack::loadBullets(char const *file) {
    io::CSVReader<3> csv(file);
    csv.read_header(io::ignore_extra_column, "name", "sprite", "speed");
    std::string name;
    std::string sprite;
    float speed;
    while (csv.read_row(name, sprite, speed)) {
        SDL_Rect actualSprite = this->atlas->getSprite(sprite.c_str());
        this->bullets.emplace(
            this->bullets.begin(),
            name,
            actualSprite,
            speed
        );
    }
}

void Sack::playSong(char const *file) const {
    if (!this->music || strcmp(this->song.c_str(), file) != 0) {
        if (this->music) Mix_FreeMusic(this->music);
        this->music = Mix_LoadMUS(file);
        if (this->music) {
            Mix_PlayMusic(this->music, -1);
            this->song = file;
        } else {
            SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Couldn't load music '%s'",
                file
            );
        }
    }
}

/*
WrenVM *Sack::createScript(std::string path) const {
    WrenVM* vm = wrenNewVM(&this->scriptConfig);
    WrenInterpretResult result = wrenInterpret(
        vm,
        "nerd",
        "System.print(\"I am running in a VM!\")\nFiber.yield()\nSystem.print(\"herd\")"
    );

    switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
            printf("Compile Error!\n");
            break;
        case WREN_RESULT_RUNTIME_ERROR:
            printf("Runtime Error!\n");
            break;
        case WREN_RESULT_SUCCESS:
            return vm;
    }
    wrenFreeVM(vm);
    return NULL;
}
*/
