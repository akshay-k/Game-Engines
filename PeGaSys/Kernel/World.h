#pragma once
#ifndef WORLD_H
#define WORLD_H
#include"DynamicRecord.h"
#include"Entity.h"
class World : public DynamicRecord
{
	typedef DynamicRecord Parent;
	RTTI_INTERFACE_WITH_PARENT(DynamicRecord);
public:
	explicit World();
	virtual ~World();
	DynamicRecord * AppendNewSector(const char * sectorName);
	void Update(double virtualTimeNow, float virtualTimeChange);
private:
	explicit World(const World *); // Disallow copy-construction
	World & operator=(const World &); // Disallow copy
};

#endif // !WORLD_H

