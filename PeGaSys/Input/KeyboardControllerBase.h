#pragma once
#ifndef KEYBOARDCONTROLLERBASE_H
#define KEYBOARDCONTROLLERBASE_H
#include"IController.h"
#include<iostream>

class KeyboardControllerBase: public IController {
public:
	enum Inputs { KEY_VALUE, KEY_MODIFIER, KEY_SPECIAL, KEY_ALL, NUM_INPUTS = KEY_ALL + 255 };

	void Fail(char * msg) const { throw msg; }

	virtual int GetInputMin(int /*inputMechanismIndex*/) const { return 0; }

	virtual int GetInputMax(int inputMechanismIndex) const {
		switch (inputMechanismIndex) { 
			case KEY_VALUE: 
				return 255; 
				break; 
			case KEY_MODIFIER: 
				return 255; 
				break; 
			case KEY_SPECIAL: 
				return 255; 
				break; 
			case KEY_ALL: 
				return 1; 
				break;
		} 
		Fail("Failed from : KeyboardControllerBase::GetInputMax"); 
		return 255; 
	}

	virtual int GetNumInputMechanisms(int) {
		return 0;
	};
	virtual int GetInputValue(int s) {
		std::cout << "Returning from KeyboardControllerBase";
		return 0;
	};
	virtual int GetNumFeedbacks() {
		printf("Returning from KeyboardControllerBase");
		return 0;
	};
	virtual int GetFeedbackRange() {
		printf("Returning from KeyboardControllerBase");
		return 0;
	};
	virtual void SetFeedback(int) {
		printf("Returning from KeyboardControllerBase");
		return;
	};
};

#endif // !KEYBOARDCONTROLLERBASE_H