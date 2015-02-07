#include "../Foundation/Foundation.h"

#include "../Rendering/RenderSystem.h"
#include "../Rendering/Shader.h"
#include <iostream>

RenderSystem* RenderSystem::mRenderer = NULL;

GLFWwindow* RenderSystem::mWindow;

static void ErrorCallback(int error, const char* description)
{
    std::cout<< "GLFW ERROR: " << description << std::endl;
}

namespace
{
	// Should move this to somewhere more appropriate, Application.cpp maybe?
	GLFWwindow* InitialiseWindow()
	{
		if (!glfwInit())
			return NULL;
        
        glfwSetErrorCallback(ErrorCallback);
    
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(640, 480, "Breakout Clone", NULL, NULL);
        
		if(!window)
		{
			glfwTerminate();
            return NULL;
		}
  
		glfwMakeContextCurrent(window);

		glViewport(0, 0, 640, 480);

		glewExperimental = GL_TRUE;
		glewInit();

		glEnable(GL_DEPTH_TEST);

		return window;
	}
}

RenderSystem::RenderSystem()
{
	if(!mWindow)
	{
		mWindow = InitialiseWindow();
	}
}

RenderSystem::~RenderSystem()
{

}

RenderSystem* RenderSystem::GetSingleton()
{
	if(!mRenderer)
	{
		mRenderer = new RenderSystem();
	}

	return mRenderer;
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
	/*for(std::vector<IRenderableComponent*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(in_dt);
		}
	}*/
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
			//glUseProgram(m_components[i]->GetShader().GetProgramID());

			// This is bad, should be done in the actual draw methods for each component
			// Maybe in default renderableComponent draw?
			//if(m_components[i]->GetOwner()->GetCameraManager()->GetActiveCamera().m_viewMatrixChanged)
			{
				/*GLint uniView = glGetUniformLocation(m_components[i]->GetShader().GetProgramID(), "view");

				glm::mat4 viewMatrix = glm::lookAt(
					ZERO,
					Vector3(1.5f, 1.5f, 1.5f),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
				glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));*/
				//glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(m_components[i]->GetOwner()->GetCameraManager()->GetActiveCamera().GetViewMatrix()));
			}

			m_components[i]->Draw();

			/*
			This obviously needs to be replaced with one draw call which takes the number
			of indices to be drawn from the component being drawn. Should probably make a Material
			class to hold this and a variety of other information. Every RenderableComponent
			should have a Material.
			*/
			if(m_components[i]->GetOwner()->GetName() == "ball")
			{
				glDisable(GL_DEPTH_TEST);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			// Unbind everthing
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	}

	//m_components[i]->GetOwner()->GetCameraManager()->GetActiveCamera().ViewMatrixChanged();
}