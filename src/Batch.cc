#include "Batch.hh"
#include "Config.hh"

GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 100, 100, 120, 120, 100, 120};

Batch::Batch(GLuint texture) {
    this->texture = texture;
    glGenVertexArraysOES(1, &this->vao);
    glBindVertexArrayOES(this->vao);
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void Batch::draw(int x, int y, SDL_Rect const &sprite) {
    SDL_Rect placement = {
        x - sprite.w / 2,
        y - sprite.h / 2,
        sprite.w,
        sprite.h
    };
    //SDL_RenderCopy(
    //    Config::renderer,
    //    this->texture,
    //    &sprite,
    //    &placement
    //);
}

void Batch::draw(SDL_Rect const &destination, SDL_Rect const &sprite) {
    //SDL_RenderCopy(
    //    Config::renderer,
    //    this->texture,
    //    &sprite,
    //    &destination
    //);
}

void Batch::render() {
    glBindVertexArrayOES(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
