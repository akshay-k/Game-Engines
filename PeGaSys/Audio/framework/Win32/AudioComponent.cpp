#include "AudioComponent.h"

RTTI_DEFINITIONS(AudioComponent);

AudioComponent::AudioComponent(char * filename) {
	WAVE_FILE = filename;
}

void AudioComponent::AudioInit(){
	
	// Initialize Framework
	ALFWInit();

	ALFWprintf("PlayStatic Test Application\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
		return;
	}

	// Generate an AL Buffer
	alGenBuffers(1, &uiBuffer);

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(WAVE_FILE), uiBuffer))
	{
		ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(WAVE_FILE));
	}

	// Generate a Source to playback the Buffer
	alGenSources(1, &uiSource);

	// Attach Source to Buffer
	alSourcei(uiSource, AL_BUFFER, uiBuffer);
	
}

void AudioComponent::StartInfiniteSound() {
	
	alSourcei(uiSource, AL_LOOPING, 1);
	// Play Source
	alSourcePlay(uiSource);
	ALFWprintf("\nPress a key to quit\n");
	ALFWprintf("Playing Source ");
	do
	{
		Sleep(100);
		ALFWprintf(".");
		// Get Source State
		alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
	} while (iState == AL_PLAYING && !_kbhit());

	ALFWprintf("\n");

	// Clean up by deleting Source(s) and Buffer(s)
	alSourceStop(uiSource);
	alDeleteSources(1, &uiSource);
	alDeleteBuffers(1, &uiBuffer);

	ALFWShutdownOpenAL();

	ALFWShutdown();
	
}

void AudioComponent::StartSingleSound() {
	
	// Play Source
	alSourcePlay(uiSource);
	ALFWprintf("Playing Source ");
	do
	{
		Sleep(100);
		ALFWprintf(".");
		// Get Source State
		alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
	} while (iState == AL_PLAYING);

	ALFWprintf("\n");

	// Clean up by deleting Source(s) and Buffer(s)
	alSourceStop(uiSource);
	alDeleteSources(1, &uiSource);
	alDeleteBuffers(1, &uiBuffer);

	ALFWShutdownOpenAL();

	ALFWShutdown();
	ALFWprintf("\nPress a key to quit\n");
	ALchar ch = _getch();
	
}