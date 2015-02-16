#include "../Rendering/Uniform.h"
#include "../Structure/Vectors.h"

Uniform::Uniform(GLint in_location)
{
	m_location = in_location;
}

// glUniform1_
template<> void Uniform::Set<GLfloat>(GLfloat in_v1) const
{
	glUniform1f(m_location, in_v1);
}

template<> void Uniform::Set<GLint>(GLint in_v1) const
{
	glUniform1i(m_location, in_v1);
}

template<> void Uniform::Set<GLuint>(GLuint in_v1) const
{
	glUniform1ui(m_location, in_v1);
}

// glUniform2_
template<> void Uniform::Set<GLfloat>(GLfloat in_v1, GLfloat in_v2) const
{
	glUniform2f(m_location, in_v1, in_v2);
}

template<> void Uniform::Set<GLint>(GLint in_v1, GLint in_v2) const
{
	glUniform2i(m_location, in_v1, in_v1);
}

template<> void Uniform::Set<GLuint>(GLuint in_v1, GLuint in_v2) const
{
	glUniform2ui(m_location, in_v1, in_v2);
}

// glUniform3_
template<> void Uniform::Set<GLfloat>(GLfloat in_v1, GLfloat in_v2, GLfloat in_v3) const
{
	glUniform3f(m_location, in_v1, in_v2, in_v3);
}

template<> void Uniform::Set<GLint>(GLint in_v1, GLint in_v2, GLint in_v3) const
{
	glUniform3i(m_location, in_v1, in_v1, in_v3);
}

template<> void Uniform::Set<GLuint>(GLuint in_v1, GLuint in_v2, GLuint in_v3) const
{
	glUniform3ui(m_location, in_v1, in_v2, in_v3);
}

// glUniform4_
template<> void Uniform::Set<GLfloat>(GLfloat in_v1, GLfloat in_v2, GLfloat in_v3, GLfloat in_v4) const
{
	glUniform4f(m_location, in_v1, in_v2, in_v3, in_v4);
}

template<> void Uniform::Set<GLint>(GLint in_v1, GLint in_v2, GLint in_v3, GLint in_v4) const
{
	glUniform4i(m_location, in_v1, in_v1, in_v3, in_v4);
}

template<> void Uniform::Set<GLuint>(GLuint in_v1, GLuint in_v2, GLuint in_v3, GLuint in_v4) const
{
	glUniform4ui(m_location, in_v1, in_v2, in_v3, in_v4);
}

// glUniform2_v
template<> void Uniform::SetVec<Vector2>(Vector2 in_value, GLsizei in_count) const
{
	glUniform2fv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::ivec2>(glm::ivec2 in_value, GLsizei in_count) const
{
	glUniform2iv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::uvec2>(glm::uvec2 in_value, GLsizei in_count) const
{
	glUniform2uiv(m_location, in_count, glm::value_ptr(in_value));
}

// glUniform3_v
template<> void Uniform::SetVec<Vector3>(Vector3 in_value, GLsizei in_count) const
{
	glUniform3fv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::ivec3>(glm::ivec3 in_value, GLsizei in_count) const
{
	glUniform3iv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::uvec3>(glm::uvec3 in_value, GLsizei in_count) const
{
	glUniform3uiv(m_location, in_count, glm::value_ptr(in_value));
}

// glUniform4_v
template<> void Uniform::SetVec<glm::vec4>(glm::vec4 in_value, GLsizei in_count) const
{
	glUniform4fv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::ivec4>(glm::ivec4 in_value, GLsizei in_count) const
{
	glUniform4iv(m_location, in_count, glm::value_ptr(in_value));
}

template<> void Uniform::SetVec<glm::uvec4>(glm::uvec4 in_value, GLsizei in_count) const
{
	glUniform4uiv(m_location, in_count, glm::value_ptr(in_value));
}

// glUniformMatrix_fv
template<> void Uniform::SetMatrix<glm::mat2>(glm::mat2 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix2fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat3>(glm::mat3 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix3fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat4>(glm::mat4 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix4fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

// glUniformMatrix_x_fv()
template<> void Uniform::SetMatrix<glm::mat2x3>(glm::mat2x3 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix2x3fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat2x4>(glm::mat2x4 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix2x4fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat3x2>(glm::mat3x2 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix3x2fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat3x4>(glm::mat3x4 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix3x4fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat4x2>(glm::mat4x2 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix4x2fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}

template<> void Uniform::SetMatrix<glm::mat4x3>(glm::mat4x3 in_value, GLsizei in_count, GLboolean in_transpose) const
{
	glUniformMatrix4x3fv(m_location, in_count, in_transpose, glm::value_ptr(in_value));
}