#include "Api.hh"
#include "Config.hh"
#include "Renderer.hh"

Janet drawBorder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *sprite = janet_unwrap_tuple(argv[1]);
    float width = janet_unwrap_number(argv[2]);
    Renderer::border(
        {
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1])),
            static_cast<int>(janet_unwrap_number(border[2])),
            static_cast<int>(janet_unwrap_number(border[3]))
        },
        {
            static_cast<int>(janet_unwrap_number(sprite[0])),
            static_cast<int>(janet_unwrap_number(sprite[1])),
            static_cast<int>(janet_unwrap_number(sprite[2])),
            static_cast<int>(janet_unwrap_number(sprite[3]))
        },
        width
    );
    return janet_wrap_nil();
}

Janet drawRect(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *sprite = janet_unwrap_tuple(argv[1]);
    Renderer::rect(
        {
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1])),
            static_cast<int>(janet_unwrap_number(border[2])),
            static_cast<int>(janet_unwrap_number(border[3]))
        },
        {
            static_cast<int>(janet_unwrap_number(sprite[0])),
            static_cast<int>(janet_unwrap_number(sprite[1])),
            static_cast<int>(janet_unwrap_number(sprite[2])),
            static_cast<int>(janet_unwrap_number(sprite[3]))
        }
    );
    return janet_wrap_nil();
}

Janet drawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *font = janet_unwrap_tuple(argv[1]);
    Renderer::text(
        Vec(
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1]))
        ),
        (char *)janet_unwrap_string(argv[2]),
        {
            static_cast<int>(janet_unwrap_number(font[0])),
            static_cast<int>(janet_unwrap_number(font[1])),
            static_cast<int>(janet_unwrap_number(font[2])),
            static_cast<int>(janet_unwrap_number(font[3]))
        }
    );
    return janet_wrap_nil();
}

Janet drawSprite(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Janet const *border = janet_unwrap_tuple(argv[0]);
    Janet const *sprite = janet_unwrap_tuple(argv[1]);
    Renderer::sprite(
        {
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1])),
            static_cast<int>(janet_unwrap_number(border[2])),
            static_cast<int>(janet_unwrap_number(border[3]))
        },
        {
            static_cast<int>(janet_unwrap_number(sprite[0])),
            static_cast<int>(janet_unwrap_number(sprite[1])),
            static_cast<int>(janet_unwrap_number(sprite[2])),
            static_cast<int>(janet_unwrap_number(sprite[3]))
        }
    );
    return janet_wrap_nil();
}

Janet getSprite(int32_t argc, Janet *argv) {
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

Janet getScreenDimensions(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    Janet items[2];
    items[0] = janet_wrap_integer(Config::SCREEN_WIDTH);
    items[1] = janet_wrap_integer(Config::SCREEN_HEIGHT);
    return janet_wrap_tuple(janet_tuple_n(items, 2));
}

/**
 * Loads in the scripting functions yeet and sets up globals and stuff.
 */
void Api::init() {
    JanetReg const cFunctions[] = {
        {"draw-rect", drawRect, "(screen/draw-rect)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-border", drawBorder, "(screen/draw-border)\nDraws a border at the given place with the given sprite and width."},
        {"draw-text", drawText, "(screen/draw-text)\nDraws some text."},
        {"draw-sprite", drawSprite, "(screen/draw-text)\nDraws some text."},
        {"get-sprite", getSprite, "(screen/get-sprite)\nGives you the bounds of a sprite in a tuple like (x y w h)"},
        {"get-screen-dimensions", getScreenDimensions, "(screen/get-screen-dimensions)\nGives you the dimensions of the screen like (w h)"},
        {NULL, NULL, NULL}
    };
    JanetTable *env = janet_core_env(NULL);
    janet_cfuns(env, "screen", cFunctions);
}

