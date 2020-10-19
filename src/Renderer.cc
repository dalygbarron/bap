#include "Renderer.hh"
#include "Util.hh"

Renderer::Renderer(
    SDL_Renderer &renderer,
    Atlas const &atlas,
    SDL_Rect background,
    SDL_Rect panelBorder,
    SDL_Rect select,
    SDL_Rect font,
    int borderSize
):
    renderer(renderer),
    atlas(atlas)
{
    this->background = background;
    this->panelBorder = panelBorder;
    this->select = select;
    this->font = font;
    this->borderSize = borderSize;
}

SDL_Rect Renderer::border(SDL_Rect bounds, SDL_Rect sprite, int width) const {
    if (bounds.w < width * 2 || bounds.h < width * 2) return {0, 0, 0, 0};
    // corners
    this->atlas.draw(
        this->renderer,
        {bounds.x, bounds.y, width, width},
        {sprite.x, sprite.y, width, width}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x + bounds.w - width, bounds.y, width, width},
        {sprite.x + sprite.w - width, sprite.y, width, width}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x, bounds.y + bounds.h - width, width, width},
        {sprite.x, sprite.y + sprite.h - width, width, width}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x + bounds.w - width, bounds.y + bounds.h - width, width, width},
        {sprite.x + sprite.w - width, sprite.y + sprite.h - width, width, width}
    );
    // edges
    this->atlas.draw(
        this->renderer,
        {bounds.x + width, bounds.y, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y, sprite.w - width * 2, width}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x, sprite.y + width, width, sprite.h - width * 2}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x + width, bounds.y + bounds.h - width, bounds.w - width * 2, width},
        {sprite.x + width, sprite.y + sprite.h - width, sprite.w - width * 2, width}
    );
    this->atlas.draw(
        this->renderer,
        {bounds.x + bounds.h - width, bounds.y + width, width, bounds.h - width * 2},
        {sprite.x + sprite.h - width, sprite.y + width, width, sprite.h - width * 2}
    );
}

void Renderer::rect(SDL_Rect bounds, SDL_Rect sprite) const {
    int hSegments = bounds.w / sprite.w;
    int vSegments = bounds.h / sprite.h;
    for (int y = 0; y < vSegments; y++) {
        for (int x = 0; x < hSegments; x++) {
            this->atlas.draw(
                this->renderer,
                {bounds.x + sprite.w * x, bounds.y + sprite.h * y, sprite.w, sprite.h},
                sprite
            );
        }
    }
}

SDL_Rect Renderer::panel(SDL_Rect bounds) const {
    int fullBorderSize = this->borderSize * 2;
    if (bounds.w < fullBorderSize || bounds.h < fullBorderSize) {
        return {0, 0, 0, 0};
    }
    SDL_Rect inner = this->border(bounds, this->panelBorder, this->borderSize);
    if (inner.w || inner.h) this->rect(inner, this->background);
    return inner;
}
