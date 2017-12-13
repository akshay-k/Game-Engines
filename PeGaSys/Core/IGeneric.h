#pragma once
#ifndef IGENRIC_H
#define IGENERIC_H
#include"RTTI.h"
#include"TypeInfoRegistry.h"

class IGeneric : public RTTI
{
public:
	virtual ~IGeneric() {}
	/// Return address of requested interface, if this object implements that interface. 
	virtual IGeneric * QueryInterface( const TypeInfo & /* typeInfo */ ) { return 0 ; }

};

// dynamically casts a generic pointer to a given specific type
template <typename T> 
T * DynamicCastPtr(IGeneric * objPtr)
{
	T * p = static_cast< T * >(objPtr->QueryInterface(TypeId< T >()));
	//ASSERT(p != 0); // ...otherwise T is not related to the type of objPtr.
					// ...or objPtr's class or T does not implement QueryInterface.
	return p;
}

#endif // !IGENRIC_H

