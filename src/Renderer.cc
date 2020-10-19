#include "Renderer.hh"
#include "Util.hh"

Renderer::Renderer(
    SDL_Renderer &renderer,
    Atlas const &atlas,
    SDL_Rect guiBackground,
    SDL_Rect guiSelect,
    SDL_Rect font,
    int guiBorderSize
):
    renderer(renderer),
    atlas(atlas)
{
    this->guiBackground = guiBackground;
    this->guiSelect = guiSelect;
    this->font = font;
    this->guiBorderSize = guiBorderSize;
}

SDL_Rect Renderer::panel(SDL_Rect bounds) const {
    this->atlas.draw(
        this->renderer,
        bounds,
        this->guiBackground
    );
    return {
        Util::min(
            bounds.x + this->guiBorderSize,
            floor(bounds.x + bounds.w / 2)
        ),
        Util::min(
            bounds.y + this->guiBorderSize,
            floor(bounds.y + bounds.h / 2)
        ),
        Util::max(bounds.w - this->guiBorderSize * 2, 0),
        Util::max(bounds.h - this->guiBorderSize * 2, 0)
    };
}
