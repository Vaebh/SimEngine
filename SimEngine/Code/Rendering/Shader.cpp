#include "../Rendering/Shader.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

#define DEBUG_PRINTING 1

Shader::Shader() :
m_shaderProgram(0)
{
  
}

Shader::Shader(const std::string& in_name, const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc) :
m_shaderProgram(0),
m_name(in_name)
{
	CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);
}

Shader::~Shader()
{
	if(m_shaderProgram)
	{
		glDeleteProgram(m_shaderProgram);
	}
}

GLint Shader::GetAttributeLocation(const char* in_attributeName)
{
  return glGetAttribLocation(GetProgramID(), in_attributeName);
}

void Shader::Use()
{
	glUseProgram(GetProgramID());
}

GLint Shader::GetUniformLocation(char* in_uniformName) const
{
	return glGetUniformLocation(GetProgramID(), in_uniformName);
}

//-------------------------------------------------------------------------------------
// CreateShaderProgram
//
// @param vertexShaderSource - The vertex shader we want to use
// @param fragShaderSource - The fragment shader we want to use
//
// @return - The index for the shader program we've just created
//-------------------------------------------------------------------------------------
void Shader::CreateShaderProgram(const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc)
{
	GLuint vertexShader = CreateShaderFromFile(in_vertexShaderSrc, GL_VERTEX_SHADER);
	GLuint fragShader = CreateShaderFromFile(in_fragShaderSrc, GL_FRAGMENT_SHADER);

	if(!ShaderCompilationCheck(vertexShader, fragShader, m_name))
	{
		if(vertexShader != 0)
			DeleteShader(vertexShader);
		if(fragShader != 0)
			DeleteShader(fragShader);

		return;
	}

	// Actually create the shader program
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragShader);

	// Telling the program which buffer the fragment shader is writing to
	glBindFragDataLocation(m_shaderProgram, 0, "outColor");
	glLinkProgram(m_shaderProgram);

	// Detach and delete the shaders
	DeleteShader(vertexShader);
	DeleteShader(fragShader);

	#if DEBUG_PRINTING == 1
	if(glIsProgram(m_shaderProgram) == GL_TRUE)
		cout << "isProgram success" << endl;
	else
		cout << "isProgram fail" << endl;
	#endif

	return;
}

bool Shader::ShaderCompilationCheck(const GLuint in_vertexShader, const GLuint in_fragmentShader, const std::string in_shaderName) const
{
	GLint vertexStatus, fragmentStatus;
	glGetShaderiv(in_vertexShader, GL_COMPILE_STATUS, &vertexStatus);
	glGetShaderiv(in_fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
        
	if(vertexStatus == GL_TRUE && fragmentStatus == GL_TRUE)
	{
		#if DEBUG_PRINTING == 1
		cout << in_shaderName + " shader compilation SUCCESS" << endl;
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

GLuint Shader::CreateShaderFromFile(const std::string& in_path, const GLenum& in_shaderType)
{
	// Get the shader
	std::string shaderSrcString = LoadShaderFromFile(in_path);

	if(shaderSrcString.empty())
	{
		return 0;
	}

	const GLchar* shaderSrc = shaderSrcString.c_str();

	// Loading Vertex Shader
	GLuint shader = glCreateShader(in_shaderType);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	return shader;
}

std::string Shader::LoadShaderFromFile(const std::string& in_path) const
{
	std::string shaderSrc = "";
	std::ifstream myFile;

	myFile.open(in_path);
	if(myFile.is_open() && !myFile.bad())
	{
		return shaderSrc.assign(std::istreambuf_iterator<char>(myFile), std::istreambuf_iterator<char>());
	}

	return "";
}

void Shader::DeleteShader(GLuint in_shader)
{
	glDetachShader(m_shaderProgram, in_shader);
	glDeleteShader(in_shader);
}