#include "View.hh"

View::View(SDL_Window &window, SDL_Texture &atlas):
    window(window),
    atlas(atlas)
{
    this->screenSurface = SDL_GetWindowSurface(&window);
}

