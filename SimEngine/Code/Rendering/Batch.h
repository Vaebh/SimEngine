#ifndef BATCH_SIMEGNINE
#define BATCH_SIMENGINE

#include "../OpenGL/GLIncludes.h"

#include "../Rendering/VertexArray.h"
#include "../Rendering/VertexAttribute.h"

#include <vector>

class Shader;
class Texture;

// This is a problem because I'm never updating the vertex info which changes every frame as things move

class Batch
{
public:
	Batch(Shader* in_shader, Texture* in_texture, const std::vector<GLfloat>& in_vertices);
	~Batch();

	void AddVerticesToBatch(const std::vector<GLfloat>& in_vertices);

	void ClearVertices();

	Shader* GetShader() { return m_shader; }
	Texture* GetTexture() { return m_texture; }

	//void SetBatchDirty(bool in_dirty) { m_batchDirty = in_dirty; }

	void Render();

private:
	Shader* m_shader;
	Texture* m_texture;

	VertexArray m_vao;
	Buffer* m_vertexBuffer;

	std::vector<GLfloat> m_vertexData;

	//bool m_batchDirty;
};

#endif