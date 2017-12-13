#include<Windows.h> 
#include<gl/GL.h>    
#include<gl/GLU.h>    
#include<gl/glut.h>
#include<assert.h>
#include"GLUT_MouseController.h"
#include"GLUT_KeyboardController.h"  
#define NUM_MOUSE_BUTTONS 4

GLUT_MouseController::GLUT_MouseController() { }

GLUT_MouseController::~GLUT_MouseController() { }

int GLUT_MouseController::GetInputValue(int inputMechanismIndex) {
	
	switch (inputMechanismIndex) { 
	case MC_BUTTON_LEFT: 
		return sMouseButtons[GLUT_LEFT_BUTTON]; 
		break; 
	case MC_BUTTON_MIDDLE: 
		return sMouseButtons[GLUT_MIDDLE_BUTTON]; 
		break; 
	case MC_BUTTON_RIGHT: 
		return sMouseButtons[GLUT_RIGHT_BUTTON]; 
		break; 
	case MC_BUTTON_BACK: 
		return 0; 
		break; 
	case MC_BUTTON_FORWARD: 
		return 0; 
		break; 
	case MC_WHEEL_DELTA: 
		return 0; 
		break; 
	case MC_POSITION_X: 
		return sMouseX; 
		break; 
	case MC_POSITION_Y: 
		return sMouseY; 
		break;
	case MC_MOTION_X: 
		return sMouseDeltaX; 
		break; 
	case MC_MOTION_Y: 
		return sMouseDeltaY; 
		break; 
	case MC_MOTION: 
		return abs(sMouseDeltaX) + abs(sMouseDeltaY); 
		break; 
	} 
	return 0; 
}

int GLUT_MouseController::GetNumFeedbacks() const { return 0; }

int GLUT_MouseController::GetFeedbackRange() const { return 0; }

void GLUT_MouseController::SetFeedback(int feedbackIndex) { }
	
void GLUT_MouseController::UpdateMousePosition(int x, int y) {
	sMouseDeltaX = x - sMouseX; 
	sMouseDeltaY = y - sMouseY; 
	sMouseX = x; sMouseY = y; 
}

void GLUT_MouseController::GlutMouseButtonCallback(int button, int state, int x, int y) {
	assert(button < NUM_MOUSE_BUTTONS); 
	//std::cout << button << "----" << state << "----" << x << "----" << y;
	sMouseButtons[button] = (GLUT_DOWN == state) ? 1 : 0; 
	UpdateMousePosition(x, y); 
	//sModifiers = glutGetModifiers(); 
}

void GLUT_MouseController::GlutMouseMotionCallback(int x, int y) {
	std::cout << "inside GlutMouseMotionCallback \n";
	UpdateMousePosition(x, y); 
	//sModifiers = glutGetModifiers() ; 
}

void GLUT_MouseController::GlutEntryCallback(int state) {
	std::cout << "inside GlutEntryCallback \n";
	if (GLUT_LEFT == state) {   // Focus left current window so act like buttons and keys got released. 
		sMouseButtons[ 0 ] = sMouseButtons[ 1 ] = sMouseButtons[ 2 ] = 0 ; 
		//memset( GLUT_KeyboardController::sKeyStates , 0 , sizeof(GLUT_KeyboardController::sKeyStates ) ) ;
		GLUT_KeyboardController::sSpecialKey = 0 ;
	} 
}

void GLUT_MouseController::GlutRegisterMouseCallbacks() {
	std::cout << "inside GlutRegisterMouseCallbacks \n";
	glutMouseFunc(GlutMouseButtonCallback);
	//glutMotionFunc(GlutMouseMotionCallback);
	//glutPassiveMotionFunc(GlutMouseMotionCallback);
	//glutEntryFunc(GlutEntryCallback);
}

int GLUT_MouseController::sMouseX = 0, GLUT_MouseController::sMouseY = 0;
int GLUT_MouseController::sMouseDeltaX = 0, GLUT_MouseController::sMouseDeltaY = 0;
std::vector<int> GLUT_MouseController::sMouseButtons = std::vector<int>(10,-1);
int GLUT_MouseController::sModifiers = 0;