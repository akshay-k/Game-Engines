#include"SequenceContainer.h"

//TODO: check Sequence::Id
Sequence &  SequenceContainer::AppendSequence(int sequenceId, size_t numSteps) {
	mSequences.push_back(Sequence(sequenceId));
	mSequences.back().Reserve(numSteps);
	return mSequences.back();
}

int SequenceContainer::GetNextCookedEvent(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep, SequenceIterator & iter) {
	//cout << "GetNextCookedEvent ";
	for (; iter != mSequences.end(); ++iter) {   
		// For each input sequence... 
		Sequence sequence = *iter ; 
		//cout << "size : *** " << sequence.getSize();
		const int cookedEvent = Cook( virtualTimeNow , virtualTimeStep , wallTimeNow , wallTimeStep , sequence ) ; 
		if( cookedEvent != Sequence::sIdNone ) {   
			// Sequence completed. 
			++ iter ; 
			// Manually advance to next sequence since loop increment will not execute. 
			// Let caller know this sequence completed. 
			return cookedEvent ; 
		} 
	} 
	return Sequence::sIdNone ;  // No sequence completed. 
}

int SequenceContainer::Cook(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep, Sequence & sequence) {
	//cout << "Cook : size ::: " << sequence.getSize();
	if (sequence.Update(virtualTimeNow, virtualTimeStep, wallTimeNow, wallTimeStep)) {   
		// Sequence completed. 
		sequence.Reset() ; 
		return sequence.GetId() ; 
	} 
	return Sequence::sIdNone ; 
}

void SequenceContainer::Update(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep) {
	//cout << "Update :: mSequences size :: " << mSequences.size() << " Sequence1 size :: " << mSequences[0].getSize();
	SequenceIterator iter = SequencesBegin(); 
	int cookedEvent = Sequence::sIdNone; 
	do {   
		//cout << "while ";
		// For each input sequence... 
		cookedEvent =  GetNextCookedEvent( virtualTimeNow , virtualTimeStep , wallTimeNow , wallTimeStep , iter ) ; 
	} while( cookedEvent != Sequence::sIdNone ) ; 
}

SequenceContainer::SequenceIterator SequenceContainer::SequencesBegin()
{
	return mSequences.begin();
}

bool SequenceContainer::Contains(int sequenceId) {
	for (SequenceIterator iter = mSequences.begin(); iter != mSequences.end(); ++iter) {   
		// For each input sequence... 
		Sequence sequence = * iter ; 
		if( sequence.GetId() == sequenceId ) {   
			// Tell caller this SequenceContainer contains a sequence with the sought identifier. 
			return true ; 
		} 
	} 
	return false ; // Tell caller this SequenceContainer does NOT contain a sequence with the sought identifier. 
}



