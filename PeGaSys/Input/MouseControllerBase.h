#pragma once
#ifndef MOUSECONTROLLERBASE_H
#define MOUSECONTROLLERBASE_H
#include<vector>
#include"IController.h"

class MouseControllerBase : public IController{
public:

	enum Inputs {
		MC_BUTTON_LEFT,   // Left mouse button 
		MC_BUTTON_MIDDLE    ,   // Middle mouse button (or wheel press) 
		MC_BUTTON_RIGHT     ,   // Right mouse button 
		MC_BUTTON_BACK      ,   // Auxiliary mouse "back" button 
		MC_BUTTON_FORWARD   ,   // Auxiliary mouse "forward" button 
		MC_WHEEL_DELTA      ,   // Scroll wheel motion 
		MC_POSITION_X       ,   // Horizontal mouse position 
		MC_POSITION_Y       ,   // Vertical mouse position 
		MC_MOTION_X         ,   // Horizontal mouse motion 
		MC_MOTION_Y         ,   // Vertical mouse motion 
		MC_MOTION           ,   // Mouse motion in any direction 
		MC_NUM_INPUTS
	};
	static const int BUTTON_UP = 0; 
	static const int BUTTON_DOWN = 1;

	void Fail(char * msg) const { throw msg; }

	int GetNumInputMechanisms() const { return MC_NUM_INPUTS; }

	int GetInputMin(int inputIndex) const { 
		switch (inputIndex) { 
		case MC_BUTTON_LEFT: 
			return 0; break; 
		case MC_BUTTON_MIDDLE: 
			return 0; break; 
		case MC_BUTTON_RIGHT: 
			return 0; break; 
		case MC_BUTTON_BACK: 
			return 0; break; 
		case MC_BUTTON_FORWARD: 
			return 0; break; 
		case MC_WHEEL_DELTA: 
			return -32767; break; 
		case MC_POSITION_X: 
			return -32767; break; 
		case MC_POSITION_Y: 
			return -32767; break; 
		case MC_MOTION_X: 
			return -32767; break; 
		case MC_MOTION_Y: 
			return -32767; break; 
		case MC_MOTION: 
			return -65535; break; 
		} 
		Fail("Failed from : MouseControllerBase::GetInputMin"); 
		return 0; 
	}

	int GetInputMax(int inputIndex) const { 
		switch (inputIndex) { 
		case MC_BUTTON_LEFT: 
			return 1; break; 
		case MC_BUTTON_MIDDLE: 
			return 1; break; 
		case MC_BUTTON_RIGHT: 
			return 1; break; 
		case MC_BUTTON_BACK: 
			return 1; break; 
		case MC_BUTTON_FORWARD: 
			return 1; break; 
		case MC_WHEEL_DELTA: 
			return 32767; break; 
		case MC_POSITION_X: 
			return 32767; break; 
		case MC_POSITION_Y: 
			return 32767; break; 
		case MC_MOTION_X: 
			return 32767; break; 
		case MC_MOTION_Y: 
			return 32767; break; 
		case MC_MOTION: 
			return 65535; break; 
		} 
		Fail("Failed from : MouseControllerBase::GetInputMax"); 
		return 0; 
	}
};

#endif // !MOUSECONTROLLERBASE_H

