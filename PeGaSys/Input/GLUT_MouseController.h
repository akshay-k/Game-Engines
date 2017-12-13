#pragma once
#ifndef GLUT_MOUSECONTROLLER_H
#define GLUT_MOUSECONTROLLER_H
#include"MouseControllerBase.h"

class GLUT_MouseController : public MouseControllerBase {
public:

	static int sMouseX, sMouseY;
	static int sMouseDeltaX, sMouseDeltaY;
	static std::vector<int> sMouseButtons;
	static int sModifiers;

	GLUT_MouseController();
	~GLUT_MouseController();

	// MouseControllerBase implements GetNumInputMechanisms. 
	// MouseControllerBase implements GetInputMin. 
	// MouseControllerBase implements GetInputMax.
	virtual int GetInputValue(int inputMechanismIndex);
	virtual int GetNumFeedbacks() const;
	virtual int GetFeedbackRange() const;
	virtual void SetFeedback(int feedback);
	/*-------------------CALLBACKS-----------------------*/

	static void UpdateMousePosition(int x, int y);
	static void GlutMouseButtonCallback(int button, int state, int x, int y);
	static void GlutMouseMotionCallback(int x, int y);
	static void GlutEntryCallback(int state);
	void GlutRegisterMouseCallbacks();
};

#endif // !GLUT_MOUSECONTROLLER_H
