#pragma once
#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H
#include "DynamicRecord.h"
#include "RTTI.h"
#include"Framework.h"

class AudioComponent : public DynamicRecord {
	RTTI_INTERFACE_WITH_PARENT(DynamicRecord);
public:
	AudioComponent(char*);
	void AudioInit();
	void StartInfiniteSound();
	void StartSingleSound();
private:
	ALuint      uiBuffer;
	ALuint      uiSource;
	ALint       iState;
	char*     WAVE_FILE;
	AudioComponent(AudioComponent &); // Disallow copy construction
	AudioComponent & operator=(AudioComponent &); // Disallow assignment copy
};

#endif // !AUDIOCOMPONENT_H



