#include "../Rendering/VertexArray.h"

// Should allow you to set it to dynamic or static drawing
VertexArray::VertexArray() : m_vertexBuffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
{
	Create();
}

VertexArray::~VertexArray()
{
	Bind();
	Destroy();
	m_vertexBuffer.Bind();
	m_vertexBuffer.Destroy();
}

void VertexArray::Create()
{
	glGenVertexArrays(1, &m_id);
}

void VertexArray::Destroy()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::SetVertexAttributes()
{
	if(m_vertexBuffer.GetAttributes().empty())
		return;

	m_vertexBuffer.Bind();
	for(int i = 0; i < m_vertexBuffer.GetAttributes().size(); ++i)
	{
		m_vertexBuffer.GetAttributes()[i].Enable();
		m_vertexBuffer.GetAttributes()[i].Set();
	}
	m_vertexBuffer.Unbind();
}