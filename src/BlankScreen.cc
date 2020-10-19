#include "Screen.hh"
#include "Util.hh"

#define STEP 33

BlankScreen::BlankScreen(Sack const &sack, std::string script): Screen(sack) {
    JanetTable *env = janet_core_env(NULL);
    Janet out;
    janet_dostring(env, Util::readWholeFile("assets/janet/talk.janet").c_str(), "main", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
    }
    JanetFiber *fiber = janet_fiber(janet_unwrap_function(out), 0, 0, NULL);
    while (janet_fiber_status(fiber) != JANET_STATUS_DEAD) {
        janet_continue(fiber, janet_wrap_nil(), NULL);
    }
}

int BlankScreen::getTimestep() const {
    return STEP;
}

int BlankScreen::update() {
    return 0;
}

void BlankScreen::render(Renderer const &renderer) const {
    SDL_Rect bounds = {30, 50, 500, 431};
    for (int i = 0; i < 10; i++) {
        bounds = renderer.panel(bounds);
    }
}
