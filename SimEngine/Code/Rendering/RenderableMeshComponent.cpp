#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/RenderableMeshComponent.h"
#include "../Rendering/RenderSystem.h"

#include <iostream>

const GLfloat vertices[] = 
{
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
};

const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/3DVertexShader.txt";
const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/3DFragShader.txt";

using namespace std;

RenderableMeshComponent::RenderableMeshComponent() :
IRenderableComponent()
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_textureData = LoadImage("bros.png");
}

RenderableMeshComponent::~RenderableMeshComponent()
{
	// TODO - Make some kind of sprite managery class, maybe SpriteBatch, and have it store and bind the vao and vbo as they're the same for every sprite
	// Also maybe use the same shader program for all sprites
    //glDeleteBuffers(1, &mVbo);
    //glDeleteVertexArrays(1, &mVao);
}

void RenderableMeshComponent::Initialise()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void RenderableMeshComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
{
	if(in_vertexShaderSrc.empty() || in_fragShaderSrc.empty())
		return;

	m_shader.CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);

	glUseProgram(m_shader.GetProgramID());

	glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	GLint posAttrib = glGetAttribLocation(m_shader.GetProgramID(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(m_shader.GetProgramID(), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glUniform1i(glGetUniformLocation(m_shader.GetProgramID(), "textureSprite"), 0);

	m_modelUniform = glGetUniformLocation(m_shader.GetProgramID(), "move");

	m_camCenter = Vector3(0.f, 0.f, 0.f);
	m_camLookat = Vector3(1.5f, 1.5f, 1.5f);

	// Set up projection
    glm::mat4 view = glm::lookAt(
        m_camLookat,
        m_camCenter,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    GLint uniView = glGetUniformLocation(m_shader.GetProgramID(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(m_shader.GetProgramID(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

glm::mat4 RenderableMeshComponent::CalculateMatrix()
{
	glm::mat4 model = glm::mat4(1);
	model = glm::scale(model, GetOwner()->m_scale) * glm::mat4_cast(GetOwner()->m_rotationQuat) * glm::translate(model, GetOwner()->GetPosition());

	return model;
}

void RenderableMeshComponent::Update(float in_dt)
{
	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, -0.01f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, 0.01f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(-0.01f, 0.f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.01f, 0.f, 0.f));
	}
}

void RenderableMeshComponent::Draw()
{
    glBindTexture(GL_TEXTURE_2D, *(m_textureData.textureID));

	// Calculate transformation
    glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE, glm::value_ptr(CalculateMatrix()));
}