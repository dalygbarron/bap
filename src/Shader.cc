#include "Shader.hh"

Shader::Shader(char const *vertexSrc, char const *fragmentSrc) {
    GLuint vertex = Util::createShader(GL_SHADER_VERTEX, vertexSrc);
    GLuint fragment = Util::createShader(GL_SHADER_FRAGMENT, fragmentSrc);

}
