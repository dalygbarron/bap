#ifndef SHADER_H
#define SHADER_H

#include "gl.hh"

class Shader {
    public:
        constexpr static char const * const DEFAULT_VERTEX =
            "attribute vec4 position;"
            "attribute vec4 textureCoord;"
            "uniform vec4 invWindowSize;"
            "uniform vec2 invTextureSize;"
            "varying vec2 vTextureCoord;"
            "void main() {"
            "gl_Position = position * (invWindowSize * vec4(2.0, 2.0, 1.0, 1.0)) - vec4(1.0, 1.0, 0.0, 0.0);"
            "vTextureCoord = textureCoord.xy * invTextureSize;"
            "}";

        constexpr static char const * const DEFAULT_FRAGMENT =
            "uniform sampler2D sampler;"
            "varying mediump vec2 vTextureCoord;"
            "void main() {"
            "gl_FragColor = texture2D(sampler, vTextureCoord);"
            "}";

        /**
         * Frees the gl junk.
         */
        ~Shader();

        /**
         * Gives you the location of the position attribute.
         * @return the location.
         */
        GLuint getPositionLoc() const;

        /**
         * Gives you the location of the texture coord attribute.
         * @return the location.
         */
        GLuint getTextureCoordLoc() const;

        /**
         * Gives you the location of the invTextureSize uniform
         * @return the location.
         */
        GLuint getInvTextureSizeLoc() const;

        /**
         * Gives you the location of the invWindowSize uniform
         * @return the location.
         */
        GLuint getInvWindowSizeLoc() const;

        /**
         * Gives you the location of the sampler uniform
         * @return the location.
         */
        GLuint getSamplerLoc() const;

        /**
         * Binds the shader.
         */
        void bind();

        /**
         * Creates a shader based on the source of a vertex shader and
         * a fragment shader.
         * @param vertexSrc   is the vertex shader.
         * @param fragmentSrc is the fragment shader.
         * @return the new shader unless it failed in which case you get null.
         */
        static Shader *createShader(
            char const *vertexSrc,
            char const *fragmentSrc
        );

        /**
         * Binds the default shader and returns it. If this is the first time
         * this is called then it creates the default shader. Don't call this
         * before stuff has been set up.
         * @return the default shader.
         */
        static Shader *bindDefaultShader();

    private:
        GLuint program;
        GLuint positionLoc;
        GLuint textureCoordLoc;
        GLuint invTextureSizeLoc;
        GLuint invWindowSizeLoc;
        GLuint samplerLoc;

        /**
         * Secret constructor that just takes the program.
         * @param program is the compiled shader program.
         */
        Shader(GLuint program);
};


#endif
