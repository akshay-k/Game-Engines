#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include"DynamicRecord.h"
#include "TransformComponent.h"
class Entity : public DynamicRecord
{
	typedef DynamicRecord Parent;
	RTTI_INTERFACE_WITH_PARENT(DynamicRecord);
public:
	enum ClassMembersE
	{
		TRANSFORM,
		NUM_MEMBERS
	};
	static const char * TRANSFORM_STR; // Name of "Transform" component
	static const char * UPDATE_STR;
	Entity();
	explicit Entity(size_t numDynamicMembers);
	Entity(const Entity & that);
	
	virtual ~Entity();
	
	Entity & operator=(const Entity & that);

	virtual IGeneric * QueryInterface(const TypeInfo & typeInfo);
protected:
	void Populate();
private:
	TransformComponent * mTransformComponent;
};


#endif // !ENTITY_H
