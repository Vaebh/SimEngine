#include "../Rendering/Batch.h"

#include "../Rendering/Shader.h"
#include "../Rendering/Texture.h"

Batch::Batch(Shader* in_shader, Texture* in_texture, const std::vector<GLfloat>& in_vertices) :
m_shader(in_shader),
m_texture(in_texture),
m_vao(),
m_vertexData(in_vertices)//,
//m_batchDirty(true)
{
	m_vertexBuffer = &(m_vao.GetVertexBuffer());

	m_vao.Bind();

	// Bind vertex buffer
	m_vertexBuffer->Bind();

	// Add vertex attributes
	// TODO - This is specific to sprites, should move it out so Batches can be used for meshes too
	m_vertexBuffer->AddAttribute(VertexAttribute(m_shader->GetAttributeLocation("position"), 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), 0));
	m_vertexBuffer->AddAttribute(VertexAttribute(m_shader->GetAttributeLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat))));
	m_vertexBuffer->AddAttribute(VertexAttribute(m_shader->GetAttributeLocation("spriteFrame"), 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))));

	m_vao.SetVertexAttributes();
}

Batch::~Batch()
{
	int g = 0;
	g += 4;
}

void Batch::AddVerticesToBatch(const std::vector<GLfloat>& in_vertices)
{
	for (int i = 0; i < in_vertices.size(); ++i)
		m_vertexData.push_back(in_vertices[i]);

	//m_batchDirty = true;
}

void Batch::ClearVertices()
{
	m_vertexData.clear();
	//m_batchDirty = true;
}

void Batch::Render()
{
	if (m_vertexData.size() > 0)
	{
		/*if (m_batchDirty)
		{
			m_batchDirty = false;

			// Bind vertex buffer
			m_vertexBuffer->Bind();

			// Send data to GPU
			m_vertexBuffer->SetData(sizeof(GLfloat) * m_vertexData.size(), &(m_vertexData[0]));
		}*/

		//m_vao.Bind();

		// Bind vertex buffer
		m_vertexBuffer->Bind();

		// Send data to GPU
		m_vertexBuffer->SetData(sizeof(GLfloat) * m_vertexData.size(), &(m_vertexData[0]));

		m_shader->Use();
		m_texture->Activate(GL_TEXTURE0);
		m_texture->Bind();

		// The 60 is for sprites, will need to find a way to calculate it for all things
		GLsizei vertCount = (m_vertexData.size() / 60) * 6;
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
	}
}