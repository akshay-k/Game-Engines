#include"SequenceStep.h"

const InstanceId SequenceStep::sGenericIdentity = InstanceId(0);

SequenceStep::SequenceStep(int maxTime, int minTime, Sequence * seq, int instId) {
	mMaximumDuration = maxTime;
	mMinimumDuration = minTime;
	mParentSequence = seq;
	mInstanceIdentifier = new InstanceId(instId);
}

void SequenceStep::AppendRequiredChord(const ControllerInputTarget& input) {
	mRequiredChord.push_back(input);
}
void SequenceStep::AppendDisallowedChord(const ControllerInputTarget & input) {
	mDisallowedChord.push_back(input);
}

int SequenceStep::getRequiredChordsSize() {
	return mRequiredChord.size();
}

Status SequenceStep::GetStatus(double durationInCurrentStep) const {
	//cout << "GetStatus "; 
	// The order of these tests matters: 
	// First check for rejection, then for satisfaction. 
	if (durationInCurrentStep > mMaximumDuration) {
		// Remained in this step too long. 
		//cout << "returning rejected";
		return REJECTED;
		// Restart sequence. 
	}
	for (InputConstIterator iter = mDisallowedChord.begin(); iter != mDisallowedChord.end(); ++iter) {
		//cout << "inside for";
		const ControllerInputTarget & input = *iter;
		if (input.IsActive()) {
			// An unacceptable input occurred. 
			return REJECTED;  // The whole chord is rejected.  Restart sequence.
		}
	}
	if (durationInCurrentStep < mMinimumDuration) {
		// Have not been in state long enough. 
		return UNSTARTED;
		// Continue waiting on chord to start. 
	}
	for (InputConstIterator iter = mRequiredChord.begin(); iter != mRequiredChord.end(); ++iter) {
		const ControllerInputTarget & input = *iter;
		if (!input.IsActive()) {
			// This input is not satisfied. 
			return UNFINISHED;  // The whole chord is not satisfied.  Continue waiting on chord. 
		}
	}
	return SATISFIED;   // The whole chord is satisfied.  Advance to next step or complete sequence.
}

void SequenceStep::CallBack(double virtualTimeNow, float virtualTimeStep, double wallTimeNow, float wallTimeStep) {
	if (mCallBack) {
		(*mCallBack)(virtualTimeNow, virtualTimeStep, wallTimeNow, wallTimeStep);
	}
}

void SequenceStep::SetParentSequence(Sequence* sequence) {
	mParentSequence = sequence;
}

void SequenceStep::Reserve(size_t numRequiredInputs, size_t numDisallowedInputs) {
	mRequiredChord.reserve(numRequiredInputs);
	mDisallowedChord.reserve(numDisallowedInputs);
}

InstanceId *SequenceStep::GetInstanceIdentifier() {
	return mInstanceIdentifier;
}

//TODO: getInstanceIdentifier, Reserve, CallBack