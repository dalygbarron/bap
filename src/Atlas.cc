#include "Atlas.hh"
#include "csv.h"

Atlas::Atlas(SDL_Texture &texture): texture(texture) {
    SDL_QueryTexture(&texture, NULL, NULL, &this->width, &this->height);
}

void Atlas::loadSprites(char const *file) {
    io::CSVReader<5> csv(file);
    csv.read_header(io::ignore_extra_column, "name", "x", "y", "w", "h");
    std::string name;
    int x, y, w, h;
    while (csv.read_row(name, x, y, w, h)) {
        this->addSprite(name.c_str(), {x, y, w, h});
    }
}

void Atlas::addSprite(char const *name, SDL_Rect sprite) {
    this->sprites[name] = sprite;
}

SDL_Rect Atlas::getSprite(char const *name) const {
    if (this->sprites.count(name) > 0) return this->sprites.at(name);
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        "atlas doesn't have sprite '%s'\n",
        name
    );
    return {0, 0, 0, 0};
}

int Atlas::getWidth() const {
    return this->width;
}

int Atlas::getHeight() const {
    return this->height;
}

void Atlas::draw(
    SDL_Renderer *renderer,
    int x,
    int y,
    SDL_Rect const &sprite
) const {
    SDL_Rect placement = {
        x - sprite.w / 2,
        y - sprite.h / 2,
        sprite.w,
        sprite.h
    };
    SDL_RenderCopy(
        renderer,
        &this->texture,
        &sprite,
        &placement
    );
}

void Atlas::draw(
    SDL_Renderer *renderer,
    SDL_Rect const &destination,
    SDL_Rect const &sprite
) const {
    SDL_RenderCopy(
        renderer,
        &this->texture,
        &sprite,
        &destination
    );
}
