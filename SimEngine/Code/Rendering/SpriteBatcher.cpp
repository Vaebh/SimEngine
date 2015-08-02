#include "../Rendering/SpriteBatcher.h"

#include "../Rendering/Batch.h"
#include "../Rendering/Texture.h"

SpriteBatcher::SpriteBatcher()// : m_batchsDirty(false)
{
	
}

SpriteBatcher::~SpriteBatcher()
{
	
}

void SpriteBatcher::AddSprite(SpriteComponent* in_newSpriteComp)
{
	std::vector<GLfloat> vertInfo;
	in_newSpriteComp->GetVertexInfo(vertInfo);

	for (int i = 0; i < m_batchs.size(); ++i)
	{
		if (//in_newSpriteComp->GetShader() == m_batchs[i]->GetShader() &&
			in_newSpriteComp->GetTexture() == m_batchs[i]->GetTexture())
		{
			m_batchs[i]->AddVerticesToBatch(vertInfo);
			return;
		}
	}
	
	m_batchs.push_back(new Batch(in_newSpriteComp->GetShader(), in_newSpriteComp->GetTexture(), vertInfo));
}

void SpriteBatcher::DrawBatchs()
{
	for (int i = 0; i < m_batchs.size(); ++i)
	{
		m_batchs[i]->Render();
	}

	FlushBatchData();
}

void SpriteBatcher::FlushBatchData()
{
	for (int i = 0; i < m_batchs.size(); ++i)
	{
		m_batchs[i]->ClearVertices();
	}
}









// old

/*void SpriteBatcher::DrawBatchs()
{
	std::list<SpriteComponent*>::iterator iter;
	for(int i = 0; i < m_sprites.size(); ++i)
	{
	if(m_sprites[i].second.empty())
	{
	//remove pair from vector
	}
	for(iter = m_sprites[i].second.begin(); iter != m_sprites[i].second.end(); ++iter)
	{
	// Don't draw sprites which are detached or invisible
	if((*iter)->GetOwner() == NULL || !(*iter)->IsVisible())
	continue;

	// This whole thing requires all sprites referencing the same shaders, textures, and vao's
	// Currently the only one that's the same across sprites is the texture.
	if(m_activeShader != &(*iter)->GetShader())
	{
	m_activeShader = &(*iter)->GetShader();
	m_activeShader->Use();
	}

	if(m_activeTexture != (*iter)->GetTexture())
	{
	m_activeTexture = (*iter)->GetTexture();
	m_activeTexture->Activate(GL_TEXTURE0);
	m_activeTexture->Bind();
	}

	if(m_activeVAO != &(*iter)->GetVAO())
	{
	m_activeVAO = &(*iter)->GetVAO();
	m_activeVAO->Bind();
	}

	(*iter)->Draw();

	(*iter)->GetVertexInfo(m_vertInfo);

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	}

	static bool isSet = false;

	if (!isSet)
	{
	isSet = true;
	m_activeVAO->GetVertexBuffer().Bind();
	m_activeVAO->GetVertexBuffer().SetData(sizeof(GLfloat) * m_vertInfo.size(), &(m_vertInfo[0]));
	//m_vertexBuffer->SetData(sizeof(GLfloat) * 60, &(vertInfo[0]));
	}

	GLsizei vertCount = (m_vertInfo.size() / 60) * 6;
	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	m_vertInfo.clear();*/