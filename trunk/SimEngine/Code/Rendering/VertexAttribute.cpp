#include "../Rendering/VertexAttribute.h"

VertexAttribute::VertexAttribute() : 
m_index(0),
m_size(0),
m_type(GL_ARRAY_BUFFER),
m_normalised(GL_FALSE),
m_stride(0),
m_offset(NULL)
{

}

VertexAttribute::VertexAttribute(GLuint in_index, GLint in_size, GLenum in_type, GLboolean in_normalised, GLsizei in_stride, GLvoid* in_offset) : 
m_index(in_index),
m_size(in_size),
m_type(in_type),
m_normalised(in_normalised),
m_stride(in_stride),
m_offset(in_offset)
{

}

void VertexAttribute::Enable()
{
	glEnableVertexAttribArray(m_index);
}

void VertexAttribute::Set()
{
	glVertexAttribPointer(m_index, m_size, m_type, m_normalised, m_stride, m_offset);
}