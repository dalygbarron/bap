#include "Util.hh"
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

GLuint Util::loadTexture(char const *file) {
    GLuint texture = 0;
    SDL_Surface *loadedSurface = IMG_Load(file);
    if (loadedSurface == NULL) {
	fprintf(
            stderr,
	    "Loading image '%s' failed because: %s\n",
	    file,
	    IMG_GetError()
	);
	return NULL;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    this is the file I was ripping off lets get back to that tomorrow
    https://gist.github.com/mortennobel/0e9e90c9bbc61cc99d5c3e9c038d8115
    SDL_FreeSurface(loadedSurface);
    return newTexture;
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
