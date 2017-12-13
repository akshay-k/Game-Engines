#pragma once
#ifndef TIMECOMPONENT_H
#define TIMECOMPONENT_H
#include"DynamicRecord.h"
#include "RTTI.h"

struct TimeComponent : public DynamicRecord
{
	RTTI_INTERFACE_WITH_PARENT(DynamicRecord);
public:

	TimeComponent() {}
	
	enum MemberIdxE
	{
		REAL_TIME_NOW,
		REAL_TIME_CHANGE,
		VIRTUAL_TIME_NOW,
		VIRTUAL_TIME_CHANGE,
		VIRTUAL_TIME_SCALE,
		FRAME_COUNTER,
		NUM_MEMBERS
	};
	static const char * REAL_TIME_NOW_STR;
	static const char * REAL_TIME_CHANGE_STR;
	static const char * VIRTUAL_TIME_NOW_STR;
	static const char * VIRTUAL_TIME_CHANGE_STR;
	static const char * VIRTUAL_TIME_SCALE_STR;
	static const char * FRAME_COUNTER_STR;

	void Populate();

	double  _realTimeNow; ///< Real time now in seconds.
	float  _realTimeChange; ///< Real time change in seconds.
	double  _virtualTimeNow; ///< Virtual (simulation) time now in seconds.
	float  _virtualTimeChange; ///< Virtual (simulation) time change in seconds.
	float  _virtualFromRealTimeScale; ///< Scale applied to real time changes when computing virtual time changes.
	unsigned long long  _frameCounter; ///< Number of times Process has been called.
private:
	TimeComponent(TimeComponent &); // Disallow copy construction
	TimeComponent & operator=(TimeComponent &); // Disallow assignment copy
};

RTTI_DEFINITIONS(TimeComponent);
const char * TimeComponent::REAL_TIME_NOW_STR = "REAL_TIME_NOW_STR";
const char * TimeComponent::REAL_TIME_CHANGE_STR = "REAL_TIME_CHANGE_STR";
const char * TimeComponent::VIRTUAL_TIME_NOW_STR = "VIRTUAL_TIME_NOW_STR";
const char * TimeComponent::VIRTUAL_TIME_CHANGE_STR = "VIRTUAL_TIME_CHANGE_STR";
const char * TimeComponent::VIRTUAL_TIME_SCALE_STR = "VIRTUAL_TIME_SCALE_STR";
const char * TimeComponent::FRAME_COUNTER_STR = "FRAME_COUNTER_STR";

#endif // !TIMECOMPONENT_H
