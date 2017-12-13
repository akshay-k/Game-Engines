#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "../Math/Matrix44.h"
#include "../Math/Vector4.h"
#include "Texture.h"
#include "TextureSampler.h"
#include "GLWindow.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"
//#include "RenderSystem.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow *window, Camera &camera);


int main()
{
	//*
	// WINDOW CREATION
	// --------------------------------------------
	GLWindow win = GLWindow();
	win.Create("Tanks!", SCR_WIDTH, SCR_HEIGHT);

	// GLAD: LOAD ALL OPENGL POINTERS
	// --------------------------------------------
	// GLAD manages function pointers for OpenGL so need to initialize before running any OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
	}
	//*/
	//RenderSystem system = RenderSystem("Tanks!");

	glEnable(GL_DEPTH_TEST);

	// TRANSFORMATION MATRICES
	// --------------------------------------------
	Math3D::Matrix44 model = Math3D::Matrix44();

	Math3D::Matrix44 identity = Math3D::Matrix44();



	// SHADERS
	// --------------------------------------------
	//*
	std::string shaderDir = "./Shaders/";
	std::string shaderFile = shaderDir + "PositionTexture";
	std::string vsPath = shaderFile + ".vs";
	std::string fsPath = shaderFile + ".fs";
	Shader s = Shader(vsPath.c_str(), fsPath.c_str());
	//*/

	// VERTEX BUFFER
	// --------------------------------------------
	/*
	int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};
	*/
	

	// cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	int sizeVertices = 36*5;
	VertexArray vao = VertexArray();
	//IndexBuffer ibo = IndexBuffer();
	VertexBuffer vb = VertexBuffer(s);

	vao.Bind();
	///*
	vb.LoadData(vertices, sizeVertices, 5 * sizeof(float),
	(void*)0, (void*)(3 * sizeof(float)), (void*)(3 * sizeof(float)));
	//vb.LoadData(vertices, 32); // testing GenericVertex struct
	//*/
	
	
	//ibo.LoadData(indices, 6);
	//vao.SetIndexBuffer(ibo);

	vb.ConfigureCommonAttributes();
	
	Camera camera = Camera();
	camera.SetEye(Math3D::Vector4(1.0f, 0.0f, 3.0f));
	camera.SetLookAt(Math3D::Vector4(0.0f, 0.0f, -1.0f));
	camera.SetUpApproximate(Math3D::Vector4(0.0f, 1.0f, 0.0f));

	camera.SetFieldOfViewVert(Math3D::Matrix44::degreesToRadians(45.0f));
	camera.SetAspectRatio((float)SCR_WIDTH / (float)SCR_HEIGHT);
	camera.SetClipDepths(0.1f, 100.0f);



	// TEXTURES
	// --------------------------------------------
	//*
	Texture *tex1 = &Texture();
	unsigned int texture = tex1->GetTextureName();
	tex1->OpenGLBind();
	Image *wall = &Image("./TextureImages/wall.jpg");

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

	s.Use(); // don't forget to activate/use the shader before setting uniforms!
	s.SetInt("texture", 0);
	s.SetMat4("projection", camera.ProjectionMatrix().convertToFloatArray());
	// create while loop because we don't want OpenGL to render once then quit
	// we want it to continue rendering until we tell it to stop
	// simple version of render loop:
	while (!glfwWindowShouldClose(win.GetWindow())) // checks if GLFW is instructed to close
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//GLWindow win = system.GetWindow();
		// INPUT
		// -------
		win.ProcessInput();
		processInput(win.GetWindow(), camera);

		// RENDER
		// -------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tex1->ActivateBind(0);
		s.Use();

		// ------------ T R A N S F O R M A T I O N S ------------------

		
		//mat1.SetRotationZ((float)glfwGetTime());
		/*
				float radius = 3.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		camera.SetEye(Math3D::Vector4(camX, 0.0f, camZ));
		camera.SetLookAt(Math3D::Vector4());
		camera.SetUpApproximate(Math3D::Vector4(0.0f, 1.0f, 0.0f));
		*/



		s.SetMat4("view", camera.ViewMatrix().convertToFloatArray());
		//*
		Math3D::Vector4 rotateVec = Math3D::Vector4((float)glfwGetTime(), (float)glfwGetTime(), (float)glfwGetTime());
		model.SetRotationXYZ(rotateVec);
		s.SetMat4("model", model.convertToFloatArray());

		//s.SetMat4("view", view.convertToFloatArray());
		//s.SetMat4("projection", projection.convertToFloatArray());
		//*/


		// ------------------------------------------------------------------------


		vao.Render(sizeVertices);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// glfw: swap buffers and poll IO events
		// --------
		glfwSwapBuffers(win.GetWindow());	// swaps color buffer and updates window
		glfwPollEvents();	// checks if events are triggered (e.g., keyboard or mouse input),
							// updates window state, and calls any corresponding callback functions
	}

	vao.RemoveIndexBuffer();
	// de-allocate all resources 
	// note: this is optional, presumably because we're calling glfwTerminate (?)
	vao.~VertexArray();

	glfwTerminate(); // cleans up resources and exits application properly
	return 0;
}

void processInput(GLFWwindow *window, Camera &camera)
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
