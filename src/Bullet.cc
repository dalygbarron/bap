#include "Bullet.hh"

Bullet::Bullet(std::string name, SDL_Rect sprite, float speed) {
    this->name = name;
    this->sprite = sprite;
    this->speed = speed;
}

std::string Bullet::getName() const {
    return this->name;
}

SDL_Rect Bullet::getSprite() const {
    return this->sprite;
}

float Bullet::getSpeed() const {
    return this->speed;
}

void Bullet::render(
    SDL_Renderer &renderer,
    Atlas const &atlas,
    Instance<Bullet> const &instance
) const {
    atlas.draw(
        renderer,
        instance.position.x,
        instance.position.y,
        this->sprite
    );
}
