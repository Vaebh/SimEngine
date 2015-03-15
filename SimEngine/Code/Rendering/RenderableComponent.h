#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

class Buffer;
class Texture;
class TextureManager;

#include "../Structure/Component.h"
#include "../Rendering/Shader.h"
#include "../Rendering/VertexArray.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	virtual ~IRenderableComponent();

	virtual void Update(float in_dt) = 0;
	virtual void Draw() = 0;

	virtual glm::mat4 CalculateModelMatrix() = 0;

	inline Shader& GetShader() {return m_shader;}

	inline VertexArray& GetVAO() {return m_vao;}

	inline void SetTextureManager(TextureManager* in_texManager) {m_texManager = in_texManager;}
	void SetTextures(const char* in_texName1, const char* in_texName2 = "", const char* in_texName3 = "", const char* in_texName4 = "");

	inline bool IsVisible() const {return m_visible;}
	inline void SetVisible(bool in_isVisible) {m_visible = in_isVisible;}

protected:
	virtual void AddUniforms() = 0;

protected:
	VertexArray m_vao;
	Buffer* m_vertexBuffer;

	Shader m_shader;

	// TODO - Expand to support a set number of textures
	Texture* m_texture;
	TextureManager* m_texManager;

	bool m_visible;
};

#endif