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
         * Frees the gl junk.
         */
        ~Shader();

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
