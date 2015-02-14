#ifndef SIMENGINE_SHADER
#define SIMENGINE_SHADER

#include "../OpenGL/GLIncludes.h"
#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& inName, const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc);
	~Shader();

	inline const GLuint GetProgramID() const {return m_shaderProgram;}
	GLint GetAttributeLocation(const char* in_attributeName);

	void CreateShaderProgram(const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc);

	void Use();
	GLint GetUniformLocation(char* in_uniformName) const;

private:
	GLuint CreateShaderFromFile(const std::string& in_path, const GLenum& in_shaderType);
	std::string LoadShaderFromFile(const std::string& in_path) const;

	bool ShaderCompilationCheck(const GLuint in_vertexShader, const GLuint in_fragmentShader, const std::string in_shaderName) const;
	void DeleteShader(GLuint in_shader);

private:
	std::string m_name;
	GLuint m_shaderProgram;
};

#endif