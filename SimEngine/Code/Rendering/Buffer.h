#ifndef BUFFER_SIMENGINE
#define BUFFER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/VertexAttribute.h"

#include <vector>

// Fill this out with the relevant OpenGL buffer information and methods
// Should handle binding and releasing buffer data, Vbo, etc
// Should work for both 2 and 3 dimensional objects

class Buffer
{
public:
	Buffer();
	Buffer(GLenum in_target, GLenum in_usage);
	virtual ~Buffer();

	void Create();
	void Destroy();

	void Bind();
	void Unbind();

	void SetData(GLsizeiptr in_dataSize, GLvoid* in_dataPtr);

	void AddAttribute(VertexAttribute in_attribute);
	inline std::vector<VertexAttribute> GetAttributes() {return m_attributes;}

	GLuint m_bufferID;


protected:
	GLenum m_usage;
	GLenum m_target;

	

private:
	GLvoid* m_dataPtr;
	GLsizeiptr m_dataSize;

	std::vector<VertexAttribute> m_attributes;
};

#endif
