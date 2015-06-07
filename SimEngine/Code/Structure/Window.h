#ifndef WINDOW_SIMENGINE
#define WINDOW_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Structure/Vectors.h"

class Window
{
public:
	Window(const char* in_name, int in_width, int in_height);
	~Window();

	inline const Vector2 GetDimensions() {return m_dimensions;}
	inline void SetDimensions(Vector2 in_dimensions) { m_dimensions = in_dimensions; }

	inline const Vector2 GetSpriteScaler() { return m_spriteScaler; }
	void SetSpriteScaler();

	GLFWwindow* GetGLFWWindow() {return m_window;}

	bool ShouldWindowClose() const;

private:
	GLFWwindow* m_window;

	Vector2 m_dimensions;
	Vector2 m_spriteScaler;
};

#endif