#include "../Structure/Window.h"

#include "../Application/Application.h"

#include <iostream>

namespace
{
	static void ErrorCallback(int in_error, const char* in_description)
	{
		std::cout<< "GLFW ERROR: " << in_description << std::endl;
	}

	static void WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* theWindow = Application::GetApplication()->GetWindow();
		theWindow->SetDimensions(Vector2(width, height));
		Application::GetApplication()->GetWindow()->SetSpriteScaler();
	}

	GLFWwindow* InitialiseWindow(const char* in_title, Vector2 in_dimensions)
	{
		if (!glfwInit())
			return NULL;
        
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(in_dimensions.x, in_dimensions.y, in_title, NULL, NULL);
		glfwSetWindowSizeCallback(window, WindowResizeCallback);
        
		if(!window)
		{
			glfwTerminate();
			return NULL;
		}
  
		glfwMakeContextCurrent(window);

		glViewport(0, 0, in_dimensions.x, in_dimensions.y);

		glewExperimental = GL_TRUE;
		glewInit();

		glEnable(GL_DEPTH_TEST);

		glfwSetErrorCallback(ErrorCallback);

		return window;
	}
}

Window::Window(const char* in_name, int in_width, int in_height) :
m_dimensions(in_width, in_height),
m_spriteScaler(0.f, 0.f)
{
	m_window = InitialiseWindow(in_name, Vector2(in_width, in_height));
	SetSpriteScaler();
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::ShouldWindowClose() const
{
	bool result = glfwWindowShouldClose(m_window);
	return result;
}

void Window::SetSpriteScaler()
{
	m_spriteScaler = Vector2(2.f / m_dimensions.x, 2.f / m_dimensions.y);
}