#ifndef GLUTILS_SIMENGINE
#define GLUTILS_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include <string>

//GLFWwindow* InitialiseWindow(int width = 640, int height = 480);

struct TextureData
{
	//TextureData(GLuint inTexID, float inWidth, float inHeight) {textureID = inTexID; width = inWidth; height = inHeight;}
	std::string name;
	GLuint* textureID;
	float width;
	float height;
};

bool ShaderCompilationCheck(GLuint shader, std::string shaderType);

// Sets up the 3D and 2D shader variables
void Setup3D(GLuint& shaderProgram);
void Setup2D(const GLuint& shaderProgram);

// Creates a shader program from the supplied vertex and fragment shaders
// Includes compilation check
GLuint CreateShaderProgram(std::string vertexShaderSrc, std::string fragShaderSrc);

std::string LoadShader(std::string path);

GLuint CreateShaderFromFile(std::string path, GLenum shaderType);

// Loads an image using the SOIL library
TextureData LoadImage(const GLchar * path);

// Draws a square in direct mode (glBegin and glEnd)
void DrawSquare(double centerX, double centerY, float length, GLFWwindow * window);

// Prints out mouse coordinates
void mouseCallback(GLFWwindow * window, int button, int action, int mods);

// Keyboard controls, exit with Esc
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif