#include "Renderer.hh"
#include "Util.hh"
#include "Config.hh"

Renderer::Renderer(SDL_Renderer &renderer): renderer(renderer) {}

SDL_Rect Renderer::border(SDL_Rect bounds, SDL_Rect sprite, int width) const {
    if (bounds.w < width * 2 || bounds.h < width * 2) return {0, 0, 0, 0};
    // corners
    Config::atlas->draw(
        this->renderer,
        {bounds.x, bounds.y, width, width},
        {sprite.x, sprite.y, width, width}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x + bounds.w - width, bounds.y, width, width},
        {sprite.x + sprite.w - width, sprite.y, width, width}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x, bounds.y + bounds.h - width, width, width},
        {sprite.x, sprite.y + sprite.h - width, width, width}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x + bounds.w - width, bounds.y + bounds.h - width, width, width},
        {sprite.x + sprite.w - width, sprite.y + sprite.h - width, width, width}
    );
    // edges
    Config::atlas->draw(
        this->renderer,
        {bounds.x + width, bounds.y, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y, sprite.w - width * 2, width}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x, sprite.y + width, width, sprite.h - width * 2}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x + width, bounds.y + bounds.h - width, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y + sprite.h - width, sprite.w - width * 2, width}
    );
    Config::atlas->draw(
        this->renderer,
        {bounds.x + bounds.w - width, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x + sprite.w - width, sprite.y + width, width, sprite.h - width * 2}
    );
    return {bounds.x + width, bounds.y + width, bounds.w - width * 2, bounds.h - width * 2};
}

void Renderer::rect(SDL_Rect bounds, SDL_Rect sprite) const {
    if (bounds.w == 0 || bounds.h == 0 || sprite.w == 0 || sprite.h == 0) {
        return;
    }
    int hSegments = bounds.w / sprite.w;
    int vSegments = bounds.h / sprite.h;
    for (int y = 0; y < vSegments; y++) {
        for (int x = 0; x < hSegments; x++) {
            Config::atlas->draw(
                this->renderer,
                {bounds.x + sprite.w * x, bounds.y + sprite.h * y, sprite.w, sprite.h},
                sprite
            );
        }
        if (hSegments * sprite.w < bounds.w) {
            int delta = bounds.w - (hSegments * sprite.w);
            Config::atlas->draw(
                this->renderer,
                {bounds.x + sprite.w * hSegments, bounds.y + sprite.h * y, delta, sprite.h},
                {sprite.x, sprite.y, delta, sprite.h}
            );
        }
    }
    if (vSegments * sprite.h < bounds.h) {
        int vDelta = bounds.h - (vSegments * sprite.h);
        for (int x = 0; x < hSegments; x++) {
            Config::atlas->draw(
                this->renderer,
                {bounds.x + sprite.w * x, bounds.y + sprite.h * vSegments, sprite.w, vDelta},
                {sprite.x, sprite.y, sprite.w, vDelta}
            );
        }
        if (hSegments * sprite.w < bounds.w) {
            int delta = bounds.w - (hSegments * sprite.w);
            Config::atlas->draw(
                this->renderer,
                {bounds.x + sprite.w * hSegments, bounds.y + sprite.h * vSegments, delta, vDelta},
                {sprite.x, sprite.y, delta, vDelta}
            );
        }
    }
}

void Renderer::text(Vec origin, char const *text, SDL_Rect font) const {
    float originX = origin.x;
    Vec character(font.w / 16, font.h / 16);
    for (int i = 0; text[i]; i++) {
        char c = text[i];
        if (c == '\n') {
            origin.x = originX;
            origin.y += character.y;
            continue;
        }
        Config::atlas->draw(
            this->renderer,
            {origin.iX(), origin.iY(), character.iX(), character.iY()},
            {font.x + character.iX() * (c % 16), font.y + character.iY() * (c / 16), character.iX(), character.iY()}
        );
        origin.x += character.iX();
    }
}

void Renderer::sprite(Vec pos, SDL_Rect const &sprite) const {
    Config::atlas->draw(
        this->renderer,
        {pos.iX() - sprite.w / 2, pos.iY() - sprite.h / 2, sprite.w, sprite.h},
        sprite
    );
}
