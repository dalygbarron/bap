#include "Screen.hh"

#define STEP 17
#define SECOND_STEP 0.017

BlankScreen::BlankScreen(std::string script): Screen(sack) {
    this->script = this->loadScript(script);
}

int BlankScreen::getTimestep() const {
    return STEP;
}

int BlankScreen::update() {

}

void BlankScreen::render(SDL_Renderer &renderer) const {

}
