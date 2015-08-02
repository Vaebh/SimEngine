#include "../Foundation/Foundation.h"

#include "../Rendering/RenderSystem.h"
#include "../Rendering/RenderableComponent.h"

#include "../Application/Application.h"

#include "../Rendering/SpriteComponent.h"
#include "../Structure/Window.h"

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

void RenderSystem::Update(float in_dt)
{
	
}

void RenderSystem::AddSpriteToBatch(SpriteComponent* in_sprite)
{
	m_spriteBatcher.AddSprite(in_sprite);
}

void RenderSystem::PreDraw()
{
	std::list<IComponent*>::iterator iter;
	for (iter = m_components.begin(); iter != m_components.end(); ++iter)
	{
		IRenderableComponent* rendComp = static_cast<IRenderableComponent*>(*iter);
		if (rendComp->IsVisible())
		{
			// Here is where things will add themselves to batchs
			rendComp->PreDraw();
		}
	}
}

/*
TODO
- Create and use Materials
*/
void RenderSystem::Draw()
{
	PreDraw();

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	/*std::list<IComponent*>::iterator iter;
	for(iter = m_components.begin(); iter != m_components.end(); ++iter)
	{
		IRenderableComponent* rendComp = static_cast<IRenderableComponent*>(*iter);
		if(rendComp->IsVisible())
		{
			rendComp->Draw();

			/*
			This obviously needs to be replaced with one draw call which takes the number
			of indices to be drawn from the component being drawn. Should probably make a Material
			class to hold this and a variety of other information. Every RenderableComponent
			should have a Material.
			*/

			// Draw 3D meshes
			//glEnable(GL_DEPTH_TEST);
			//glDrawArrays(GL_TRIANGLES, 0, rendComp->GetVAO().GetNumVertices());
	//	}
	//}

	// Draw sprites
	glDisable(GL_DEPTH_TEST);
	m_spriteBatcher.DrawBatchs();

	glfwSwapBuffers(Application::GetApplication()->GetWindow()->GetGLFWWindow());
}