#include "Atlas.hh"

Atlas::Atlas(SDL_Texture &texture): texture(texture) {
    SDL_QueryTexture(&texture, NULL, NULL, &this->width, &this->height);
}

void Atlas::addSprite(char const *name, SDL_Rect sprite) {
    this->sprites[name] = sprite;
}

SDL_Rect Atlas::getSprite(char const *name) const {
    if (this->sprites.count(name) > 0) return this->sprites.at(name);
    return {0, 0, 0, 0};
}

int Atlas::getWidth() const {
    return this->width;
}

int Atlas::getHeight() const {
    return this->height;
}

void Atlas::draw(
    SDL_Renderer &renderer,
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
        &renderer,
        &this->texture,
        &sprite,
        &placement
    );
}
