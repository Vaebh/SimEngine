#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

class Buffer;
class Image;
class Texture;
class TextureManager;

#include "../Foundation/Foundation.h"

#include "../Structure/Component.h"

#include "../Rendering/Shader.h"
#include "../Rendering/VertexArray.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	virtual ~IRenderableComponent();

	virtual void Update(float in_dt) = 0;
	virtual void PreDraw();
	virtual void Draw() = 0;

	inline VertexArray& GetVAO() {return m_vao;}
	inline Shader* GetShader() {return &m_shader;}

	inline void SetTextureManager(TextureManager* in_texManager) {m_texManager = in_texManager;}
	Image* RequestImage(const char* in_imgName);
	std::vector<Image*> RequestImages(uint32_t in_numArgs, ...);

	inline bool IsVisible() const {return m_visible;}
	inline void SetVisible(bool in_isVisible) {m_visible = in_isVisible;}

protected:
	virtual void Initialise() = 0;
	virtual void SetVertexData() = 0;
	virtual void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc) = 0;

	virtual glm::mat4 CalculateModelMatrix() = 0;

protected:
	VertexArray m_vao;
	Buffer* m_vertexBuffer;

	Shader m_shader;

	// NOOOOOO Meshes don't need multiple images only sprites dooooooo
	Texture* m_texture;
	TextureManager* m_texManager;

	bool m_visible;
};

#endif