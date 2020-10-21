#include "Screen.hh"
#include "Util.hh"

#define STEP 33

BlankScreen::BlankScreen(Sack const &sack, std::string script): Screen(sack) {
    this->script = this->loadFiber(script.c_str());
}

int BlankScreen::getTimestep() const {
    return STEP;
}

int BlankScreen::customUpdate() {
    if (janet_fiber_status(this->script) != JANET_STATUS_DEAD) {
        Janet out;
        janet_continue(this->script, janet_wrap_nil(), &out);
        return 0;
    }
    return 1;
}
