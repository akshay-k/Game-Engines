#pragma once
#ifndef ICONTROLLER_H
#define ICONTROLLER_H
#include<iostream>

class IController
{
public:
	virtual int GetNumInputMechanisms() {
		printf("GetNumInputMechanisms returning from Icontroller!");
		return 0;
	};
	virtual int GetInputMin(int) { 
		printf("GetInputMin returning from Icontroller!");
		return 0; 
	};
	virtual int GetInputMax(int) { 
		printf("GetInputMax returning from Icontroller!");
		return 0; 
	};
	virtual int GetInputValue(int s) {
		printf("GetInputValue returning from Icontroller!");
		return 0;
	}
	virtual int GetNumFeedbacks() {
		printf("GetNumFeedbacks returning from Icontroller!");
		return 0;
	};
	//TODO: what is range? what is feedback?
	virtual int GetFeedbackRange() {
		printf("GetFeedbackRange returning from Icontroller!");
		return 0;
	};
	virtual void SetFeedback(int) {
		printf("SetFeedback returning from Icontroller!");
		return;
	};
};

#endif // !ICONTROLLER_H

