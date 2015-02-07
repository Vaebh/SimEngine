#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/RenderableMeshComponent.h"
#include "../Rendering/RenderSystem.h"

#include <iostream>

/*
TODO
This needs to be changed from only working with a pre-set cube to
working with any model/set of vertices that I give it.

For this reason I need to get model loading working as well
*/

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

RenderableMeshComponent::RenderableMeshComponent(std::string in_tex) :
IRenderableComponent()
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_textureData = LoadImage(in_tex.c_str());
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
	// Generate vertex array and vertex buffer
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	// Bind and send data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void RenderableMeshComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
{
	if(in_vertexShaderSrc.empty() || in_fragShaderSrc.empty())
		return;

	// Bind vertex array
	glBindVertexArray(m_vao);

	// Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Create and activate shader
	m_shader.CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);
	glUseProgram(m_shader.GetProgramID());

	// Link the vertex attributes to the data
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

glm::mat4 RenderableMeshComponent::CalculateModelMatrix()
{
	glm::mat4 transMatrix = glm::translate(glm::mat4(1), GetOwner()->GetPosition());
	glm::mat4 inverseTransMatrix = glm::inverse(transMatrix);

	glm::mat4 rotMatrix = transMatrix * glm::mat4_cast(GetOwner()->m_rotationQuat) * inverseTransMatrix;

	glm::mat4 model = glm::mat4(1);
	model = glm::scale(model, GetOwner()->m_scale) * rotMatrix * glm::translate(model, GetOwner()->GetPosition());

	return model;
}

void RenderableMeshComponent::Update(float in_dt)
{
	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, -0.0001f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, 0.0001f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(-0.0001f, 0.f, 0.f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0001f, 0.f, 0.f));
	}

	GetOwner()->m_rotationQuat = glm::rotate(GetOwner()->m_rotationQuat, in_dt * 50, Vector3(0, 1, 0));
}

void RenderableMeshComponent::Draw()
{
	// Bind shader program
	glUseProgram(m_shader.GetProgramID());

	// Set shader uniforms
    glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE, glm::value_ptr(CalculateModelMatrix()));

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *(m_textureData.textureID));

	// Bind vertex array
	glBindVertexArray(m_vao);
}