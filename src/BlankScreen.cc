#include "Screen.hh"
#include "Util.hh"

#define STEP 33

BlankScreen::BlankScreen(char const *script, int argc, char const **argv) {
    this->script = this->loadFiber(script, argc, argv);
}

BlankScreen::~BlankScreen() {
    delete this->script;
}

int BlankScreen::getTimestep() const {
    return STEP;
}

void BlankScreen::customUpdate() {
    if (janet_fiber_status(this->script) != JANET_STATUS_DEAD) {
        Janet out;
        janet_continue(this->script, janet_wrap_nil(), &out);
        return;
    }
    this->pop();
}
