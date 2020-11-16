#include "Renderer.hh"
#include "Util.hh"
#include "Config.hh"

SDL_Rect Renderer::border(
    Batch *batch,
    SDL_Rect bounds,
    SDL_Rect sprite,
    int width
) {
    if (bounds.w < width * 2 || bounds.h < width * 2) return {0, 0, 0, 0};
    // corners
    batch->draw(
        {bounds.x, bounds.y, width, width},
        {sprite.x, sprite.y, width, width}
    );
    batch->draw(
        {bounds.x + bounds.w - width, bounds.y, width, width},
        {sprite.x + sprite.w - width, sprite.y, width, width}
    );
    batch->draw(
        {bounds.x, bounds.y + bounds.h - width, width, width},
        {sprite.x, sprite.y + sprite.h - width, width, width}
    );
    batch->draw(
        {bounds.x + bounds.w - width, bounds.y + bounds.h - width, width, width},
        {sprite.x + sprite.w - width, sprite.y + sprite.h - width, width, width}
    );
    // edges
    batch->draw(
        {bounds.x + width, bounds.y, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y, sprite.w - width * 2, width}
    );
    batch->draw(
        {bounds.x, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x, sprite.y + width, width, sprite.h - width * 2}
    );
    batch->draw(
        {bounds.x + width, bounds.y + bounds.h - width, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y + sprite.h - width, sprite.w - width * 2, width}
    );
    batch->draw(
        {bounds.x + bounds.w - width, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x + sprite.w - width, sprite.y + width, width, sprite.h - width * 2}
    );
    return {
        bounds.x + width,
        bounds.y + width,
        bounds.w - width * 2,
        bounds.h - width * 2
    };
}

void Renderer::rect(Batch *batch, SDL_Rect bounds, SDL_Rect sprite) {
    if (bounds.w == 0 || bounds.h == 0 || sprite.w == 0 || sprite.h == 0) {
        return;
    }
    int hSegments = bounds.w / sprite.w;
    int vSegments = bounds.h / sprite.h;
    for (int y = 0; y < vSegments; y++) {
        for (int x = 0; x < hSegments; x++) {
            batch->draw({
                    bounds.x + sprite.w * x,
                    bounds.y + sprite.h * y,
                    sprite.w,
                    sprite.h
                },
                sprite
            );
        }
        if (hSegments * sprite.w < bounds.w) {
            int delta = bounds.w - (hSegments * sprite.w);
            batch->draw({
                    bounds.x + sprite.w * hSegments,
                    bounds.y + sprite.h * y,
                    delta,
                    sprite.h
                },
                {sprite.x, sprite.y, delta, sprite.h}
            );
        }
    }
    if (vSegments * sprite.h < bounds.h) {
        int vDelta = bounds.h - (vSegments * sprite.h);
        for (int x = 0; x < hSegments; x++) {
            batch->draw({
                    bounds.x + sprite.w * x,
                    bounds.y + sprite.h * vSegments,
                    sprite.w,
                    vDelta
                },
                {sprite.x, sprite.y, sprite.w, vDelta}
            );
        }
        if (hSegments * sprite.w < bounds.w) {
            int delta = bounds.w - (hSegments * sprite.w);
            batch->draw({
                    bounds.x + sprite.w * hSegments,
                    bounds.y + sprite.h * vSegments,
                    delta,
                    vDelta
                },
                {sprite.x, sprite.y, delta, vDelta}
            );
        }
    }
}

void Renderer::text(
    Batch *batch,
    Vec origin,
    char const *text,
    SDL_Rect font
) {
    float originX = origin.x;
    Vec character(font.w / 16, font.h / 16);
    for (int i = 0; text[i]; i++) {
        char c = text[i];
        if (c == '\n') {
            origin.x = originX;
            origin.y += character.y;
            continue;
        }
        batch->draw({
                origin.iX(),
                origin.iY(),
                character.iX(),
                character.iY()
            },
            {
                font.x + character.iX() * (c % 16),
                font.y + character.iY() * (c / 16),
                character.iX(),
                character.iY()
            }
        );
        origin.x += character.iX();
    }
}

void Renderer::sprite(
    Batch *batch,
    SDL_Rect const &bounds,
    SDL_Rect const &sprite
) {
    batch->draw(bounds, sprite);
}

