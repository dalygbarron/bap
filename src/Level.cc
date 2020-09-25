#include "Level.hh"

Level::Level(int width, int height, SDL_Rect bounds):
    width(width),
    height(height),
    bounds(bounds)
{
    int n = width * height;
    this->back = new uint8_t[n];
    this->mid = new uint8_t[n];
    this->front = new uint8_t[n];
}

Level::~Level() {
    delete this->back;
    delete this->mid;
    delete this->front;
}

void Level::render(Graphics &graphics) {

}
