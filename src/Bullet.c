#include "Bullet.hh"

Bullet::Bullet(std::string name, SDL_Rect sprite, float speed) {
    this->name = name;
    this->sprite = sprite;
    this->speed = speed;
}
