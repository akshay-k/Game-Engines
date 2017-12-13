#include"Sequence.h"
#include"SequenceStep.h"
#include<ctype.h>
using namespace std;

SequenceStep & Sequence::AppendSequenceStep(const SequenceStep & sequenceStepInfo, size_t numRequiredInputs, size_t numDisallowedInputs)
{
	mSequenceSteps.push_back(sequenceStepInfo);
	mSequenceSteps.back().Reserve(numRequiredInputs, numDisallowedInputs);
	mSequenceSteps.back().SetParentSequence(this);
	return mSequenceSteps.back();
}

int Sequence::getSize() {
	return mSequenceSteps.size();
}

bool Sequence::Update(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep) {
	//cout << "Sequence : Update ";
	//cout << "mSeqSteps :Current : " << mCurrentStep;
	//cout << "size : " << mSequenceSteps.size();
	SequenceStep & nextSequenceStep = mSequenceSteps[mCurrentStep + 1]; 
	//cout << nextSequenceStep.getRequiredChordsSize();
	//cout << " probable error ";
	const double durationInCurrentStep = wallTimeNow - mTimeCurrentStepEntered; 
	const Status nextStepStatus = nextSequenceStep.GetStatus(durationInCurrentStep); 
	//cout << "trying switch";
	switch (nextStepStatus) { 
		case UNSTARTED:                                    
			break; 
		case UNFINISHED:                                    
			break; 
		case SATISFIED: 
			cout << "satisfied";
			AdvanceToNextStep(wallTimeNow); 
			break; 
		case REJECTED: 
			Reset(); 
			break; 
		default: 
			Fail("Invalid state : from Sequemce::Update"); 
			break; 
	}
	if (mCurrentStep >= 0) {   
		//cout << " Sequence is in progress. ";
		SequenceStep & currentSequenceStep = mSequenceSteps[ mCurrentStep ] ; 
		// NOTE: Callback is invoked regardless of status.  
		//The assumption is that the *current* step is SATISFIED until the next step becomes satisfied.  
		//CONSIDER: Either call only when *current* is SATISFIED or pass *current* status to Callback. 
		currentSequenceStep.CallBack( virtualTimeNow , virtualTimeStep , wallTimeNow , wallTimeStep ) ; 
	}
	if (mCurrentStep >= int(mSequenceSteps.size() - 1)) {   
		// Sequence completed. 
		Reset() ; 
		return true ; 
	}
	return false; // Sequence is not complete.
}

/** Reset this sequence to the beginning.
Call this either when the sequence needs to be restarted due to a rejection or after it completes.
*/ 
void Sequence::Reset() { 
	mCurrentStep = -1;
	mTimeCurrentStepEntered = 0.0; 
}

void Sequence::Fail(char * msg) {
	throw msg;
}

void Sequence::AdvanceToNextStep(double timeNow) { 
	++mCurrentStep; 
	mTimeCurrentStepEntered = timeNow; 
}

bool Sequence::SequenceStepIdIsUnique(InstanceId seqStepId ) {
	
	if( SequenceStep::sGenericIdentity == seqStepId ) {  
		// Identifier was not provided so we treat this as "no conflict". 
		return true ; 
	} 
	
	for( size_t i = 0 ; i < mSequenceSteps.size() ; ++ i ) { 
		if( *(mSequenceSteps[ i ].GetInstanceIdentifier()) == seqStepId ) {   
			// Found another sequence step with the same identifier. 
			return false ;  // Tell caller a conflict was found. 
		} 
	} 
	return true ; 
}

const char * Sequence::StringOfId() const { 
	static char strId[5] = {}; 
	if (isprint(mId & 0xff)) { 
		memcpy(strId, &mId, 4); 
	} else { 
		sprintf_s(strId, "%i", mId); 
	}
	return strId; 
}

void Sequence::Reserve(size_t numSteps) {
	mSequenceSteps.reserve(numSteps);
}



