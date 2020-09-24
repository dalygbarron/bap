#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

class Bullet {
    public:
	SDL_Rect sprite;
	float x;
	float y;
	float vX;
	float vY;
	float gX;
	float gY;
	bool alive;
};

#endif
