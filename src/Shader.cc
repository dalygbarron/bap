#include "Shader.hh"

void Shader::bind() {
    glUseProgram(this->program);
}

Shader *Shader::createShader(char const *vertexSrc, char const *fragmentSrc) {
    GLuint vertex = Util::createShader(GL_SHADER_VERTEX, vertexSrc);
    GLuint fragment = Util::createShader(GL_SHADER_FRAGMENT, fragmentSrc);
    if (vertex == 0 || fragment == 0) return NULL;
    GLuint program = Util::createShaderProgram(vertex, fragment);
    if (program == 0) return NULL;
    return Shader(program);
}

Shader *Shader::bindDefaultShader() {
    static Shader *def = createShader(
        Shader::defaultVertex,
        Shader::defaultFragment
    );
    def->bind();
}

Shader::Shader(GLuint program) {
    this->program = program;
    this->programLoc = glGetAttribLocation(program, "position");
    this->textureCoordLoc = glGetAttribLocation(program, "textureCoord");
    this->invTextureSizeLoc = glGetUniformLocation(program, "invTextureSize");
    this->invWindowSizeLoc = glGetUniformLocation(program, "invWindowSize");
    this->samplerLoc = glGetUniformLocation(program, "sampler");
    SDL_Rect screen = Util::getScreen();
    glUseProgram(program);
    glUniform4f(
        this->invWindowSizeLoc,
        1.0f / screen.width,
        1.0f / screen.height,
        1.0f,
        1.0f
    );
}
