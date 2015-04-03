#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/SpriteComponent.h"
#include "../Rendering/RenderSystem.h"

#include "../Structure/GameObject.h"

#include "../Rendering/Texture.h"

#include <iostream>

const GLfloat SPRITE_VERTICES[] = 
{	// position					//texcoords
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,

	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f
};

const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderDefault.txt";
const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderDefault.txt";

SpriteComponent::SpriteComponent(const std::string in_texture) :
IRenderableComponent(),
m_width(0),
m_height(0),
m_uvs(glm::vec2(0)),
m_textureName(in_texture)
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);
}

SpriteComponent::~SpriteComponent()
{
	m_vao.Destroy();
}

void SpriteComponent::Initialise()
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());

	m_vertexBuffer->Bind();
	m_vertexBuffer->SetData(sizeof(SPRITE_VERTICES), SPRITE_VERTICES);
}

void SpriteComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
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
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("position"), 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0) );
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat))) );

	m_vao.SetVertexAttributes();

	// Add the uniforms
	AddUniforms();

	m_shader["textureSprite"]->Set(0);
}

void SpriteComponent::AddUniforms()
{
	m_shader.AddUniform("model");
	m_shader.AddUniform("uv");
	m_shader.AddUniform("textureSprite");
}

void SpriteComponent::OnAttached(GameObject* in_gameObject)
{
	IRenderableComponent::OnAttached(in_gameObject);

	SetTextureManager(in_gameObject->GetRenderSystem()->GetTextureManager());
	SetTextures(m_textureName.c_str());

	in_gameObject->GetRenderSystem()->GetSpriteBatcher()->AddSprite(this, m_textureName);
}

void SpriteComponent::OnDetached(GameObject* in_gameObject)
{
	// Fill this out with logic for anything sprite-specific that needs to be done
	IRenderableComponent::OnDetached(in_gameObject);
}

glm::mat4 SpriteComponent::CalculateModelMatrix()
{
	glm::mat4 model(1.f);
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->GetScale());
	return model;
}

void SpriteComponent::Update(float in_dt)
{

}


/* TODO
Right now Sprites are being drawn as a square in the actual world. They should
instead be drawn last of all on top of everything else, so objects in the world
can't slice through them. This is done by disabling depth testing before drawing any sprites.

Obviously this would be needlessly expensive if meshes and sprites were mixed
up in the rendering order, so all sprites should be drawn last, in a batch.
*/
void SpriteComponent::Draw()
{
	// Bind shader program
	//m_shader.Use();

	// Set shader uniforms
	m_shader["model"]->SetMatrix(CalculateModelMatrix(), 1, GL_FALSE);
	m_shader["uv"]->SetVec(GetUVs(), 1);

	/*if(m_texture != NULL)
	{
		// Bind the texture
		m_texture->Activate(GL_TEXTURE0);
		m_texture->Bind();
	}

	// Bind vertex array
	m_vao.Bind();*/
}