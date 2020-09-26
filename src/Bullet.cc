#include "Bullet.hh"

Bullet::Bullet(std::string name, SDL_Rect sprite, float speed) {
    this->name = name;
    this->sprite = sprite;
    this->speed = speed;
}

void Bullet::update(float delta, Instance<Bullet> *instance) {
    Vec velocityPresent = instance->velocity;
    Vec acceleratorPresent = instance->accelerator;
    velocityPresent.mult(delta);
    acceleratorPresent.mult(delta);
    instance->position.add(velocityPresent);
    instance->velocity.add(acceleratorPresent);
}

void Bullet::render(
    SDL_Renderer &renderer,
    Atlas const &atlas,
    Instance<Bullet> *instance
) {
    atlas.draw(
        renderer,
        instance->position.x,
        instance->position.y,
        &this->sprite
    );
}
