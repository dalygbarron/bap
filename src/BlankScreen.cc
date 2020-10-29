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
    JanetFiberStatus status = janet_fiber_status(this->script);
    if (status != JANET_STATUS_DEAD && status != JANET_STATUS_ERROR) {
        Janet out;
        janet_continue(this->script, janet_wrap_nil(), &out);
        status = janet_fiber_status(this->script);
        if (status != JANET_STATUS_ALIVE && status != JANET_STATUS_PENDING) {
            janet_stacktrace(this->script, out);
        }
        return;
    }
    printf("end\n");
    this->pop();
}
