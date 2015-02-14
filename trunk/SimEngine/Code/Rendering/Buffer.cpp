#include "../Rendering/Buffer.h"

Buffer::Buffer() : 
m_target(GL_ARRAY_BUFFER),
m_usage(GL_STATIC_DRAW)
{
	//Create();
}

Buffer::Buffer(GLenum in_target, GLenum in_usage) : 
m_target(in_target),
m_usage(in_usage)
{
	Create();
}

Buffer::~Buffer()
{
	Destroy();
}

void Buffer::Create()
{
	glGenBuffers(1, &m_bufferID);
}

void Buffer::Destroy()
{
	glDeleteBuffers(1, &m_bufferID);
}

void Buffer::Bind()
{
	glBindBuffer(m_target, m_bufferID);
}

void Buffer::Unbind()
{
	glBindBuffer(m_target, 0);
}

void Buffer::SetData(GLsizeiptr in_dataSize, GLvoid* in_dataPtr)
{
	glBufferData(m_target, in_dataSize, in_dataPtr, m_usage);
}

void Buffer::AddAttribute(VertexAttribute in_attribute)
{
	m_attributes.push_back(in_attribute);
}