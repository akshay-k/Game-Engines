// Input.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<Windows.h>    
#include<gl/GL.h>    
#include<gl/GLU.h>    
#include<gl/glut.h>  
#include"GLUT_KeyboardController.h"
#include"GLUT_MouseController.h"
#include"SequenceContainer.h"
using namespace std;

GLUT_KeyboardController * keyboardController = new GLUT_KeyboardController();
GLUT_MouseController * mouseController = new GLUT_MouseController();
SequenceContainer* seqContainer = new SequenceContainer();

void Init_OpenGL()
{
	// set background color to Black    
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// set shade model to Flat    
	glShadeModel(GL_FLAT);
}

void Display_Objects(void)
{
	// clearing the window or remove all drawn objects    
	glClear(GL_COLOR_BUFFER_BIT);
	/*glPushMatrix(), which copies the current matrix and adds
	the copy to the top of the stack, and
	glPopMatrix(), which discards the top matrix on the stack*/
	glPushMatrix();
	//the glTranslatef() routine in the display list alters the position of the next object to be drawn    
	glTranslatef(0.0, 0.0, 0.0);
	// set color to object glColor3f(red,green,blue);    
	glColor3f(1.0, 0.8, 0.0);
	// draw a wire tea pot    
	glutWireTeapot(1.0);

	// draw a wire sphere    
	glTranslatef(-2.5, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(0.8, 30, 30);

	// draw a wire cone    
	glTranslatef(5.0, 0.0, 0.0);
	glColor3f(0.0, 0.6, 1.0);
	glutWireCone(0.8, 1.5, 20, 20);

	// draw a wire cube    
	glTranslatef(-1.0, 1.4, 0.0);
	glColor3f(1.0, 0.3, 0.0);
	glutWireCube(1.0);

	// draw a wire torus    
	glTranslatef(-3.0, 0.4, 0.0);
	glColor3f(1.0, 0.3, 1.0);
	glutWireTorus(0.2, 0.6, 20, 20);

	// draw a text    
	glTranslatef(-2.5, -4.0, 0.0);

	char str[] = { "OpenGL Demo in Visual C++" };

	glColor3f(1.0, 1.0, 1.0);
	// set position to text    
	glRasterPos2f(2.0, 0.0);

	for (int i = 0; i < strlen(str); i++)
	{
		// draw each character    
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	//you can draw many objects here like polygons,lines,triangles etc    

	glPopMatrix();
	glutSwapBuffers();
}
// Reshape() function    
void Reshape(int w, int h)
{
	//adjusts the pixel rectangle for drawing to be the entire new window    
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//matrix specifies the projection transformation    
	glMatrixMode(GL_PROJECTION);
	// load the identity of matrix by clearing it.    
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	//matrix specifies the modelview transformation    
	glMatrixMode(GL_MODELVIEW);
	// again  load the identity of matrix    
	glLoadIdentity();
	// gluLookAt() this function is used to specify the eye.    
	// it is used to specify the coordinates to view objects from a specific position    
	gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void GlutIdleFunction() {
	//cout << "GlutIdleFunction ";
	seqContainer->Update(1, 5, 1, 5);
}

int main(int argc, char** argv)
{
	//Sequence &seq = seqContainer->AppendSequence(1, 1);;
	//SequenceStep *step1 = new SequenceStep(5, 1, &seq, 1);
	//SequenceStep &step2 = seq.AppendSequenceStep(*step1, 1, 0);
	//ControllerInputTarget * target1 = new ControllerInputTarget(keyboardController, 1, 'a', 'a');
	//step2.AppendRequiredChord(*target1);
	//cout << "size : ***" << step2.getRequiredChordsSize();

	Sequence &seq = seqContainer->AppendSequence(2, 1);;
	SequenceStep *step1 = new SequenceStep(5, 1, &seq, 2);
	SequenceStep &step2 = seq.AppendSequenceStep(*step1, 1, 0);
	ControllerInputTarget * target1 = new ControllerInputTarget(mouseController, 0, 1, 1);
	step2.AppendRequiredChord(*target1);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(250, 50);
	glutCreateWindow("OpenGL Demo");
	Init_OpenGL();
	keyboardController->GlutRegisterKeyCallbacks();
	mouseController->GlutRegisterMouseCallbacks();
	glutIdleFunc(GlutIdleFunction);
	glutDisplayFunc(Display_Objects);
	glutReshapeFunc(Reshape);
	glutMainLoop();
    return 0;
}
 
