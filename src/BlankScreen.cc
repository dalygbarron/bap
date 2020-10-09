#include "Screen.hh"

#define STEP 17
#define SECOND_STEP 0.017

BlankScreen::BlankScreen(Sack const &sack, std::string script): Screen(sack) {
    this->script = sack.createScript(script);
}

int BlankScreen::getTimestep() const {
    return STEP;
}

int BlankScreen::update() {

    return 0;
}

void BlankScreen::render(SDL_Renderer &renderer) const {

}
