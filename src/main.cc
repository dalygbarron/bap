#include "Util.hh"
#include "Config.hh"
#include "Renderer.hh"
#include "Api.hh"
#include "janet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#include <stdio.h>
#include <vector>

int const INDEX_DELTA = 0;
int const INDEX_INPUT = 1;

const GLchar* vertexSource =
    "attribute vec4 position;    \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = position;\n"
    "}\n";
const GLchar* fragmentSource =
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor = vec4(gl_FragCoord.x / 600.0, gl_FragCoord.y / 600.0, 0.0, 1.0 );\n"
    "}\n";

SDL_Window *window;
SDL_GLContext context;
SDL_Renderer *renderer;
JanetKV in[2];

/**
 * Gotta do this shit for emscripten, annoying I know.
 */
class ProgramState {
    public:
        bool running;
        int time;
        int updateTimer;
        int fpsTimer;
        int startIteration;
        int iteration;
        JanetFiber *script;
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    window = SDL_CreateWindow(
        "BAP",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window) {
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    context = SDL_GL_CreateContext(window);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("ERror initialising opengl\n");
        return false;
    }
    SDL_GL_MakeCurrent(window, context);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image couldn't init because: %s", IMG_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer couldn't init because: %s", Mix_GetError());
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
	window,
	-1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        printf("Couldn't start renderer because: %s\n", SDL_GetError());
        return 1;
    }
    SDL_RenderSetLogicalSize(
        renderer,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT
    );
    GLuint defaultShader = Util::createShaderProgram(
        Util::createShader(GL_VERTEX_SHADER, vertexSource),
        Util::createShader(GL_FRAGMENT_SHADER, fragmentSource)
    );
    Config::init(renderer, defaultShader);
    janet_init();
    Api::init();
    in[INDEX_DELTA].key = janet_ckeywordv("delta");
    in[INDEX_INPUT].key = janet_ckeywordv("input");
    return true;
}

/**
 * The main loop of the program.
 * @param data is meant to be a program state object which contains all the
 *             variables the loop needs between iterations.
 */
void loop(void *data) {
    // glViewport(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    // SDL_GL_MakeCurrent(window, context);
    glClearColor(1.0f, 0.8f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(Config::defaultShader);
    struct ProgramState *program = (ProgramState *)data;
    std::vector<SDL_Keycode> keys;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            program->running = false;
            return;
        } else if (event.type == SDL_KEYDOWN) {
            keys.push_back(event.key.keysym.sym);
        }
    }
    int currentTime = SDL_GetTicks();
    program->fpsTimer += currentTime - program->time;
    program->time = currentTime;
    JanetFiberStatus status = janet_fiber_status(program->script);
    if (status != JANET_STATUS_DEAD && status != JANET_STATUS_ERROR) {
        Janet inputs[keys.size()];
        for (int i = 0; i < keys.size(); i++) {
            inputs[i] = janet_wrap_number(keys[i]);
        }
        Janet out;
        // TODO: calculate delta.
        in[INDEX_DELTA].value = janet_wrap_number(0.1);
        in[INDEX_INPUT].value = janet_wrap_tuple(
            janet_tuple_n(inputs, keys.size())
        );
        janet_continue(
            program->script,
            janet_wrap_struct(in),
            &out
        );
        status = janet_fiber_status(program->script);
        if (status != JANET_STATUS_ALIVE && status != JANET_STATUS_PENDING) {
            janet_stacktrace(program->script, out);
        }
    } else {
        program->running = false;
    }
    if (program->fpsTimer >= Config::FPS_RATE) {
        printf(
            "%.2f fps\n",
            (float)(program->iteration - program->startIteration) /
                (Config::FPS_RATE / 1000)
        );
        program->startIteration = program->iteration;
        program->fpsTimer = 0;
    }
    SDL_GL_SwapWindow(window);
    program->iteration++;
}

/**
 * The start of the program.
 * @param argc is the number of arguments.
 * @param argv is the list of arguments.
 * @return the return code of the program.
 */
int main(int argc, char **argv) {
    if (!init()) {
        return 1;
    }
    ProgramState *program = new ProgramState();
    program->script = Util::loadFiber("script/init.janet");
    program->running = true;
    program->time = SDL_GetTicks();
    program->updateTimer = 0;
    program->fpsTimer = 0;
    program->startIteration = 0;
    program->iteration = 0;
    while (program->running && program->script) {
        loop(program);
        #ifndef __EMSCRIPTEN__
        SDL_Delay(10);
        #endif
    }
    return 0;
}
