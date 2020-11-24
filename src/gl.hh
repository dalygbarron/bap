#ifndef GL_H
#define GL_H

#ifdef __EMSCRIPTEN__
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#endif

#if __APPLE__
#include <opengl/gl.h>
#include <opengl/glu.h>
void glGenVertexArraysOES(GLsizei n, GLuint *ids);
void glBindVertexArrayOES(GLuint id);
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#endif
