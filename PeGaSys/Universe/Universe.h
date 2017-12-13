#pragma once
#ifndef UNIVERSE_H
#define UNIVERSE_H
#include"Entity.h"
#include"World.h"
#include"TimeComponent.h"

struct GlobalEntity
{
	enum MemberIdxE
	{
		TIME = Entity::NUM_MEMBERS,
		INPUT,
		NUM_MEMBERS
	};
	static const char * TIME_STR;
	static const char * INPUT_STR;
};
const char * GlobalEntity::TIME_STR = "TIME_STR";
const char * GlobalEntity::INPUT_STR = "INPUT_STR";

class Universe
{
public:
	static const size_t GLOBAL_SECTOR = 0;
	static const size_t GLOBAL_ENTITY = 0;
	static const char * GLOBAL_SECTOR_STR;
	static const char * GLOBAL_ENTITY_STR;
	//Universe(Render::ApiBase * renderApi, Audio::IAudioApi * audioApi, Input::ControllerContainer * controllerContainer);
	Universe() { mTimeComponent = new TimeComponent; mWorld = new World; mRootSchema = new Schema; }
	//~Universe() {}
	void Process(double realTimeNow, float realTimeChange);
	World * GetWorld() { return mWorld; }
	const double & GetVirtualTimeNow() const { return mTimeComponent->_virtualTimeNow; }
private:
	Universe(const Universe & that);
	Universe & operator=(const Universe & that);
	void NewSectorForGlobals(World * world);
	Schema * mRootSchema; ///< Root Schema for type wrappers.
	World * mWorld; ///< Virtual world
	DynamicRecord * mGlobalSector; ///< Sector for global Entity
	Entity * mGlobalEntity; ///< Global entity for global variables like time
	TimeComponent * mTimeComponent; ///< Global component for time
	//InputComponent * mInputComponent; ///< Global component for input
};

const char * Universe::GLOBAL_SECTOR_STR = "GLOBAL_SECTOR_STR";
const char * Universe::GLOBAL_ENTITY_STR = "GLOBAL_ENTITY_STR";

void Universe::Process(double realTimeNow, float realTimeChange)
{
	{ // TimeComponent::PreUpdate
		mTimeComponent->_realTimeNow = realTimeNow;
		mTimeComponent->_realTimeChange= realTimeChange;
		mTimeComponent->_virtualTimeChange = mTimeComponent->_virtualFromRealTimeScale * realTimeChange; // virtual time relates to real time
	}
	// Update Entities. Updates render models from physics simulation.
	mWorld->Update(mTimeComponent->_virtualTimeNow, mTimeComponent->_virtualTimeChange);
	{ // TimeComponent::PostUpdate
	  // Update virtual clock.
		mTimeComponent->_virtualTimeNow += mTimeComponent->_virtualTimeChange;
		++(mTimeComponent->_frameCounter);
	}
}


#endif // !UNIVERSE_H