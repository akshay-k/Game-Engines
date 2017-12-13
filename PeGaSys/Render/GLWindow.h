#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


extern void framebuffer_size_callback(GLFWwindow * window, int width, int height);

#ifndef WINDOW_H
#define WINDOW_H
class GLWindow
{
public:
	GLWindow(bool isFullScreen = false);
	~GLWindow();

	int Create(const char * name, const int width, const int height);
	GLFWwindow * GetWindow();

	bool WindowShouldClose();

	void ProcessInput();
	void Update();

	void CloseWindow();

	
private:
	GLFWwindow * mWindow;
	bool mFullScreen;

};



#endif