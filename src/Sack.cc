#include "Sack.hh"
#define CSV_IO_NO_THREAD
#include "csv.h"

Sack::Sack(Atlas *atlas): atlas(atlas) {
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
    std::string name;
    std::string sprite;
    std::string behaviour;
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
