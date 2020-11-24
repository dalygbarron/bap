#include "Shader.hh"
#include "Util.hh"

Shader::~Shader() {

}

GLuint Shader::getPositionLoc() const {
    return this->positionLoc;
}

GLuint Shader::getTextureCoordLoc() const {
    return this->textureCoordLoc;
}

GLuint Shader::getInvTextureSizeLoc() const {
    return this->invTextureSizeLoc;
}

GLuint Shader::getInvWindowSizeLoc() const {
    return this->invWindowSizeLoc;
}

GLuint Shader::getSamplerLoc() const {
    return this->samplerLoc;
}

void Shader::bind() {
    glUseProgram(this->program);
}

Shader *Shader::createShader(char const *vertexSrc, char const *fragmentSrc) {
    GLuint vertex = Util::createShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragment = Util::createShader(GL_FRAGMENT_SHADER, fragmentSrc);
    if (vertex == 0 || fragment == 0) return NULL;
    GLuint program = Util::createShaderProgram(vertex, fragment);
    if (program == 0) return NULL;
    return new Shader(program);
}

Shader *Shader::bindDefaultShader() {
    static Shader *def = NULL;
    if (def == NULL) {
        def = createShader(Shader::DEFAULT_VERTEX, Shader::DEFAULT_FRAGMENT);
    }
    def->bind();
    return def;
}

Shader::Shader(GLuint program) {
    this->program = program;
    this->positionLoc = glGetAttribLocation(program, "position");
    this->textureCoordLoc = glGetAttribLocation(program, "textureCoord");
    this->invTextureSizeLoc = glGetUniformLocation(program, "invTextureSize");
    this->invWindowSizeLoc = glGetUniformLocation(program, "invWindowSize");
    this->samplerLoc = glGetUniformLocation(program, "sampler");
    SDL_Rect screen = Util::getScreen();
    glUseProgram(program);
    glUniform4f(
        this->invWindowSizeLoc,
        1.0f / screen.w,
        1.0f / screen.h,
        1.0f,
        1.0f
    );
}
