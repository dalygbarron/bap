#ifndef SHADER_H
#define SHADER_H

class Shader {
    public:
        char const *defaultVertexShader = "attribute vec4 position;"
            "attribute vec4 textureCoord;"
            "uniform vec4 invCanvas;"
            "uniform vec2 invTextureSize;"
            "varying highp vec2 vTextureCoord;"
            "void main() {"
            "gl_Position = position * (invCanvas * vec4(2, 2, 1.0, 1.0)) - vec4(1.0, 1.0, 0, 0);"
            "vTextureCoord = textureCoord.xy * invTextureSize;"
            "}";

        char const *defaultFragmentShader = "uniform sampler2D sampler;
            "varying highp vec2 vTextureCoord;"
            "void main() {"
            "gl_FragColor = texture2D(sampler, vTextureCoord);"
            "}";

        /**
         * Creates the shader with the source of the vertex shader and the
         * fragment shader.
         * @param vertexSrc   is the source code of the vertex shader.
         * @param fragmentSrc is the source code of the fragment shader.
         */
        Shader(char const *vertexSrc, char const *fragmentSrc);

        /**
         * Frees the gl junk.
         */
        ~Shader();

    private:
        GLuint program;
        GLuint positionLoc;
        GLuint textureCoordLoc;
        GLuint invTextureSizeLoc;
        GLuint invWindowSizeLoc;
        GLuint samplerLoc;
};


#endif
