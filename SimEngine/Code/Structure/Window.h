#ifndef WINDOW_SIMENGINE
#define WINDOW_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Structure/Vectors.h"

class Window
{
public:
	Window(int in_width, int in_height);

	inline const Vector2 GetDimensions() {return m_dimensions;}

	inline const GLFWwindow* GetWindow() {return m_window;}

private:
	GLFWwindow* m_window;
	GLFWwindow* InitialiseWindow();

	Vector2 m_dimensions;
};

#endif