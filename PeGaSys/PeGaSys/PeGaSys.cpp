
#include <iostream>
#include <ctime>
#include "Universe.h"
#include "PhysicsWorld.h"
//*

// Render headers
// --------------------------------
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "RenderSystem.h"
#include "GLWindow.h"

/*can be commented when not testing input*/

/*
#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<gl/glut.h>
#include"GLUT_KeyboardController.h"
#include"GLUT_MouseController.h"
#include"SequenceContainer.h"
/*can be commented when not testing audio*/
#include "Framework/Win32/AudioComponent.h"

#define	TEST_WAVE_FILE		"Footsteps.wav"


using namespace std;


/*--------globals for input-----------*/
/*
GLUT_KeyboardController * keyboardController = new GLUT_KeyboardController();
GLUT_MouseController * mouseController = new GLUT_MouseController();
SequenceContainer* seqContainer = new SequenceContainer();

void GlutIdleFunction() {
	seqContainer->Update(1, 5, 1, 5);
}

void Display_Objects(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void createTestGlutWindowAndTestInput(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(700, 500);
glutInitWindowPosition(250, 50);
glutCreateWindow("OpenGL Demo");
keyboardController->GlutRegisterKeyCallbacks();
mouseController->GlutRegisterMouseCallbacks();
glutIdleFunc(GlutIdleFunction);
glutDisplayFunc(Display_Objects);
glutMainLoop();
}
*/
/*--------------end of input related helpers--------------*/



int main(int argc, char** argv)
{
	/*--------------Physics test-------------------*/
	/*
	PhysicsWorld pw(5);
	PhysicalObject* pb = pw.NewPhysicalObject(SPHERE_SHAPE);
	PhysicalObject* pb2 = pw.NewPhysicalObject(CONVEX_POLYHEDRON_SHAPE);

	Entity *e1 = new Entity();
	Entity *e2 = new Entity();
	pb->SetClientData(e1);
	pb2->SetClientData(e2);


	CollisionWorld cw = pw.GetCollisionWorld();
	PhysicsWorld::PhysicalObjectContainer poc = pw.GetPhysicalObjects();
	(void)poc;


	/*--------------Render test-------------------*/

	RenderSystem render = RenderSystem("Tanks!");
	render.Demo();

	GLWindow renderWin = render.Initialize();

	while (!renderWin.WindowShouldClose())
	{
		renderWin.ProcessInput();
		render.ClearBuffers();
		/*

		All the rendering stuff goes here.
		
		*/
		renderWin.Update();
	}
	renderWin.CloseWindow();




	//Universe universe;
	//time_t t = time(0);
	//universe.Process(1.1, 0.1f);

	/*--------------Audio test-------------------*/
	//AudioComponent *a = new AudioComponent(TEST_WAVE_FILE);
	//a->AudioInit();
	//cout << "Hello World!";
	//a->StartInfiniteSound();

	/*--------------Input test-------------------*/
	//Mouse------------
	//Sequence &seq = seqContainer->AppendSequence(2, 1);;
	//SequenceStep *step1 = new SequenceStep(5, 1, &seq, 2);
	//SequenceStep &step2 = seq.AppendSequenceStep(*step1, 1, 0);
	//ControllerInputTarget * target1 = new ControllerInputTarget(mouseController, 0, 1, 1);
	//step2.AppendRequiredChord(*target1);
	//Keyboard----------

	/*

	Sequence &seq = seqContainer->AppendSequence(1, 1);;
	SequenceStep *step1 = new SequenceStep(5, 1, &seq, 1);
	SequenceStep &step2 = seq.AppendSequenceStep(*step1, 1, 0);
	ControllerInputTarget * target1 = new ControllerInputTarget(keyboardController, 1, 'a', 'a');
	step2.AppendRequiredChord(*target1);
	createTestGlutWindowAndTestInput(argc, argv);


	*/

	/*--------------UI test-------------------*/

	return 0;
}







