#ifndef SIMENGINE_SHADER
#define SIMENGINE_SHADER

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/Uniform.h"

#include <string>
#include <memory>
#include <unordered_map>

class Shader
{
public:
	Shader();
	Shader(const std::string& in_name, const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc);
	~Shader();

	Uniform* operator[](const char* in_uniformName);

	void CreateShaderProgram(const std::string& in_vertexShaderSrc, const std::string& in_fragShaderSrc);

	void Use();

	void AddUniform(const char* in_uniformName);

	inline const GLuint GetProgramID() const {return m_shaderProgram;}
	GLint GetAttributeLocation(const char* in_attributeName);
	GLint GetUniformLocation(const char* in_uniformName) const;

private:
	GLuint CreateShaderFromFile(const std::string& in_path, const GLenum& in_shaderType);
	std::string LoadShaderFromFile(const std::string& in_path) const;

	bool ShaderCompilationCheck(const GLuint in_vertexShader, const GLuint in_fragmentShader, const std::string in_shaderName) const;
	void DeleteShader(GLuint in_shader);

private:
	std::string m_name;
	GLuint m_shaderProgram;

	std::unordered_map < const char*, std::unique_ptr<Uniform> > m_uniforms;
};

#endif