#include "../Rendering/Shader.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

#define DEBUG_PRINTING 1

Shader::Shader() :
mShaderProgram(0)
{
  
}

Shader::Shader(const std::string& inName, const std::string& vertexShaderSrc, const std::string& fragShaderSrc) :
mShaderProgram(0),
mName(inName)
{
	CreateShaderProgram(vertexShaderSrc, fragShaderSrc);
}

Shader::~Shader()
{
	if(mShaderProgram)
	{
		glDeleteProgram(mShaderProgram);
	}
}

GLint Shader::GetAttributeLocation(const char * inAttributeName)
{
  return glGetAttribLocation(GetProgramID(), inAttributeName);
}

//-------------------------------------------------------------------------------------
// CreateShaderProgram
//
// @param vertexShaderSource - The vertex shader we want to use
// @param fragShaderSource - The fragment shader we want to use
//
// @return - The index for the shader program we've just created
//-------------------------------------------------------------------------------------
void Shader::CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragShaderSrc)
{
	GLuint vertexShader = CreateShaderFromFile(vertexShaderSrc, GL_VERTEX_SHADER);
	GLuint fragShader = CreateShaderFromFile(fragShaderSrc, GL_FRAGMENT_SHADER);

	if(!ShaderCompilationCheck(vertexShader, fragShader, mName))
	{
		if(vertexShader != 0)
			DeleteShader(vertexShader);
		if(fragShader != 0)
			DeleteShader(fragShader);

		return;
	}

	// Actually create the shader program
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, vertexShader);
	glAttachShader(mShaderProgram, fragShader);

	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(mShaderProgram, 0, "outColor");
	glLinkProgram(mShaderProgram);

	// Detach and delete the shaders
	DeleteShader(vertexShader);
	DeleteShader(fragShader);

	#if DEBUG_PRINTING == 1
	if(glIsProgram(mShaderProgram) == GL_TRUE)
		cout << "isProgram success" << endl;
	else
		cout << "isProgram fail" << endl;
	#endif

	return;
}

bool Shader::ShaderCompilationCheck(const GLuint vertexShader, const GLuint fragmentShader, const std::string shaderName) const
{
	GLint vertexStatus, fragmentStatus;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
        
	if(vertexStatus == GL_TRUE && fragmentStatus == GL_TRUE)
	{
		#if DEBUG_PRINTING == 1
		cout << shaderName + " shader compilation SUCCESS" << endl;
		#endif
		return true;
	}
	else
	{
		if(vertexStatus == GL_FALSE)
		{
			#if DEBUG_PRINTING == 1
			cout << "Vertex shader compilation FAILED" << endl;
			#endif
		}
		if(fragmentStatus == GL_FALSE)
		{
			#if DEBUG_PRINTING == 1
			cout << "Fragment shader compilation FAILED" << endl;
			#endif
		}

		cout << "Invalid shaders" << endl;

		return false;
	}
}

GLuint Shader::CreateShaderFromFile(const std::string& path, const GLenum& shaderType)
{
	// Get the shader
	std::string shaderSrcString = LoadShaderFromFile(path);

	if(shaderSrcString.empty())
	{
		return 0;
	}

	const GLchar* shaderSrc = shaderSrcString.c_str();

	// Loading Vertex Shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	return shader;
}

std::string Shader::LoadShaderFromFile(const std::string& path) const
{
	std::string shaderSrc = "";
	std::ifstream myFile;

	myFile.open(path);
	if(myFile.is_open() && !myFile.bad())
	{
		return shaderSrc.assign(std::istreambuf_iterator<char>(myFile), std::istreambuf_iterator<char>());
	}

	return "";
}

void Shader::DeleteShader(GLuint inShader)
{
	glDetachShader(mShaderProgram, inShader);
	glDeleteShader(inShader);
}