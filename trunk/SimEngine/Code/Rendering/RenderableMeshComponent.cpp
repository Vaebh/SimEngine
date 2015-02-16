#include "../Rendering/RenderableMeshComponent.h"

#include "../Application/Application.h"

#include "../Camera/CameraManager.h"
#include "../Events/EventMessenger.h"
#include "../OpenGL/GLUtils.h"
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

RenderableMeshComponent::RenderableMeshComponent(const char* in_meshName, const char* in_textureName) :
IRenderableComponent()
{
	m_textureData = LoadImage(in_textureName);

	Initialise(in_meshName);
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	MessageDelegate mesDel = new EventCallbackMember<RenderableMeshComponent>(this, &RenderableMeshComponent::HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_A_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_S_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_Z_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_X_PRESS, NULL, mesDel);

	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_0_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_1_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_2_PRESS, NULL, mesDel);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_3_PRESS, NULL, mesDel);
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
	glm::mat4 transMatrix = glm::translate(glm::mat4(1), GetOwner()->GetPosition());
	glm::mat4 inverseTransMatrix = glm::inverse(transMatrix);

	glm::mat4 rotMatrix = glm::mat4_cast(GetOwner()->GetRotation());

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, GetOwner()->GetPosition()) * rotMatrix * glm::scale(model, GetOwner()->GetScale()) ;

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
	/*if(glfwGetKey(GetOwner()->GetInputManager()get ->mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		//m_owner->SetPosition(m_owner->GetPosition() + Vector3(0.0f, -0.0001f, 0.f));
		m_owner->SetScale(m_owner->GetScale() + Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		//m_owner->SetPosition(m_owner->GetPosition() + Vector3(0.0f, 0.0001f, 0.f));
		m_owner->SetScale(m_owner->GetScale() - Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_Z) == GLFW_PRESS)
	{
		//m_owner->SetPosition(m_owner->GetPosition() + Vector3(-0.01f, 0.f, 0.f));
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 0, 1)));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		//m_owner->SetPosition(m_owner->GetPosition() + Vector3(0.01f, 0.f, 0.f));

		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), in_dt * 50, Vector3(0, 1, 0)));
	}*/

	//GetOwner()->m_rotationQuat = glm::rotate(GetOwner()->m_rotationQuat, in_dt * 50, Vector3(0, 1, 0));
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

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *(m_textureData.textureID));

	// Bind vertex array
	m_vao.Bind();
}


// Need to expose delta time somewhere other than in Update
void RenderableMeshComponent::HandleEvent(uint32_t in_eventType, GameObject* in_target)
{
	if(in_eventType == INPUT_A_PRESS)
	{
		m_owner->SetScale(m_owner->GetScale() + Vector3(0.00001f, 0.00001f, 0.00001f));
	}

	if(in_eventType == INPUT_S_PRESS)
	{
		m_owner->SetScale(m_owner->GetScale() - Vector3(0.00001f, 0.00001f, 0.00001f));
		//m_owner->MovePosition(Vector3(0.001f, 0.f, 0.f));
	}

	if(in_eventType == INPUT_Z_PRESS)
	{
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), Application::GetApplication()->GetDeltaTime() * 100.f, Vector3(0, 0, 1)));
	}

	if(in_eventType == INPUT_X_PRESS)
	{
		GetOwner()->SetRotation(glm::rotate(GetOwner()->GetRotation(), Application::GetApplication()->GetDeltaTime() * 100.f, Vector3(0, 1, 0)));
	}

	if(in_eventType == INPUT_0_PRESS)
	{
		m_owner->MovePosition(Vector3(0.001f, 0.f, 0.f));
	}

	if(in_eventType == INPUT_1_PRESS)
	{
		m_owner->MovePosition(Vector3(-0.001f, 0.f, 0.f));
	}

	float zoomSpeed = 0.01f;

	if(in_eventType == INPUT_2_PRESS)
	{
		Camera* const curCam = GetOwner()->GetCameraManager()->GetActiveCamera();
		Vector3 dir = glm::normalize(curCam->GetTarget() - curCam->GetPosition());

		curCam->SetPosition(curCam->GetPosition() + -dir * zoomSpeed);
		curCam->SetTarget(curCam->GetTarget() + -dir * zoomSpeed);
	}

	if(in_eventType == INPUT_3_PRESS)
	{
		Camera* const curCam = GetOwner()->GetCameraManager()->GetActiveCamera();
		Vector3 dir = glm::normalize(curCam->GetTarget() - curCam->GetPosition());

		curCam->SetPosition(curCam->GetPosition() + dir * zoomSpeed);
		curCam->SetTarget(curCam->GetTarget() + dir * zoomSpeed);
	}
}