#include "../Rendering/RenderableMeshComponent.h"

#include "../Application/Application.h"

#include "../Camera/CameraManager.h"
#include "../Events/EventMessenger.h"
#include "../Input/InputManager.h"
#include "../Utils/ModelLoader.h"

#include "../Rendering/Texture.h"


#include <iostream>

namespace
{
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/3DVertexShader.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/3DFragShader.txt";

	const std::string modelPath = "../SimEngine/Assets/Models/";
	const char* defaultModel = "cube.obj";
}

RenderableMeshComponent::RenderableMeshComponent(const char* in_meshName) :
IRenderableComponent()
{
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

	// Add the uniforms
	AddUniforms();

	// Set some initial uniform values
	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 10.0f);
	m_shader["proj"]->SetMatrix(proj, 1, GL_FALSE);

	m_shader["textureSprite"]->Set(0);
}

glm::mat4 RenderableMeshComponent::CalculateModelMatrix()
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::mat4_cast(GetOwner()->GetRotation()) * glm::scale(model, GetOwner()->GetScale()) ;

	return model;
}

void RenderableMeshComponent::AddUniforms()
{
	m_shader.AddUniform("model");
	m_shader.AddUniform("view");
	m_shader.AddUniform("proj");
	m_shader.AddUniform("textureSprite");
}

bool RenderableMeshComponent::LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData)
{
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
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_A))
	{
		m_owner->SetScale(m_owner->GetScale() + Vector3(0.00001f, 0.00001f, 0.00001f));
	}
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_S))
	{
		m_owner->SetScale(m_owner->GetScale() - Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_Z))
	{
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 100.f, Vector3(0, 0, 1)));
	}
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_X))
	{
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 100.f, Vector3(0, 1, 0)));
	}

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_1))
	{
		m_owner->MovePosition(Vector3(0.001f, 0.f, 0.f));
	}
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_2))
	{
		m_owner->MovePosition(Vector3(-0.001f, 0.f, 0.f));
	}

	float zoomSpeed = 0.01f;

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_3))
	{
		Camera* const curCam = GetOwner()->GetCameraManager()->GetActiveCamera();
		Vector3 dir = glm::normalize(curCam->GetTarget() - curCam->GetPosition());

		curCam->SetPosition(curCam->GetPosition() + -dir * zoomSpeed);
		curCam->SetTarget(curCam->GetTarget() + -dir * zoomSpeed);
	}
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_4))
	{
		Camera* const curCam = GetOwner()->GetCameraManager()->GetActiveCamera();
		Vector3 dir = glm::normalize(curCam->GetTarget() - curCam->GetPosition());

		curCam->SetPosition(curCam->GetPosition() + dir * zoomSpeed);
		curCam->SetTarget(curCam->GetTarget() + dir * zoomSpeed);
	}

	GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 1, 0)));
}

void RenderableMeshComponent::Draw()
{
	// Bind shader program
	m_shader.Use();

	// Set shader uniforms
	m_shader["model"]->SetMatrix(CalculateModelMatrix(), 1, GL_FALSE);

	const Camera* const curCam = GetOwner()->GetCameraManager()->GetActiveCamera();
	if(curCam->HasViewMatrixChanged())
	{
		m_shader["view"]->SetMatrix(curCam->GetViewMatrix(), 1, GL_FALSE);
	}

	if(m_texture != NULL)
	{
		// Bind the texture
		m_texture->Activate(GL_TEXTURE0);
		m_texture->Bind();
	}

	// Bind vertex array
	m_vao.Bind();
}