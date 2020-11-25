#include "Util.hh"
#include "Config.hh"
#include "gl.hh"
#include <iostream>
#include <fstream>
#include <vector>

GLuint Util::createShader(GLenum type, char const *src) {
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);
    if (shader == 0) return 0;
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            printf("Error compiling shader:\n%s\n%s\n", src, infoLog);
            delete[] infoLog;
        }
    }
    return shader;
}

GLuint Util::createShaderProgram(GLuint vertex, GLuint fragment) {
    GLint linked;
    GLuint program = glCreateProgram();
    if (program == 0) return 0;
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glBindAttribLocation(program, 0, "position");
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = new char[infoLen];
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            printf("Error compiling shader:\n%s\n", infoLog);
            delete[] infoLog;
        }
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

std::string Util::readWholeFile(char const *file) {
    FILE *f = fopen(file, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        char *string = (char *)malloc(fsize + 1);
        fread(string, 1, fsize, f);
        fclose(f);
        string[fsize] = 0;
        std::string output = string;
        delete string;
        return output;
    }
    fprintf(stderr, "Couldn't open file %s.\n", file);
    return NULL;
}

JanetFiber *Util::loadFiber(char const *path) {
    Janet out;
    JanetTable *env = janet_core_env(NULL);
    janet_dostring(env, Util::readWholeFile(path).c_str(), "screen", &out);
    if (!janet_checktype(out, JANET_FUNCTION)) {
        fprintf(stderr, "SCript needs a function retard\n");
        return NULL;
    }
    return janet_fiber(janet_unwrap_function(out), 0, 0, NULL);
}

float Util::min(float a, float b) {
    if (a < b) return a;
    return b;
}

int Util::min(int a, int b) {
    if (a < b) return a;
    return b;
}

int Util::max(int a, int b) {
    if (a > b) return a;
    return b;
}

bool Util::white(char c) {
    return c == ' ' || c == '\n';
}

SDL_Rect Util::getScreen() {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return {viewport[0], viewport[1], viewport[2], viewport[3]};
}

void Util::centre(int width, int height) {
    float ratio = Util::min(
        width / (float)Config::SCREEN_WIDTH,
        height / (float)Config::SCREEN_HEIGHT
    );
    int ratioWidth = (int)Config::SCREEN_WIDTH * ratio;
    int ratioHeight = (int)Config::SCREEN_HEIGHT * ratio;
    glViewport(width / 2 - ratioWidth / 2, height / 2 - ratioHeight / 2, ratioWidth, ratioHeight);
}
