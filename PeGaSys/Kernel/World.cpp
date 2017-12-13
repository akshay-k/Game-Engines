#include "World.h"

RTTI_DEFINITIONS(World);

inline DynamicRecord * World::AppendNewSector(const char * sectorName)
{
	return NULL;
}

void World::Update(double virtualTimeNow, float virtualTimeChange)
{
	TypedValue tvVirtualTimeNow(virtualTimeNow), tvVirtualTimeChange(virtualTimeChange);
	Arguments args(tvVirtualTimeNow, tvVirtualTimeChange);
	InvokeDescendants(Entity::TRANSFORM_STR, args);
}

World & World::operator=(const World &) { return *this; }

World::World(){}

World::~World(){}