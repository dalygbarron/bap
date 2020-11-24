#include "Texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::~Texture() {
    glDeleteTextures(1, &this->glTexture);
}

Texture *Texture::loadTexture(char const *file) {
    GLuint texture = 0;
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
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int format;
    SDL_Surface *formattedSurface;
    if (loadedSurface->format->BytesPerPixel == 3) {
        formattedSurface = SDL_ConvertSurfaceFormat(
            loadedSurface,
            SDL_PIXELFORMAT_RGB24,
            0
        );
        format = GL_RGB;
    } else {
        formattedSurface = SDL_ConvertSurfaceFormat(
            loadedSurface,
            SDL_PIXELFORMAT_ARGB32,
            0
        );
        format = GL_RGBA;
    }
    unsigned int width = formattedSurface->w;
    unsigned int height = formattedSurface->h;
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        formattedSurface->pixels
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(formattedSurface);
    SDL_FreeSurface(loadedSurface);
    return new Texture(texture, width, height);
}

Texture::Texture(GLuint glTexture, unsigned int width, unsigned int height):
    glTexture(glTexture),
    width(width),
    height(height)
{}
