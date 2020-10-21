#include "Screen.hh"
#include "Util.hh"
#include <stdio.h>

Screen::Screen(Sack const &sack): sack(sack) {
    // that is all.
}

int Screen::update() {
    this->drawQueue.clear();
    return this->customUpdate();
}

void Screen::render(Renderer const &renderer) {
    this->customRender(renderer);
    for (DrawOperation operation: this->drawQueue) {
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

int Screen::customUpdate() {
    return 0;
}

void Screen::customRender(Renderer const &renderer) const {}

JanetFiber *Screen::loadFiber(char const *file) {
    Janet out;
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile(file).c_str(), "screen", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
        return NULL;
    }
    Janet pointer = janet_wrap_pointer(this);
    return janet_fiber(janet_unwrap_function(out), 0, 1, &pointer);
}

Janet Screen::drawBorder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *sprite = janet_unwrap_tuple(argv[2]);
    float width = janet_unwrap_number(argv[3]);
    DrawOperation operation;
    operation.type = DrawOperation::BORDER;
    operation.sprite = {
        static_cast<int>(janet_unwrap_number(sprite[0])),
        static_cast<int>(janet_unwrap_number(sprite[1])),
        static_cast<int>(janet_unwrap_number(sprite[2])),
        static_cast<int>(janet_unwrap_number(sprite[3]))
    };
    operation.bounds = {
        static_cast<int>(janet_unwrap_number(border[0])),
        static_cast<int>(janet_unwrap_number(border[1])),
        static_cast<int>(janet_unwrap_number(border[2])),
        static_cast<int>(janet_unwrap_number(border[3]))
    };
    operation.width = width;
    ((Screen *)screenPointer)->drawQueue.push_back(operation);
    return janet_wrap_nil();
}

void Screen::initScripting() {
    JanetReg const cFunctions[] = {
        {"drawBorder", drawBorder, "(screen/drawBorder)\n\nDraws a border at the given place."},
        {NULL, NULL, NULL}
    };
    JanetTable *env = janet_core_env(NULL);
    janet_cfuns(env, "screen", cFunctions);
}
