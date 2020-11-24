#include "Api.hh"
#include "Config.hh"
#include "Renderer.hh"
#include "Util.hh"

Janet createBatch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Texture *texture = (Texture *)janet_getpointer(argv, 0);
    int32_t max = janet_getinteger(argv, 1);
    return janet_wrap_pointer(new Batch(texture, max));
}

Janet renderBatch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    batch->render();
    return janet_wrap_nil();
}

Janet freeBatch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    delete batch;
    return janet_wrap_nil();
}

Janet drawRectToBatch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 9);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    SDL_Rect dst = {
        janet_getinteger(argv, 1),
        janet_getinteger(argv, 2),
        janet_getinteger(argv, 3),
        janet_getinteger(argv, 4)
    };
    SDL_Rect src = {
        janet_getinteger(argv, 5),
        janet_getinteger(argv, 6),
        janet_getinteger(argv, 7),
        janet_getinteger(argv, 8)
    };
    batch->draw(dst, src);
    return janet_wrap_nil();
}

Janet clearBatch(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    batch->clear();
    return janet_wrap_nil();
}

Janet loadTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    char const *filename = (char *)janet_getcstring(argv, 0);
    Texture *texture = Texture::loadTexture(filename);
    if (texture == NULL) {
        janet_panicf("%s is not a valid filename", filename);
    }
    return janet_wrap_pointer(texture);
}

Janet freeTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Texture *texture = (Texture *)janet_getpointer(argv, 0);
    delete texture;
    return janet_wrap_nil();
}

Janet drawBorder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *sprite = janet_unwrap_tuple(argv[2]);
    float width = janet_unwrap_number(argv[3]);
    Renderer::border(
        batch,
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
    janet_fixarity(argc, 3);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *sprite = janet_unwrap_tuple(argv[2]);
    Renderer::rect(
        batch,
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
    janet_fixarity(argc, 4);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *font = janet_unwrap_tuple(argv[2]);
    Renderer::text(
        batch,
        Vec(
            static_cast<int>(janet_unwrap_number(border[0])),
            static_cast<int>(janet_unwrap_number(border[1]))
        ),
        (char *)janet_unwrap_string(argv[3]),
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
    janet_fixarity(argc, 3);
    Batch *batch = (Batch *)janet_getpointer(argv, 0);
    Janet const *border = janet_unwrap_tuple(argv[1]);
    Janet const *sprite = janet_unwrap_tuple(argv[2]);
    Renderer::sprite(
        batch,
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
        {"load-texture", loadTexture, "(api/load-batch)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"free-texture", freeTexture, "(api/render-batch)\nRenders a batch."},
        {"create-batch", createBatch, "(api/load-batch)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-rect-to-batch", drawRectToBatch, "(api/draw-rect-to-batch)\nRenders a batch."},
        {"clear-batch", clearBatch, "(api/clear-batch)\nRenders a batch."},
        {"render-batch", renderBatch, "(api/render-batch)\nRenders a batch."},
        {"free-batch", freeBatch, "(api/load-batch)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-rect", drawRect, "(screen/draw-rect)\nDraws a rectangle on the screen at the given place with the given pattern."},
        {"draw-border", drawBorder, "(screen/draw-border)\nDraws a border at the given place with the given sprite and width."},
        {"draw-text", drawText, "(screen/draw-text)\nDraws some text."},
        {"draw-sprite", drawSprite, "(screen/draw-text)\nDraws some text."},
        {"get-screen-dimensions", getScreenDimensions, "(screen/get-screen-dimensions)\nGives you the dimensions of the screen like (w h)"},
        {NULL, NULL, NULL}
    };
    JanetTable *env = janet_core_env(NULL);
    janet_cfuns(env, "api", cFunctions);
}

