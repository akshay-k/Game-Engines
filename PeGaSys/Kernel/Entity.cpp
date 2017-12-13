#include "Entity.h"

const char * Entity::UPDATE_STR = "Update";
const char * Entity::TRANSFORM_STR = "Transform";
RTTI_DEFINITIONS(Entity);

IGeneric * Entity::QueryInterface(const TypeInfo & typeInfo) {
	if (TypeId< Entity >() == typeInfo) {
		return static_cast< Entity * >(this);
	}
	else {
		return nullptr;
	}
}

void Entity::Populate() {}

Entity & Entity::operator=(const Entity & that) { return *this; }

Entity::~Entity(){}

Entity::Entity(){}

Entity::Entity(size_t numDynamicMembers)
{
}

Entity::Entity(const Entity & that)
{
}
