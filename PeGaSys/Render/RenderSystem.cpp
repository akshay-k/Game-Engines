#include "RenderSystem.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <assert.h>

#include "Shader.h"
#include "../Math/Matrix44.h"
#include "../Math/Vector4.h"
#include "Texture.h"
#include "TextureSampler.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "CubeVertices.h"



RenderSystem::~RenderSystem()
{
}

GLWindow RenderSystem::Initialize()
{
	mWindow = GLWindow();
	//assert(mWindowName != NULL);
	mWindow.Create(mWindowName.c_str(), mScreenWidth, mScreenHeight);
	InitializeGlad();

	glEnable(GL_DEPTH_TEST);
	return mWindow;
}

void RenderSystem::ProcessInput()
{
	mWindow.ProcessInput();
}

void RenderSystem::ClearBuffers(Math3D::Vector4 clearColor)
{
	glClearColor(clearColor.getX(), clearColor.getY(), clearColor.getZ(), clearColor.getW());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::InitializeGlad()
{
	// GLAD manages function pointers for OpenGL so need to initialize before running any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void RenderSystem::Demo()
{


	//*
	// WINDOW CREATION
	// --------------------------------------------
	GLWindow win = GLWindow();
	win.Create("Tanks!", mScreenWidth, mScreenHeight);

	// GLAD: LOAD ALL OPENGL POINTERS
	// --------------------------------------------
	// GLAD manages function pointers for OpenGL so need to initialize before running any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//*/
	//RenderSystem system = RenderSystem("Tanks!");

	glEnable(GL_DEPTH_TEST);

	// TRANSFORMATION MATRICES
	// --------------------------------------------
	Math3D::Matrix44 model = Math3D::Matrix44();

	Math3D::Matrix44 identity = Math3D::Matrix44();

	Math3D::Matrix44 groundmodel = Math3D::Matrix44();
	groundmodel.SetRotationX(Math3D::Matrix44::degreesToRadians(-85.0f));



	// CAMERA
	// --------------------------------------------
	Camera camera = Camera();
	camera.SetEye(Math3D::Vector4(1.0f, 0.0f, 3.0f));
	camera.SetLookAt(Math3D::Vector4(0.0f, 0.0f, -1.0f));
	camera.SetUpApproximate(Math3D::Vector4(0.0f, 0.1f, 0.0f));

	camera.SetFieldOfViewVert(Math3D::Matrix44::degreesToRadians(45.0f));
	camera.SetAspectRatio((float)mScreenWidth / (float)mScreenHeight);
	camera.SetClipDepths(0.1f, 100.0f);


	// GROUND OBJECT

	// 1. create shader
	std::string shaderDir = "../Render/Shaders/";
	std::string shaderFile = shaderDir + "PositionColor";
	std::string vsPath = shaderFile + ".vs";
	std::string fsPath = shaderFile + ".fs";
	Shader sground = Shader(vsPath.c_str(), fsPath.c_str());




	float groundvertices[] = {
		// position			// color (r g b)
		5.5f,  5.5f, 0.0f,   1.0f, 0.0f, 0.0f,// top right
		5.5f, 5.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
		5.5f, 5.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
		5.5f,  5.5f, 0.0f,  1.0f, 1.0f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	// 2. generate buffers
	VertexArray vaog = VertexArray();
	VertexBuffer vbg = VertexBuffer(sground);
	IndexBuffer ibog = IndexBuffer();


	// 3. bind vao and load data 
	vaog.Bind();
	vbg.LoadData(groundvertices, 24, 6 * sizeof(float),
		(void*)0, (void*)(3 * sizeof(float)), (void*)(3 * sizeof(float)));
	ibog.LoadData(indices, 6);
	vaog.SetIndexBuffer(ibog);
	vbg.ConfigureCommonAttributes();

	sground.Use();
	sground.SetMat4("model", groundmodel.convertToFloatArray());
	sground.SetMat4("projection", camera.ProjectionMatrix().convertToFloatArray());
	vaog.Unbind();
	glUseProgram(0);

	// SHADERS
	// --------------------------------------------
	//*

	shaderFile = shaderDir + "PositionTexture";
	vsPath = shaderFile + ".vs";
	fsPath = shaderFile + ".fs";
	Shader s = Shader(vsPath.c_str(), fsPath.c_str());
	//*/


	VertexArray vao = VertexArray();
	IndexBuffer ibo = IndexBuffer();
	VertexBuffer vb = VertexBuffer(s);



	vao.Bind();
	//*
	vb.LoadData(CUBE_VERTICES, NUM_VERTICES, 5 * sizeof(float),
		(void*)0, (void*)(3 * sizeof(float)), (void*)(3 * sizeof(float)));
	//vb.LoadData(vertices, 32); // testing GenericVertex struct (didn't work)
	//*/

	std::cout << "cube vb" << vb.GetName() << std::endl;
	std::cout << "ground vb" << vbg.GetName() << std::endl;
	//ibo.LoadData(indices, 6);
	//vao.SetIndexBuffer(ibo);
	//*
	vb.ConfigureCommonAttributes();

	// TEXTURES
	// --------------------------------------------
	//*
	Texture *tex1 = &Texture();
	unsigned int texture = tex1->GetTextureName();
	tex1->OpenGLBind();
	Image *wall = &Image("../Render/TextureImages/wall.jpg");

	// configure texture settings
	SamplerState *texState = &SamplerState();
	texState->mAddressU = SamplerState::ADDRESS_MIRROR;
	texState->mAddressV = SamplerState::ADDRESS_MIRROR;
	texState->mMipFilter = SamplerState::FILTER_LINEAR;
	texState->mMinFilter = SamplerState::FILTER_LINEAR;
	texState->mMagFilter = SamplerState::FILTER_LINEAR;
	TextureSampler::SamplerState_Apply(*texState);

	tex1->Create2DTextureFromImage(wall);
	wall->FreeImageData();
	//*/
	//*
	s.Use(); // don't forget to activate/use the shader before setting uniforms!
	s.SetInt("texture", 0);
	s.SetMat4("projection", camera.ProjectionMatrix().convertToFloatArray());
	//*/
	vao.Unbind();
	glUseProgram(0);

	// create while loop because we don't want OpenGL to render once then quit
	// we want it to continue rendering until we tell it to stop
	// simple version of render loop:
	while (!win.WindowShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// INPUT
		// -------
		win.ProcessInput();
		processInput(win.GetWindow(), camera);

		// RENDER
		// -------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// sets color to clear the screen with
												// sets state
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// clears the screen
																	// uses state (retrieves clearing color from current state)
		//glEnable(GL_TEXTURE_2D);
		s.Use();
		vao.Bind();
		tex1->ActivateBind(0);

		s.SetMat4("view", camera.ViewMatrix().convertToFloatArray());
		Math3D::Vector4 rotateVec = Math3D::Vector4((float)glfwGetTime(), (float)glfwGetTime(), (float)glfwGetTime());
		model.SetRotationXYZ(rotateVec);
		s.SetMat4("model", model.convertToFloatArray());
		glBindBuffer(GL_ARRAY_BUFFER, vb.GetName());
		vao.Render(NUM_VERTICES);
		vao.Unbind();
		glUseProgram(0);


		glDisable(GL_TEXTURE_2D);
		sground.Use();
		vaog.Bind();
		glBindBuffer(GL_ARRAY_BUFFER, vbg.GetName());
		sground.SetMat4("view", camera.ViewMatrix().convertToFloatArray());
		vaog.Render();
		vaog.Unbind();
		glUseProgram(0);
		glEnable(GL_TEXTURE_2D);



		// glfw: swap buffers and poll IO events
		// --------
		glfwSwapBuffers(win.GetWindow());
		glfwPollEvents();
	}

	//vao.RemoveIndexBuffer();
	// de-allocate all resources 
	// note: this is optional, presumably because we're calling glfwTerminate (?)
	//vao.~VertexArray();

	glfwTerminate(); // cleans up resources and exits application properly
}

void RenderSystem::processInput(GLFWwindow *window, Camera &camera)
{
	Math3D::Vector4 cameraPos = camera.GetEye();
	Math3D::Vector4 cameraFront = camera.GetLookAt();
	Math3D::Vector4 cameraUp = camera.GetUpApproximate();

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += (cameraSpeed * cameraFront);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Math3D::Vector4 temp = cameraFront^cameraUp;
		temp.Normalize();
		cameraPos -= temp * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Math3D::Vector4 temp = cameraFront^cameraUp;
		temp.Normalize();
		cameraPos += temp * cameraSpeed;
	}
	camera.SetEye(cameraPos);
}
