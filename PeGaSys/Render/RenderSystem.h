#pragma once
#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "GLWindow.h"
#include <string>
#include "Camera.h"

class RenderSystem
{
public:
	RenderSystem(std::string name,
		const unsigned int scrWidth = 800,
		const unsigned int scrHeight = 600) : mWindowName(name), mScreenWidth(scrWidth), mScreenHeight(scrHeight) {};
	~RenderSystem();

	// initializes glad, enables depth buffer, creates window
	GLWindow Initialize();
	void ProcessInput();
	void ClearBuffers(Math3D::Vector4 clearColor = Math3D::Vector4(0.2f, 0.3f, 0.3f, 1.0f));




	// Getters and Setters
	void SetWindow(GLWindow &win) { mWindow = win; }
	GLWindow GetWindow() const { return mWindow; }

// -------------------------------------------------
	void Demo();
// -------------------------------------------------
protected:
	void InitializeGlad();


private:
	const unsigned int mScreenWidth;
	const unsigned int mScreenHeight;


	GLWindow mWindow;
	std::string mWindowName;

	SceneNodeBase mRootSceneNode;
	Camera mCamera;


	void processInput(GLFWwindow * window, Camera & camera); // helper for demo
};

#endif // !RENDER_SYSTEM_H