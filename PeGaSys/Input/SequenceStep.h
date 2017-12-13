#pragma once
#ifndef SEQUENCESTEP_H
#define SEQUENCESTEP_H
#include"ControllerInputTarget.h"
#include<vector>
#include<list>
#include"Sequence.h"
using namespace std;

class Sequence;
enum Status {
	REJECTED, UNSTARTED, UNFINISHED, SATISFIED
};

class InstanceId {
	int Id;
public:
	explicit InstanceId(int i) { Id = i; }
	bool operator== (InstanceId& other) const
	{
		return Id == other.Id;
	}
};

class SequenceStep {
private:
	typedef vector<ControllerInputTarget>::const_iterator InputConstIterator;
	vector<ControllerInputTarget> mRequiredChord;
	vector<ControllerInputTarget> mDisallowedChord;
	int mMaximumDuration, mMinimumDuration;
	void(*mCallBack)(double, float, double, float);
	InstanceId *mInstanceIdentifier;
	Sequence * mParentSequence;
	//TODO: mInstanceIdentifier, mParentSequence;
public:
	SequenceStep(int maxTime, int minTime, Sequence * seq, int instId);
	void AppendRequiredChord(const ControllerInputTarget& );
	void AppendDisallowedChord(const ControllerInputTarget & );
	Status GetStatus(double ) const;
	void CallBack(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep);
	void SetParentSequence(Sequence*);
	void Reserve(size_t , size_t );
	InstanceId* GetInstanceIdentifier();
	int getRequiredChordsSize();
	//TODO: getInstanceIdentifier, Reserve, CallBack

	static const InstanceId sGenericIdentity;
};
#endif // !SEQUENCESTEP_H
