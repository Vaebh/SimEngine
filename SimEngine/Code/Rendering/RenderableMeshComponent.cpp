#include "../Rendering/RenderableMeshComponent.h"

#include "../Application/Application.h"

#include "../Camera/CameraManager.h"
#include "../Events/EventMessenger.h"
#include "../Input/InputManager.h"
#include "../Utils/ModelLoader.h"

#include "../Rendering/Texture.h"
#include "../Rendering/RenderSystem.h"

#include "../Structure/GameObject.h"

#include <iostream>

namespace
{
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/3DVertexShaderNormals.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/3DFragShaderNormals.txt";

	const std::string modelPath = "../SimEngine/Assets/Models/";
	const char* defaultModel = "cube.bin";
}

RenderableMeshComponent::RenderableMeshComponent(const char* in_meshName, const char* in_textureName) :
IRenderableComponent(),
m_meshName(in_meshName),
m_textureName(in_textureName),
m_lightPos(VECTOR3_ZERO)
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);
}

RenderableMeshComponent::~RenderableMeshComponent()
{
	m_vao.Destroy();
}

void RenderableMeshComponent::Initialise()
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());

	m_vertexBuffer->Bind();
	SetVertexData();
}

void RenderableMeshComponent::SetVertexData()
{
	std::vector<GLfloat> vertexData;
	assert(LoadModel(m_meshName.c_str(), vertexData));

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
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0) );
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))) );
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))) );

	m_vao.SetVertexAttributes();

	// Add the uniforms
	AddUniforms();

	// Set some initial uniform values
	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 10.0f);
	m_shader["proj"]->SetMatrix(proj, 1, GL_FALSE);

	m_shader["textureSprite"]->Set(0);
}

void RenderableMeshComponent::AddUniforms()
{
	m_shader.AddUniform("model");
	m_shader.AddUniform("view");
	m_shader.AddUniform("proj");
	m_shader.AddUniform("textureSprite");
	m_shader.AddUniform("lightPos");
}

bool RenderableMeshComponent::LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData)
{
	int numVerts = 0;
	std::string fileName = modelPath + in_fileName;

	if(!LoadVertexData(fileName.c_str(), out_vertexData, numVerts))
	{
		// Clear vertices in case of partially loaded data
		out_vertexData.clear();

		// Try to load default model
		if(!LoadVertexData((modelPath + defaultModel).c_str(), out_vertexData, numVerts))
			return false;
	}

	// Set draw count
	m_vao.SetNumVertices(numVerts);

	return true;
}

void RenderableMeshComponent::OnAttached(GameObject* in_gameObject)
{
	IRenderableComponent::OnAttached(in_gameObject);

	SetTextureManager(in_gameObject->GetRenderSystem()->GetTextureManager());
	//SetTextures(m_textureName.c_str());

	in_gameObject->GetRenderSystem()->AddComponent(this);
}

void RenderableMeshComponent::OnDetached(GameObject* in_gameObject)
{
	// Fill this out with logic for anything sprite-specific that needs to be done
	IRenderableComponent::OnDetached(in_gameObject);
}

glm::mat4 RenderableMeshComponent::CalculateModelMatrix()
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::mat4_cast(GetOwner()->GetRotation()) * glm::scale(model, GetOwner()->GetScale()) ;

	return model;
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

	///GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 1, 0)));

	float lightSpeed = 0.001f;

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_5))
		m_lightPos += Vector3(lightSpeed, 0.f, 0.f);
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_6))
		m_lightPos += Vector3(-lightSpeed, 0.f, 0.f);

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_7))
		m_lightPos += Vector3(0.f, lightSpeed, 0.f);
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_8))
		m_lightPos += Vector3(0.f, -lightSpeed, 0.f);

	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_Q))
		m_lightPos += Vector3(0.f, 0.f, lightSpeed);
	if(GetOwner()->GetInputManager()->IsKeyDown(GLFW_KEY_W))
		m_lightPos += Vector3(0.f, 0.f, -lightSpeed);

	glUseProgram(m_shader.GetProgramID());
	m_shader["lightPos"]->SetVec(m_lightPos, 1);
	glUseProgram(0);
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