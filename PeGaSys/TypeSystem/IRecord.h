#pragma once
#ifndef IRECORD_H
#define IRECORD_H
#include"IGeneric.h"
#include"Schema.h"

class IRecord : public IGeneric
{
public: 
	virtual ~IRecord() {} 
	virtual const TypeInfo & GetTypeIdInstance(void) const = 0; 
	virtual bool IsA(const TypeInfo &) const = 0; 
	virtual IGeneric * QueryInterface(const TypeInfo & /* typeInfo */) = 0; 
	virtual const Schema * GetSchema() const = 0; 
	virtual bool & Bool(size_t memberIndex) = 0; 
	virtual bool & Bool(const char * memberName) = 0; 
	virtual int & Int(size_t memberIndex) = 0; 
	virtual int & Int(const char * memberName) = 0; 
	virtual const int & Int(size_t memberIndex) const = 0; 
	virtual const int & Int(const char * memberName) const = 0; 
	virtual long long & Int64(size_t memberIndex) = 0; 
	virtual long long & Int64(const char * memberName) = 0; 
	virtual unsigned long long & UInt64(size_t memberIndex) = 0; 
	virtual unsigned long long & UInt64(const char * memberName) = 0; 
	virtual float & Flt(size_t memberIndex) = 0; 
	virtual float & Flt(const char * memberName) = 0; 
	virtual const float & Flt(size_t memberIndex) const = 0; 
	virtual const float & Flt(const char * memberName) const = 0; 
	virtual double & Dbl(size_t memberIndex) = 0; 
	virtual double & Dbl(const char * memberName) = 0; 
	virtual Math3D::Vector4 & Vec(size_t memberIndex) = 0; 
	virtual Math3D::Vector4 & Vec(const char * memberName) = 0; 
	virtual Math3D::Matrix44Ptr & Mtx(size_t memberIndex) = 0; 
	virtual Math3D::Matrix44Ptr & Mtx(const char * memberName) = 0; 
	virtual void * & Ptr(size_t memberIndex) = 0; 
	virtual void * & Ptr(const char * memberName) = 0; 
	virtual class RecordBase * & Ref(size_t memberIndex) = 0; 
	virtual class RecordBase * & Ref(const char * memberName) = 0; 
	virtual InstanceMethodP & InstMethod(size_t memberIndex) = 0; 
	virtual InstanceMethodP & InstMethod(const char * memberName) = 0; 
	virtual ClassMethodPointer & ClassMethod(size_t memberIndex) = 0; 
	virtual ClassMethodPointer & ClassMethod(const char * memberName) = 0;

};

#endif // !IRECORD_H
