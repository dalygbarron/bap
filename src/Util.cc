#include "Util.hh"
#include <iostream>
#include <fstream>
#include <vector>

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

std::string Util::readWholeFile(char const *file) {
    std::ifstream ifs(file, std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);
    return std::string(bytes.data(), fileSize);
}

int Util::min(int a, int b) {
    if (a < b) return a;
    return b;
}

int Util::max(int a, int b) {
    if (a > b) return a;
    return b;
}

bool Util::white(char c) {
    return c == ' ' || c == '\n';
}
