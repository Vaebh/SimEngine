#ifndef VERTEX_ARRAY_SIMENGINE
#define VERTEX_ARRAY_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Create();
	void Destroy();

	void Bind();
	void Unbind();

	inline const GLuint GetID() {return m_id;}

	inline Buffer& GetVertexBuffer() {return m_vertexBuffer;}
	inline void SetVertexBuffer(Buffer in_vertexBuffer) {m_vertexBuffer = in_vertexBuffer;}

	inline const GLuint GetNumVertices() const {return m_numVertices;}
	inline void SetNumVertices(GLuint in_numVertices) {m_numVertices = in_numVertices;}

	void SetVertexAttributes();

private:
	GLuint m_id;
	Buffer m_vertexBuffer;

	GLuint m_numVertices;
};

#endif