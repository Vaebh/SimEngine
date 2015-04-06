#include "../Rendering/SpriteBatcher.h"

#include "../Rendering/Texture.h"

namespace
{
    const GLfloat SPRITE_VERTICES[] =
    {	// position					//texcoords
        -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
        
        0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f
    };
};

SpriteBatcher::SpriteBatcher() :
m_activeShader(NULL),
m_activeTexture(NULL),
m_activeVAO(NULL)
{
	const GLfloat SPRITE_VERTICES2[] = {1.f};
}

SpriteBatcher::~SpriteBatcher()
{
	
}

/*void SpriteBatcher::AddUniforms()
{
	m_activeShader.AddUniform("model");
	m_activeShader.AddUniform("uv");
	m_activeShader.AddUniform("textureSprite");
}*/

void SpriteBatcher::AddSprite(SpriteComponent* in_newSpriteComp)
{
	// Check if we have a list for this texture already, if we do then add a new one for it
	// if we don't then add a new list with it in it
	std::vector< std::pair<std::string, std::list<SpriteComponent*>> >::iterator iter;
	for(iter = m_sprites.begin(); iter != m_sprites.end(); ++iter)
	{
		if((*iter).first == in_newSpriteComp->GetTextureName())
		{
			(*iter).second.push_back(in_newSpriteComp);
			return;
		}
	}

	m_sprites.push_back( std::make_pair(in_newSpriteComp->GetTextureName(), std::list<SpriteComponent*>()) );
	m_sprites.back().second.push_back(in_newSpriteComp);
}

void SpriteBatcher::DrawBatch()
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

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	m_activeShader = NULL;
	m_activeTexture = NULL;
	m_activeVAO = NULL;
}