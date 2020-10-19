#include "Renderer.hh"
#include "Util.hh"

Renderer::Renderer(
    SDL_Renderer &renderer,
    Atlas const &atlas,
    SDL_Rect background,
    SDL_Rect select,
    SDL_Rect font,
    int borderSize
):
    renderer(renderer),
    atlas(atlas)
{
    this->background = background;
    this->select = select;
    this->font = font;
    this->borderSize = borderSize;
}

SDL_Rect Renderer::panel(SDL_Rect bounds) const {
    int fullBorderSize = this->borderSize * 2;
    int midSize = this->background.w - fullBorderSize;
    if (bounds.w < fullBorderSize || bounds.h < fullBorderSize) {
        return {0, 0, 0, 0};
    }
    // draw the edges
    SDL_Rect src = {this->background.x, this->background.y, this->borderSize + midSize, this->borderSize + midSize};
    SDL_Rect dst = {bounds.x, bounds.y, this->borderSize + midSize, this->borderSize + midSize};
    this->atlas.draw(this->renderer, src, dst);
    
    // draw the edges
    // draw the middle

    return {
        Util::min(
            bounds.x + this->borderSize,
            floor(bounds.x + bounds.w / 2)
        ),
        Util::min(
            bounds.y + this->borderSize,
            floor(bounds.y + bounds.h / 2)
        ),
        Util::max(bounds.w - this->borderSize * 2, 0),
        Util::max(bounds.h - this->borderSize * 2, 0)
    };
}
