#include "Screen.hh"
#include "Util.hh"
#include <stdio.h>

Screen::Screen(Sack const &sack): sack(sack) {
    // that is all.
}

void Screen::render(Renderer const &renderer) {
    this->customRender(renderer);
    while (!this->drawQueue.empty()) {
        DrawOperation operation = this->drawQueue.front();
        this->drawQueue.pop();
        switch (operation.type) {
            case DrawOperation::BORDER:
                renderer.border(
                    operation.bounds,
                    operation.sprite,
                    operation.width
                );
                break;
            case DrawOperation::RECT:
                renderer.rect(operation.bounds, operation.sprite);
                break;
            case DrawOperation::PANEL:
                renderer.panel(operation.bounds);
                break;
            case DrawOperation::TEXT:
                renderer.text(
                    Vec(operation.bounds.x, operation.bounds.y),
                    operation.text
                );
                break;
        }
    }
}

void Screen::customRender(Renderer const &renderer) const {}

JanetFiber *Screen::loadFiber(char const *file) {
    Janet out;
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile(file).c_str(), "main", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
        return NULL;
    }
    Janet pointer = janet_wrap_pointer(this);
    return janet_fiber(janet_unwrap_function(out), 0, 1, &pointer);
}
