#include "Batch.hh"
#include "Shader.hh"
#include "Config.hh"

Batch::Batch(Texture *texture, int max):
    texture(texture),
    max(max)
{
    this->texture = texture;
    this->items = new GLfloat[max * 12];
    this->textureItems = new GLfloat[max * 12];
    glGenBuffers(N_BUFFER, this->buffers);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[Batch::ITEM_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * max * 12, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[Batch::TEXTURE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * max * 12, NULL, GL_DYNAMIC_DRAW);
    Shader *shader = Shader::bindDefaultShader();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture->glTexture);
    glUniform1i(shader->getSamplerLoc(), 0);
    glUniform2f(
        shader->getInvTextureSizeLoc(),
        1.0f / texture->width,
        1.0f / texture->height
    );
}

Batch::~Batch() {
    delete this->items;
    delete this->textureItems;
    // TODO: should probably delete some stuff.
}

void Batch::clear() {
    this->n = 0;
}

void Batch::draw(int x, int y, SDL_Rect const &sprite) {
    SDL_Rect dst {
        x - sprite.w / 2,
        y - sprite.h / 2,
        sprite.w,
        sprite.h
    };
    this->draw(dst, sprite);
}

void Batch::draw(SDL_Rect const &dst, SDL_Rect const &src) {
    if (this->n >= this->max) return;
    int offset = this->n * 12;
    this->items[offset] = dst.x;
    this->items[offset + 1] = dst.y;
    this->items[offset + 2] = dst.x + dst.w;
    this->items[offset + 3] = dst.y;
    this->items[offset + 4] = dst.x;
    this->items[offset + 5] = dst.y + dst.h;
    this->items[offset + 6] = dst.x + dst.w;
    this->items[offset + 7] = dst.y;
    this->items[offset + 8] = dst.x + dst.w;
    this->items[offset + 9] = dst.y + dst.h;
    this->items[offset + 10] = dst.x;
    this->items[offset + 11] = dst.y + dst.h;
    this->textureItems[offset] = src.x;
    this->textureItems[offset + 1] = src.y + src.h;
    this->textureItems[offset + 2] = src.x + src.w;
    this->textureItems[offset + 3] = src.y + src.h;
    this->textureItems[offset + 4] = src.x;
    this->textureItems[offset + 5] = src.y;
    this->textureItems[offset + 6] = src.x + src.w;
    this->textureItems[offset + 7] = src.y + src.h;
    this->textureItems[offset + 8] = src.x + src.w;
    this->textureItems[offset + 9] = src.y;
    this->textureItems[offset + 10] = src.x;
    this->textureItems[offset + 11] = src.y;
    this->n++;
}

void Batch::render() {
    Shader *shader = Shader::bindDefaultShader();
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[Batch::ITEM_BUFFER]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n * 12, this->items);
    glVertexAttribPointer(shader->getPositionLoc(), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(shader->getPositionLoc());
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[Batch::TEXTURE_BUFFER]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n * 12, this->textureItems);
    glVertexAttribPointer(shader->getTextureCoordLoc(), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(shader->getTextureCoordLoc());
    // TODO: use different texture slots to save time when using
    //       more than one texture.
    glDrawArrays(GL_TRIANGLES, 0, this->n * 6);
}
