#include "Screen.hh"
#include "Util.hh"

#define STEP 17
#define SECOND_STEP 0.017

BlankScreen::BlankScreen(Sack const &sack, std::string script): Screen(sack) {
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile("assets/janet/talk.janet").c_str(), "main", NULL);
    JANET_API JanetFiber *fiber = janet_root_fiber();
    printf("%d\n", fiber);
    while (janet_fiber_status(fiber) != JANET_STATUS_DEAD) {
        janet_continue(fiber, janet_wrap_nil(), NULL);
        printf("nerd\n");
    }
}

int BlankScreen::getTimestep() const {
    return STEP;
}

int BlankScreen::update() {

    return 0;
}

void BlankScreen::render(SDL_Renderer &renderer) const {

}
