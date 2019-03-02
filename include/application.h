#pragma once

#ifndef APPICATION_H
#define APPLICATION_H

#include <header.h>

/*static auto delWindow = [](GLFWwindow* window) //const to provoke internal linkage
{
	glfwDestroyWindow(window);
};*/ // can't use lambdas in header files, must have a static namespace
//we'll use a struct and static method instead

struct delWindowFunctor {
	void operator()(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}
};

class Application
{
private:
	std::unique_ptr<GLFWwindow, delWindowFunctor> window;
	int SCR_WIDTH = 0, SCR_HEIGHT = 0;

	bool GLFW = false, GLAD = false;

	void init();
	void kill();
	static void framebuffer_size_callback(GLFWwindow* window, int height, int width);
public:
	Application(const unsigned int w,const unsigned int h);

	~Application();

	GLFWwindow* Window();
};

#endif
