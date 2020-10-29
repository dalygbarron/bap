#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>

int const SCREEN_WIDTH = 768;
int const SCREEN_HEIGHT = 480;

GLuint programId = 0;
GLuint vertexPos2DLocation = -1;
GLuint vbo = 0;
GLuint ibo = 0;

SDL_Window *window = NULL;
SDL_GLContext context;
bool renderQuad = true;

void printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}
		
		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a program\n", program );
	}
}

void printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}
		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a shader\n", shader );
	}
}

/**
 * Loads a default rendering program and clear colour.
 * Technically this will go in the bin later.
 */
bool initGL() {
    programId = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLchar const *vertexShaderSource[] = {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint vertexShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
    if (vertexShaderCompiled != GL_TRUE) {
        printf("Unabled to compile vertex shader %d\n", vertexShader);
        printShaderLog(vertexShader);
        return false;
    }
    glAttachShader(programId, vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar const *fragmentShaderSource[] = {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
    };
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint fragmentShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
    if (fragmentShaderCompiled != GL_TRUE) {
        printf("Unable to compile fragment shader %d\n", fragmentShader);
        printShaderLog(fragmentShader);
        return false;
    }
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d\n", programId);
        printProgramLog(programId);
        return false;
    }
    vertexPos2DLocation = glGetAttribLocation(programId, "LVertexPos2D");
    if (vertexPos2DLocation == -1) {
        printf("LVertexPos2D is not a valid glsl program variable\n");
        return false;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLfloat vertexData[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        -0.5f, 0.5f,
        -0.5f, 0.5f
    };
    GLuint indexData[] = {0, 1, 2, 3};
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        2 * 4 * sizeof(GLfloat),
        vertexData,
        GL_STATIC_DRAW
    );
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    return true;
}

/**
 * Starts SDL, creates the window and initialises opengl.
 * @return false iff there was a critical problem.
 */
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not init, error: %s\n", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    window = SDL_CreateWindow(
        "Death Sucker",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("Couldn't create window, error: %s\n", SDL_GetError());
        return false;
    }
    context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("OpenGL context couldn't start, error: %s\n", SDL_GetError());
        return false;
    }
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initialising glew %s\n", glewGetErrorString(glewError));
    }
    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Couldn't set up vsync, error: %s\n", SDL_GetError());
    }
    if (!initGL()) {
        printf("Unable to init OpenGl\n");
        return false;
    }
    return true;
}

/**
 * Frees junk.
 */
void close() {
    glDeleteProgram(programId);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (renderQuad) {
        glUseProgram(programId);
        glEnableVertexAttribArray(vertexPos2DLocation);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
            vertexPos2DLocation,
            2,
            GL_FLOAT,
            GL_FALSE,
            2 * sizeof(GLfloat),
            NULL
        );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
        glDisableVertexAttribArray(vertexPos2DLocation);
        glUseProgram(0);
    }
}

int main(int argc, char const **argv) {
    if (!init()) {
        return 1;
    }
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        render();
        SDL_GL_SwapWindow(window);
    }

    close();
    return 0;
}
