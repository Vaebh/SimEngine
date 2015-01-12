#ifndef SIMENGINE_SHADER
#define SIMENGINE_SHADER

#include "../OpenGL/GLIncludes.h"
#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& inName, const std::string& vertexShaderSrc, const std::string& fragShaderSrc);
	~Shader();

	inline GLuint GetProgramID() {return mShaderProgram;}
	GLint GetAttributeLocation(const char* inAttributeName);

	void CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragShaderSrc);

private:
	GLuint CreateShaderFromFile(const std::string& path, const GLenum& shaderType);
	std::string LoadShaderFromFile(const std::string& path) const;

	bool ShaderCompilationCheck(const GLuint vertexShader, const GLuint fragmentShader, const std::string shaderName) const;
	void DeleteShader(GLuint inShader);

private:
	std::string mName;
	GLuint mShaderProgram;
};

#endif