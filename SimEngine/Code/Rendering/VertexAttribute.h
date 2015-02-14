#ifndef VERTEX_ATTRIBUTE_SIMENGINE
#define VERTEX_ATTRIBUTE_SIMENGINE

#include "../OpenGL/GLIncludes.h"

class VertexAttribute
{
public:
	VertexAttribute();
	VertexAttribute(GLuint in_index, GLint in_size, GLenum in_type, GLboolean in_normalised, GLsizei in_stride, GLvoid* in_offset);

	void Enable();
	void Set();

private:
	GLuint m_index;
	GLint m_size;
	GLenum m_type;
	GLboolean m_normalised;
	GLsizei m_stride;
	GLvoid* m_offset;
};

#endif