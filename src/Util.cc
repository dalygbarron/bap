#include "Util.hh"
#include <iostream>
#include <fstream>
#include <vector>

SDL_Texture *Util::loadTexture(char const *file, SDL_Renderer &renderer) {
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(file);
    if (loadedSurface == NULL) {
	fprintf(
            stderr,
	    "Loading image '%s' failed because: %s\n",
	    file,
	    IMG_GetError()
	);
	return NULL;
    }
    newTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
    if (newTexture == NULL) {
	fprintf(stderr, "Creating texture failed because: %s\n", SDL_GetError());
	return NULL;
    }
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

std::string Util::readWholeFile(char const *file) {
    FILE *f = fopen(file, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        char *string = (char *)malloc(fsize + 1);
        fread(string, 1, fsize, f);
        fclose(f);
        string[fsize] = 0;
        std::string output = string;
        delete string;
        return output;
    }
    fprintf(stderr, "Couldn't open file %s.\n", file);
    return NULL;
}

JanetFiber *Util::loadFiber(char const *path) {
    Janet out;
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile(path).c_str(), "screen", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
        return NULL;
    }
    return janet_fiber(janet_unwrap_function(out), 0, 0, NULL);
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
