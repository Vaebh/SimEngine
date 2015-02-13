#ifndef BUFFER_SIMENGINE
#define BUFFER_SIMENGINE

#include "../OpenGL/GLIncludes.h"

// Fill this out with the relevant OpenGL buffer information and methods
// Should handle binding and releasing buffer data, Vbo, etc
// Should work for both 2 and 3 dimensional objects

class Buffer
{
public:
	Buffer();
	~Buffer();

	void Create();
	void Destroy();

	void Bind();
	void Unbind();

private:
	GLvoid* m_dataPtr;
	GLsizeiptr m_dataSize;

	GLenum m_usage;
	GLenum m_target;
};

#endif
