#include "GLWindow.h"
#include <iostream>
#include <assert.h>

GLWindow::GLWindow(bool isFullScreen)
{
	mFullScreen = isFullScreen;
}


int GLWindow::Create(const char * name, const int width, const int height)
{
	// initializes GLFW
	glfwInit();

	// configures window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	assert(name != NULL);

	if (mFullScreen) { // TODO: add monitor field (in a Target class?)
		mWindow = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
	}
	else {
		mWindow = glfwCreateWindow(width, height, name, NULL, NULL);
	}

	if (mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window '" << name << "'" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);


	return 1;
}


GLFWwindow* GLWindow::GetWindow()
{
	return mWindow;
}

bool GLWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(mWindow);
}

GLWindow::~GLWindow()
{
}

// TODO: merge w/ input library
void GLWindow::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
}

void GLWindow::Update()
{
	glfwSwapBuffers(mWindow);	// swaps color buffer and updates window
	glfwPollEvents();
}

void GLWindow::CloseWindow()
{
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}


