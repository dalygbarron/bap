#include "Screen.hh"

#define STEP 33

DesignScreen::DesignScreen(Sack const &sack): Screen(sack) {

}

int DesignScreen::getTimestep() const {
    return STEP;
}

int DesignScreen::update() {
    return 0;
}

void DesignScreen::customRender(Renderer const &renderer) const {

}
