#include "../Foundation/Foundation.h"

#include "../Rendering/RenderSystem.h"
#include "../Rendering/RenderableComponent.h"

#include "../Application/Application.h"

#include "../Rendering/SpriteComponent.h"

#include <iostream>

RenderSystem::RenderSystem() :
m_texManager()
{
	
}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::SetFrameBufferTarget(GLuint inFrameBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, inFrameBuffer);
}

// These two methods should be abstract in System.h
void RenderSystem::AddComponent(IRenderableComponent* inRenderableComponent)
{
	if(inRenderableComponent)
	{
		m_components.push_back(inRenderableComponent);
	}
}

void RenderSystem::RemoveComponent(IRenderableComponent* inRenderableComponent)
{
	if(inRenderableComponent)
	{
		std::vector<IRenderableComponent*>::const_iterator it;

		for(it = m_components.begin(); it != m_components.end(); ++it)
		{
			if((*it) == inRenderableComponent)
			{
				m_components.erase(it);

				// Downsize the vector
				std::vector<IRenderableComponent*>(m_components).swap(m_components);
				break;
			}
		}
	}
}

void RenderSystem::Update(float in_dt)
{
	
}

/*
TODO
- Batch sprites, notes above SpriteComponent.cpp's Draw function
- Create and use Materials
*/
void RenderSystem::Draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	for(uint32_t i = 0; i < m_components.size(); ++i)
	{
		if(m_components[i]->IsVisible())
		{
			m_components[i]->Draw();

			/*
			This obviously needs to be replaced with one draw call which takes the number
			of indices to be drawn from the component being drawn. Should probably make a Material
			class to hold this and a variety of other information. Every RenderableComponent
			should have a Material.
			*/
			if(dynamic_cast<SpriteComponent*>(m_components[i]) != NULL)
			{
				glDisable(GL_DEPTH_TEST);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				glDrawArrays(GL_TRIANGLES, 0, m_components[i]->GetVAO().GetNumVertices());
			}

			// Unbind everthing
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	}

	glfwSwapBuffers(Application::GetApplication()->GetWindow()->GetGLFWWindow());
}