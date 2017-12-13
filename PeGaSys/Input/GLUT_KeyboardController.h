#pragma once
#ifndef GLUT_KEYBORADCONTROLLER_H
#define GLUT_KEYBORADCONTROLLER_H
#include"KeyboardControllerBase.h"
#include<vector>

class GLUT_KeyboardController : public KeyboardControllerBase {
public:

	static const int NUM_KEYS = 10000;
	static int sKey, sSpecialKey;
	static std::vector<int> sKeyStates;
	static int sModifiers;

	void SetProperties();
	GLUT_KeyboardController();
	~GLUT_KeyboardController();

	// KeyboardControllerBase implements GetNumInputMechanisms. 
	// KeyboardControllerBase implements GetInputMin. 
	// KeyboardControllerBase implements GetInputMax.
	virtual int GetInputValue(int inputMechanismIndex);
	virtual int GetNumFeedbacks();
	virtual int GetFeedbackRange();
	virtual void SetFeedback(int feedback);

	/*-------------------CALLBACKS-------------------*/
	static void GlutKeyboardCallback(unsigned char c, int x, int y);
	static void GlutKeyboardUpCallback(unsigned char c, int x, int y);
	static void GlutSpecialKeyCallback(int key, int x, int y);
	static void GlutSpecialKeyUpCallback(int /*key*/, int x, int y);
	void GlutRegisterKeyCallbacks();
};

#endif // !GLUT_KEYBORADCONTROLLER_H
