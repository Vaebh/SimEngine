#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/Test3DComponent.h"
#include "../Rendering/RenderSystem.h"

#include <ctime>

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

Test3DComponent::Test3DComponent() :
IRenderableComponent()
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	mTextureData = LoadImage("bros.png");
}

Test3DComponent::~Test3DComponent()
{
	// TODO - Make some kind of sprite managery class, maybe SpriteBatch, and have it store and bind the vao and vbo as they're the same for every sprite
	// Also maybe use the same shader program for all sprites
    //glDeleteBuffers(1, &mVbo);
    //glDeleteVertexArrays(1, &mVao);
}

void Test3DComponent::Initialise()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Test3DComponent::SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc)
{
	if(inVertexShaderSrc.empty() || inFragShaderSrc.empty())
		return;

	m_shader.CreateShaderProgram(inVertexShaderSrc, inFragShaderSrc);

	glUseProgram(m_shader.GetProgramID());

	glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	GLint posAttrib = glGetAttribLocation(m_shader.GetProgramID(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(m_shader.GetProgramID(), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	/*GLint posAttrib = glGetAttribLocation(m_shader.GetProgramID(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);*/
                     
	/*GLint texAttrib = glGetAttribLocation(m_shader.GetProgramID(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(4*sizeof(float)));*/

	glUniform1i(glGetUniformLocation(m_shader.GetProgramID(), "textureSprite"), 0);

	mMoveUniform = glGetUniformLocation(m_shader.GetProgramID(), "move");

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

glm::mat4 Test3DComponent::CalculateMatrix()
{
	//glm::mat4 model;
	//model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->m_scale) * glm::rotate(model, GetOwner()->mRotationAngle.x, X_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.y, Y_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.z, Z_UNIT_POSITIVE);

	// Calculate transformation
	/*glm::mat4 model;
	model = glm::rotate(
		model,
		(GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 180.0f,
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(model));*/

	//glm::mat4 rotMatrix = glm::mat4_cast(GetOwner()->m_rotationQuat);

	glm::mat4 identityMat = glm::mat4(1.0f);
	glm::mat4 rotMatrix = glm::mat4_cast(GetOwner()->m_rotationQuat);
	glm::mat4 transMatrix = glm::translate(identityMat, GetOwner()->GetPosition());
	glm::mat4 viewMatrix = rotMatrix * glm::inverse(transMatrix);

	//glm::rotate(GetOwner()->m_rotationQuat, 90.f, Vector3(0, 1, 0));

	glm::mat4 model;
	model = glm::scale(model, GetOwner()->m_scale) * rotMatrix * glm::translate(model, GetOwner()->GetPosition());

	return model;
}

void Test3DComponent::Update(float in_dt)
{
	//mAnimTimer += in_dt;
	//IRenderableComponent::Update(in_dt);

	Vector3 camDir = m_camCenter - m_camLookat;

	camDir = glm::normalize(camDir);

	//std::cout << "x: " <<  mOwner->GetPosition().x << std::endl;
	//std::cout << "y: " << mOwner->GetPosition().y << std::endl;
	//std::cout << "z: " << mOwner->GetPosition().z << std::endl;


	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_camCenter = m_camCenter + camDir * 0.05f;
		//m_camLookat = m_camLookat + camDir * 0.05f;

		std::cout << "camx: " <<  m_camCenter.x << std::endl;
		std::cout << "camy: " << m_camCenter.y << std::endl;
		std::cout << "camz: " << m_camCenter.z << std::endl;
		mOwner->SetPosition(mOwner->GetPosition() + camDir * 0.05f);

		// Set up projection
		glm::mat4 view = glm::lookAt(
			m_camLookat,
			m_camCenter,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		GLint uniView = glGetUniformLocation(m_shader.GetProgramID(), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_camCenter = m_camCenter - camDir * 0.05f;
		//m_camLookat = m_camLookat - camDir * 0.05f;

		mOwner->SetPosition(mOwner->GetPosition() + camDir * -0.05f);

		// Set up projection
		glm::mat4 view = glm::lookAt(
			m_camLookat,
			m_camCenter,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		GLint uniView = glGetUniformLocation(m_shader.GetProgramID(), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	}

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

	static bool thing = false;
	static float angle = 10.f;

	static float scale = 1.0f;

	static bool thing2 = false;

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(0.01f, 0.f, 0.f));
		//if(!thing)
			//GetOwner()->m_rotationQuat = glm::rotate(GetOwner()->m_rotationQuat, angle, Vector3(0, 1, 0));
		

		thing = true;
	}

	if(thing && glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_RELEASE)
	{
		thing = false;
		//angle += 10.0f;

		scale += 0.1f;

		GetOwner()->m_scale.x = scale;
		GetOwner()->m_scale.y = scale;
		GetOwner()->m_scale.z = scale;
	}

	if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		thing2 = true;
	if(thing2 && glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		thing2 = false;

		scale -= 0.1f;
	}

	GetOwner()->m_scale.x = scale;
	GetOwner()->m_scale.y = scale;
	GetOwner()->m_scale.z = scale;


	GetOwner()->m_rotationQuat = glm::rotate(GetOwner()->m_rotationQuat, in_dt * 50, Vector3(0, 1, 0));
}

void Test3DComponent::Draw()
{
    glBindTexture(GL_TEXTURE_2D, *(mTextureData.textureID));

	// Calculate transformation
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(CalculateMatrix()));
}