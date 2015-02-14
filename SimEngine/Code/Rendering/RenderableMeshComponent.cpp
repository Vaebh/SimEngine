#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/RenderableMeshComponent.h"
#include "../Rendering/RenderSystem.h"

#include "../Camera/CameraManager.h"

#include "../Utils/ModelLoader.h"

#include <iostream>

namespace
{
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/3DVertexShader.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/3DFragShader.txt";

	const std::string modelPath = "../SimEngine/Assets/Models/";
	const char* defaultModel = "cube.obj";
}

using namespace std;

RenderableMeshComponent::RenderableMeshComponent(const char* in_textureName, const char* in_meshName) :
IRenderableComponent(),
m_modelUniform(0),
m_viewUniform(0)
{
	m_textureData = LoadImage(in_textureName);

	Initialise(in_meshName);
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);
}

RenderableMeshComponent::~RenderableMeshComponent()
{
	m_vao.Destroy();
}

void RenderableMeshComponent::Initialise(const char* in_meshName)
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());

	std::vector<GLfloat> vertexData;

	assert(LoadModel(in_meshName, vertexData));

	m_vertexBuffer->Bind();
	m_vertexBuffer->SetData(vertexData.size() * sizeof(GLfloat), &vertexData[0]);
}

void RenderableMeshComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
{
	if(in_vertexShaderSrc.empty() || in_fragShaderSrc.empty())
		return;

	// Bind vertex array
	m_vao.Bind();

	// Bind vertex buffer
    m_vertexBuffer->Bind();

	// Create and activate shader
	m_shader.CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);
	m_shader.Use();

	// Add vertex attributes
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0) );
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))) );

	m_vao.SetVertexAttributes();

	SetUniforms();
}

glm::mat4 RenderableMeshComponent::CalculateModelMatrix()
{
	glm::mat4 transMatrix = glm::translate(glm::mat4(1), GetOwner()->GetPosition());
	glm::mat4 inverseTransMatrix = glm::inverse(transMatrix);

	glm::mat4 rotMatrix = transMatrix * glm::mat4_cast(GetOwner()->GetRotation()) * inverseTransMatrix;

	glm::mat4 model = glm::mat4(1);
	model = glm::scale(model, GetOwner()->GetScale()) * rotMatrix * glm::translate(model, GetOwner()->GetPosition());

	return model;
}

void RenderableMeshComponent::SetUniforms()
{
	m_modelUniform = m_shader.GetUniformLocation("model");
    m_viewUniform = m_shader.GetUniformLocation("view");

    glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 100.0f);
    GLint uniProj = m_shader.GetUniformLocation("proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(m_shader.GetUniformLocation("textureSprite"), 0);
}

bool RenderableMeshComponent::LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData)
{
	// Load model
	std::vector<Vector3> tempVertices;
	std::vector<Vector2> tempUVs;
	std::vector<Vector3> tempNormals;

	// Try to load model
	if(!LoadOBJ(modelPath + in_fileName, tempVertices, tempUVs, tempNormals))
	{
		std::cout << "Attempting to load default mesh" << std::endl;
		if(!LoadOBJ(modelPath + defaultModel, tempVertices, tempUVs, tempNormals))
			return false;
	}

	// Format the data
	ConstructVertexData(out_vertexData, tempVertices, tempUVs, tempNormals);

	// Set draw count
	m_vao.SetNumVertices(tempVertices.size());

	return true;
}

void RenderableMeshComponent::Update(float in_dt)
{
	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, -0.0001f, 0.f));
		mOwner->SetScale(mOwner->GetScale() + Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.0f, 0.0001f, 0.f));
		mOwner->SetScale(mOwner->GetScale() - Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_Z) == GLFW_PRESS)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(-0.01f, 0.f, 0.f));
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 0, 1)));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.01f, 0.f, 0.f));

		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 1, 0)));
	}

	//GetOwner()->m_rotationQuat = glm::rotate(GetOwner()->m_rotationQuat, in_dt * 50, Vector3(0, 1, 0));
}

void RenderableMeshComponent::Draw()
{
	// Bind shader program
	m_shader.Use();

	// Set shader uniforms
    glUniformMatrix4fv(m_modelUniform, 1, GL_FALSE, glm::value_ptr(CalculateModelMatrix()));

	if(GetOwner()->GetCameraManager()->GetActiveCamera()->HasViewMatrixChanged())
	{
		glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, glm::value_ptr(GetOwner()->GetCameraManager()->GetActiveCamera()->GetViewMatrix()));
	}

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *(m_textureData.textureID));

	// Bind vertex array
	m_vao.Bind();
}