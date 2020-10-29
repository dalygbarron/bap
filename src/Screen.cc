#include "Screen.hh"
#include "Util.hh"
#include "Config.hh"
#include <stdio.h>

Screen::~Screen() {
    this->transfer.type = TransferOperation::NONE;
}

void Screen::push(Screen *screen) {
    this->transfer.type = TransferOperation::PUSH;
    this->transfer.next = screen;
}

void Screen::pop() {
    this->transfer.type = TransferOperation::POP;
}

void Screen::replace(Screen *screen) {
    this->transfer.type = TransferOperation::REPLACE;
    this->transfer.next = screen;
}

Screen::TransferOperation Screen::update() {
    this->drawQueue.clear();
    this->customUpdate();
    TransferOperation currentTransfer = this->transfer;
    this->transfer.type = TransferOperation::NONE;
    return currentTransfer;
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
            case DrawOperation::TEXT:
                renderer.text(
                    Vec(operation.bounds.x, operation.bounds.y),
                    operation.text,
                    operation.sprite
                );
                break;
        }
    }
}

void Screen::customUpdate() {}

void Screen::customRender(Renderer const &renderer) const {}

JanetFiber *Screen::loadFiber(char const *file, int argc, char const **argv) {
    Janet out;
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile(file).c_str(), "screen", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
        return NULL;
    }
    Janet args[argc + 2];
    args[0] = janet_wrap_pointer(this);
    for (int i = 1; i <= argc; i++) {
        args[i] = janet_wrap_string(janet_cstring(argv[i - 1]));
    }
    return janet_fiber(janet_unwrap_function(out), 0, argc + 1, args);
}

Janet Screen::pushTrans(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    void *newScreenPointer = janet_unwrap_pointer(argv[1]);
    ((Screen *)screenPointer)->push((Screen *)newScreenPointer);
    return janet_wrap_nil();
}

Janet Screen::popTrans(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    ((Screen *)screenPointer)->pop();
    return janet_wrap_nil();
}

Janet Screen::replaceTrans(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    void *newScreenPointer = janet_unwrap_pointer(argv[1]);
    ((Screen *)screenPointer)->replace((Screen *)newScreenPointer);
    return janet_wrap_nil();
}

Janet Screen::newBlank(int32_t argc, Janet *argv) {
    janet_arity(argc, 3, -1);
    Screen *screen = (Screen *)janet_getpointer(argv, 0);
    char const *scriptName = (char *)janet_getcstring(argv, 1);
    char const *strings[argc - 2];
    for (int i = 2; i < argc; i++) {
        strings[i - 2] = (char const *)janet_getcstring(argv, i);
    }
    BlankScreen *newScreen = new BlankScreen(
        scriptName,
        argc - 2,
        strings
    );
    return janet_wrap_pointer(newScreen);
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

Janet Screen::drawRect(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *sprite = janet_unwrap_tuple(argv[2]);
    DrawOperation operation;
    operation.type = DrawOperation::RECT;
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
    ((Screen *)screenPointer)->drawQueue.push_back(operation);
    return janet_wrap_nil();
}

Janet Screen::drawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    DrawOperation operation;
    void *screenPointer = janet_unwrap_pointer(argv[0]);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *font = janet_unwrap_tuple(argv[2]);
    operation.text = (char *)janet_unwrap_string(argv[3]);
    operation.type = DrawOperation::TEXT;
    operation.sprite = {
        static_cast<int>(janet_unwrap_number(font[0])),
        static_cast<int>(janet_unwrap_number(font[1])),
        static_cast<int>(janet_unwrap_number(font[2])),
        static_cast<int>(janet_unwrap_number(font[3]))
    };
    operation.bounds = {
        static_cast<int>(janet_unwrap_number(border[0])),
        static_cast<int>(janet_unwrap_number(border[1]))
    };
    ((Screen *)screenPointer)->drawQueue.push_back(operation);
    return janet_wrap_nil();
}

Janet Screen::getSprite(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char const *name = (char const *)janet_getcstring(argv, 0);
    SDL_Rect sprite = Config::getAtlas()->getSprite(name);
    Janet list[4];
    list[0] = janet_wrap_integer(sprite.x);
    list[1] = janet_wrap_integer(sprite.y);
    list[2] = janet_wrap_integer(sprite.w);
    list[3] = janet_wrap_integer(sprite.h);
    return janet_wrap_tuple(janet_tuple_n(list, 4));
}

Janet Screen::getScreenDimensions(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    Janet items[2];
    items[0] = janet_wrap_integer(Config::SCREEN_WIDTH);
    items[1] = janet_wrap_integer(Config::SCREEN_HEIGHT);
    return janet_wrap_tuple(janet_tuple_n(items, 2));
}

void Screen::initScripting() {
    JanetReg const cFunctions[] = {
        {"new-blank", newBlank, "(screen/new-blank)\nCreates a new Blank Screen."},
        {"push-trans", pushTrans, "(screen/push-trans)\nPuts a new screen on top of this one."},
        {"pop-trans", popTrans, "(screen/pop-trans)\nRemoves the current screen from the screen stack."},
        {"replace-trans", replaceTrans, "(screen/replace-trans)\nReplace the current screen with a new one"},
        {"draw-rect", drawRect, "(screen/draw-rect)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-border", drawBorder, "(screen/draw-border)\nDraws a border at the given place with the given sprite and width."},
        {"draw-text", drawText, "(screen/draw-text)\nDraws some text."},
        {"get-sprite", getSprite, "(screen/get-sprite)\nGives you the bounds of a sprite in a tuple like (x y w h)"},
        {"get-screen-dimensions", getScreenDimensions, "(screen/get-screen-dimensions)\nGives you the dimensions of the screen like (w h)"},
        {NULL, NULL, NULL}
    };
    JanetTable *env = janet_core_env(NULL);
    janet_cfuns(env, "screen", cFunctions);
}
