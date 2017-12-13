#pragma once
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include"SequenceStep.h"
using namespace std;

class SequenceStep;
class InstanceId;
class Sequence {
	//TODO: Sequence::Id?? Used it SequenceContainer
private:
	vector<SequenceStep> mSequenceSteps;
	int mCurrentStep, mId;
	double mTimeCurrentStepEntered;
public:
	static const int sIdNone = -1;
	Sequence(int i) { mId = i; mCurrentStep = -1; mTimeCurrentStepEntered = 0.0; }
	SequenceStep & AppendSequenceStep(const SequenceStep & sequenceStepInfo, size_t numRequiredInputs, size_t numDisallowedInputs);
	bool Update(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep);
	void Reset();
	void Fail(char *);
	void Reserve(size_t);
	int GetId() { return mId; }
	int getSize();
private:
	void AdvanceToNextStep(double timeNow);
	const char * StringOfId() const;
	bool SequenceStepIdIsUnique(InstanceId seqStepId);

};

#endif // !SEQUENCE_H

