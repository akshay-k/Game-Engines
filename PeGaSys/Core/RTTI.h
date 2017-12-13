#pragma once
#ifndef RTTI_H
#define RTTI_H
#include"TypeInfo.h"

#define RTTI_INTERFACE()          \
public:         \
	virtual bool IsA(const TypeInfo & typeInfo) const { return (typeInfo == GetTypeIdClass()); }   \
	static const TypeInfo & GetTypeIdClass() { return sRunTimeTypeId; }                 \
	virtual const TypeInfo & GetTypeIdInstance() const { return GetTypeIdClass(); }                 \
private:                     \
	static TypeInfo sRunTimeTypeId; \

#define RTTI_INTERFACE_EXCEPT_ISA()                                                         \
public:                                                                                 \
	static  const TypeInfo & GetTypeIdClass ()        { return sRunTimeTypeId ; } \
	virtual const TypeInfo & GetTypeIdInstance() const { return GetTypeIdClass()   ; } \
private:                                                                                \
	static TypeInfo sRunTimeTypeId ;

#define RTTI_INTERFACE_WITH_PARENT( ParentType )                  \
public:                                                          \
virtual bool IsA( const TypeInfo & typeInfo ) const { \
return ( typeInfo == GetTypeIdClass() ) || ParentType::IsA( typeInfo ); }    \
static  const TypeInfo & GetTypeIdClass (){ return sRunTimeTypeId; }              \
virtual const TypeInfo & GetTypeIdInstance() const { return GetTypeIdClass(); }     \
private:                                                              \
static TypeInfo sRunTimeTypeId ;

#define RTTI_DEFINITIONS( Type ) TypeInfo Type::sRunTimeTypeId( # Type ) ;

class RTTI
{
public:
	virtual ~RTTI() {}
	virtual const TypeInfo & GetTypeIdInstance() const = 0;
	virtual bool IsA(const TypeInfo &) const = 0;
};

inline const TypeInfo & TypeId(const RTTI * object) { return object->GetTypeIdInstance(); } 

inline const TypeInfo & TypeId(const RTTI & object) { return object.GetTypeIdInstance(); } 

template <typename T> const TypeInfo & TypeId() { return T::GetTypeIdClass(); } 

template < typename T > const T * ReinterpretCastPtr(const void * voidPtr) { 
	const T * rttiObject = reinterpret_cast< const T * >(voidPtr);    
	return rttiObject; 
}

template < typename T > T * ReinterpretCastPtr(void * voidPtr) { 
	T * rttiObject = reinterpret_cast< T * >(voidPtr); 
	return rttiObject; 
}

#endif // !RTTI_H

