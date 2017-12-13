#include"ControllerInputTarget.h"
#include<iostream>

void ControllerInputTarget::Init(IController * controller, int inputMechanismIndex, int inputValueMin, int inputValueMax)
{
	mController = controller;
	mInputMechanismIndex = inputMechanismIndex;

	if (INT_MIN == inputValueMin) {
		mInputValueMin = mController->GetInputMin(mInputMechanismIndex);
	}
	else {
		mInputValueMin = inputValueMin;
	}

	if (INT_MAX == inputValueMax) {
		mInputValueMax = mController->GetInputMax(mInputMechanismIndex);
	}
	else {
		mInputValueMax = inputValueMax;
	}
}

bool ControllerInputTarget::IsActive() const
{
	//std::cout << "control within isActive";
	const int value = mController->GetInputValue(mInputMechanismIndex);
	bool active = (value >= mInputValueMin) && (value <= mInputValueMax);
	if(active == 1)
		cout << "active :: " << active;
	return active;
}

ControllerInputTarget::ControllerInputTarget() {
	Init();
}
ControllerInputTarget::ControllerInputTarget(IController * controller, int inputMechanismIndex, int inputValueMin, int inputValueMax) {
	Init(controller, inputMechanismIndex, inputValueMin, inputValueMax);
}
ControllerInputTarget::ControllerInputTarget(IController * controller, int inputMechanismIndex) {
	Init(controller, inputMechanismIndex);
}