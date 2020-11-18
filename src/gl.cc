#include "gl.hh"

#if __APPLE__
void glGenVertexArraysOES(GLsizei n, GLuint *ids) {
    glGenVertexArraysAPPLE(n, ids);
}

void glBindVertexArrayOES(GLuint id) {
    glBindVertexArrayAPPLE(id);
}
#endif
