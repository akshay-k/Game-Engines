#pragma once
#include <assert.h>
class PhysicalObject;
template < typename T > T * ReinterpretCastPtrHelper(void * voidPtr)
{
	T * obj = reinterpret_cast< T * >(voidPtr);
	assert(obj->GetType() == T::sType);
	return obj;
}

class IPhysicalObjectAffector
{
public:
	virtual void operator()(PhysicalObject * physObj) = 0;
};

class PhysicalObjectAffectorBase:public IPhysicalObjectAffector
{
public:
	PhysicalObjectAffectorBase(unsigned type);
	~PhysicalObjectAffectorBase();
	virtual void operator()(class PhysicalObject * physObj) = 0;
	unsigned GetType() const { return mType; }
private:
	unsigned mType;
};

