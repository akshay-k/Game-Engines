 #pragma once
#ifndef SEQUENCECONTAINER_H
#define SEQUENCECONTAINER_H
#include"Sequence.h"

class SequenceContainer {
	typedef vector<Sequence>::const_iterator SequenceIterator;
	vector<Sequence> mSequences;
public:
	Sequence & AppendSequence(int sequenceId, size_t numSteps);
	int GetNextCookedEvent(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep, SequenceIterator & iter);
	int Cook(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep, Sequence & sequence);
	void Update(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep);
	SequenceIterator SequencesBegin();
	bool Contains(int sequenceId);
};

#endif // !SEQUENCECONTAINER_H