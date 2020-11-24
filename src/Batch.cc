#include "Batch.hh"
#include "Config.hh"

Batch::Batch(Texture *texture, int max): max(max) {
    this->texture = texture;
    this->items = new float[max * 12];
    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
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
    if (this->n >= this->max) return;
    int offset = this->n * 12;
    items[offset] = dst.x;
    items[offset + 1] = dst.y;
    items[offset + 2] = dst.x + dst.width;
    items[offset + 3] = dst.y;
    items[offset + 4] = dst.x;
    items[offset + 5] = dst.y + dst.height;
    items[offset + 6] = dst.x + dst.width;
    items[offset + 7] = dst.y;
    items[offset + 8] = dst.x + dst.width;
    items[offset + 9] = dst.y + dst.height;
    items[offset + 10] = dst.x;
    items[offset + 11] = dst.y + dst.height;
    textureItems[offset] = src.x;
    textureItems[offset + 1] = src.y + src.height;
    textureItems[offset + 2] = src.x + src.width;
    textureItems[offset + 3] = src.y + src.height;
    textureItems[offset + 4] = src.x;
    textureItems[offset + 5] = src.y;
    textureItems[offset + 6] = src.x + src.width;
    textureItems[offset + 7] = src.y + src.height;
    textureItems[offset + 8] = src.x + src.width;
    textureItems[offset + 9] = src.y;
    textureItems[offset + 10] = src.x;
    textureItems[offset + 11] = src.y;
    this->n++;
}

void Batch::render() {
    Shader *shader = Shader::bindDefaultShader();
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->items);
    glVertexAttribPointer(shader->positionLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(shader->positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, textureItems);
    glVertexAttribPointer(shader->textureCoordLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(shader->textureCoordLoc);
    // TODO: use different texture slots to save time when using
    //       more than one texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->glTexture);
    glUniform1i(shader.sampler, 0);
    glUniform2f(shader.invTextureSize, 1 / texture->width, 1 / texture->height);
    glDrawArrays(GL_TRIANGLES, 0, this->n * 6);
}
