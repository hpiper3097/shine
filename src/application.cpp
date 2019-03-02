#include "../include/application.h"
#include <iostream>

Application::Application(const unsigned int w, const unsigned int h)
//	: window((*void), std::default_delete<(*void)> //default initializer;
{
	SCR_WIDTH = w;
	SCR_HEIGHT = h;
	init();
}

Application::~Application()
{
	window.release();
	kill();
}

GLFWwindow* Application::Window()
{
	return window.get();
}

void Application::init()
{
//	ASSERT(glfwInit() == GL_TRUE); GLFW = true;
	if(!glfwInit())
		std::cerr << "GLFW failed to initialize!" << std::endl;
	GLFW = true;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version (major)3.(minor)3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //explicitly using core

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window.reset(glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW OpenGL Test", nullptr, nullptr)); //window creation
//	ASSERT(window.get() != nullptr);
	if(window.get() == nullptr)
		std::cerr << "Window creation failed!" << std::endl;
	glfwMakeContextCurrent(window.get());
	glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback); //register callbacks after window creation and before gameloop

//	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)); GLAD = true;//load glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Glad failed to initialize!" << std::endl;
	GLAD = true;
}

void Application::kill()
{
	glfwTerminate();
	GLFW = false;
	GLAD = false;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int height, int width)
{
	glViewport(0, 0, height, width);
}

