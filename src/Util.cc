#include "Util.hh"

SDL_Texture *Util::loadTexture(char const *file, SDL_Renderer &renderer) {
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(file);
    if (loadedSurface == NULL) {
	printf(
	    "Loading image '%s' failed because: %s\n",
	    file,
	    IMG_GetError()
	);
	return NULL;
    }
    newTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
    if (newTexture == NULL) {
	printf("Creating texture failed because: %s\n", SDL_GetError());
	return NULL;
    }
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
