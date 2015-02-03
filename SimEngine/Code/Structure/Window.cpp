#include "../Structure/Window.h"

Window::Window(int in_width, int in_height) :
m_dimensions(in_width, in_height)
{

}

//namespace
//{
	GLFWwindow* Window::InitialiseWindow()
	{
		if (!glfwInit())
			return NULL;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(m_dimensions.x, m_dimensions.y, "Breakout Clone", NULL, NULL);
        
		if(!window)
		{
			glfwTerminate();
            return NULL;
		}
  
		glfwMakeContextCurrent(window);

		glViewport(0, 0, m_dimensions.x, m_dimensions.y);

		glewExperimental = GL_TRUE;
		glewInit();

		glEnable(GL_DEPTH_TEST);

		return window;
	}
//}