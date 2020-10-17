#include "Screen.hh"

#define STEP 33

DesignScreen::DesignScreen(Sack const &sack): Screen(sack) {

}

int DesignScreen::getTimestep() const {
    return STEP;
}

int DesignScreen::update() {

}

void DesignScreen::render(SDL_Renderer &renderer) const {

}
