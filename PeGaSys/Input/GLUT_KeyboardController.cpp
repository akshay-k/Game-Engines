#include<Windows.h>    
#include<gl/GL.h>    
#include<gl/GLU.h>    
#include<gl/glut.h>  
#include<assert.h>
#include"GLUT_KeyboardController.h"
#include"GLUT_MouseController.h"
#include<iostream>

void GLUT_KeyboardController::SetProperties() {
	// These properties are set on the current GLUT window. 
	// If these calls happen without there being a current GLUT window then an invalid pointer dereference will happen. 
	glutIgnoreKeyRepeat(1);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
}

GLUT_KeyboardController::GLUT_KeyboardController() { }

GLUT_KeyboardController::~GLUT_KeyboardController() {}

int GLUT_KeyboardController::GetInputValue(int inputMechanismIndex) {
	//std::cout << "return from the actual controller";
	/*
	if (inputMechanismIndex >= KEY_ALL) {
		// Caller is asking about the non-special key keyIndex+KEY_ALL.
		int keyIndex = inputMechanismIndex - KEY_ALL ;  // Extract keyIndex from vaule encoded in arg
		assert( ( keyIndex >= 0 ) && ( keyIndex < NUM_KEYS ) ) ;
		return sKeyStates[ keyIndex ] ; // return whether that key is currently down
	}
	switch( inputMechanismIndex ) {
		case KEY_VALUE:
			return sKey ;
			break ;
		case KEY_MODIFIER:
			return sModifiers ;
			break ;
		case KEY_SPECIAL:
			return sSpecialKey ;
			break ;
		case KEY_ALL:
			Fail("Failed from GLUT_KeyboardController : GetInputValue : case KEY_ALL");
			break ;
		default:
			Fail("Failed from GLUT_KeyboardController : GetInputValue : case deafult");
			break ;
	}
	*/
	//return 0;
	return sKey;
}
int GLUT_KeyboardController::GetNumFeedbacks() { return 0; }

int GLUT_KeyboardController::GetFeedbackRange() { return 0; }

void GLUT_KeyboardController::SetFeedback(int feedbackIndex) { }

void GLUT_KeyboardController::GlutKeyboardCallback(unsigned char c, int x, int y) {
	assert(c < NUM_KEYS);
	sKey = c;
	std::cout << "key : " << c;
	sKeyStates[c] = 1;
	std::cout << " set in vector ";
	//GLUT_MouseController::UpdateMousePosition(x, y);
	//std::cout << "before assert";
	//sModifiers = glutGetModifiers();
}

void GLUT_KeyboardController::GlutKeyboardUpCallback(unsigned char c, int x, int y) {
	std::cout << " upkey callback ";
	assert(c < NUM_KEYS);
	sKey = 0;
	sKeyStates[c] = 0;
	//GLUT_MouseController::UpdateMousePosition(x, y);
	//sModifiers = glutGetModifiers();
}
void GLUT_KeyboardController::GlutSpecialKeyCallback(int key, int x, int y) {
	std::cout << " special key callback ";
	sSpecialKey = key;
	//GLUT_MouseController::UpdateMousePosition(x, y);
	//sModifiers = glutGetModifiers();
}

void GLUT_KeyboardController::GlutSpecialKeyUpCallback(int /*key*/, int x, int y) {
	std::cout << " upspecialkey callback ";
	sSpecialKey = 0;
	//GLUT_MouseController::UpdateMousePosition(x, y);
	//sModifiers = glutGetModifiers();
}

void GLUT_KeyboardController::GlutRegisterKeyCallbacks() {
	// These apply to the current GLUT window only. 
	// If there is no current GLUT window, these calls will crash the app. 
	glutKeyboardFunc(GlutKeyboardCallback);
	glutKeyboardUpFunc(GlutKeyboardUpCallback);
	//glutSpecialFunc(GLUT_KeyboardController::GlutSpecialKeyCallback);
	//glutSpecialUpFunc(GLUT_KeyboardController::GlutSpecialKeyUpCallback);
}

int GLUT_KeyboardController::sKey = 0, GLUT_KeyboardController::sSpecialKey = 0;
std::vector<int> GLUT_KeyboardController::sKeyStates = std::vector<int>(1000);
int GLUT_KeyboardController::sModifiers=0;