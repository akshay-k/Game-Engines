#pragma once
#ifndef CONTROLLERINPUTTARGET_H
#define CONTROLLERINPUTTARGET_H
#include<climits>
#include"IController.h"
using namespace std;
class ControllerInputTarget
{
private:
	IController* mController;
	int mInputValueMin, mInputValueMax, mInputMechanismIndex;
public:
	void Init(IController * controller = 0, int inputMechanismIndex = 0, int inputValueMin = INT_MIN, int inputValueMax = INT_MAX);

	bool IsActive() const;

	ControllerInputTarget();
	ControllerInputTarget(IController * controller, int inputMechanismIndex, int inputValueMin, int inputValueMax);
	ControllerInputTarget(IController * controller, int inputMechanismIndex);
};

#endif // !CONTROLLERINPUTTARGET_H

