#pragma once
#ifndef DYNAMICRECORD_H
#define DYNAMICRECORD_H
#include"RecordBase.h"
#include"Schema.h"

class DynamicRecord : public RecordBase {
public: 
	DynamicRecord();

	DynamicRecord(Schema &schema);
	
	explicit DynamicRecord(const DynamicRecord & that);
	
	virtual const Schema * GetSchema() const;

	DynamicRecord * GetRoot();

	DynamicRecord * GetOwner();
	
	const DynamicRecord * GetOwner() const;
	
	void Reserve(size_t numMembers);
	
	size_t Add(const char * name, PrimitiveTypeE type, TypeQualiferE qualifiers = TYPE_QUALIFIER_NONE);
	size_t Add(const char * name, const TypedValue & initialValue /* reference to allow for declared alignment */,
		TypeQualiferE qualifiers = TYPE_QUALIFIER_NONE);
	size_t AddMethod(const char * name, InstanceMethodP method);
	size_t AddNonOwning(const char * name, DynamicRecord * objectToReference,
		TypeQualiferE qualifiers = TYPE_QUALIFIER_NONE);
	size_t AddOwning(const char * name, DynamicRecord * objectToAdopt,
		TypeQualiferE qualifiers = TYPE_QUALIFIER_NONE);
	
	//TODO::
	virtual ~DynamicRecord();
	virtual bool & Bool(size_t memberIndex);
	
	virtual bool & Bool(const char * memberName);

	virtual int & Int(size_t memberIndex);

	virtual int & Int(const char * memberName);
	
	virtual const int & Int(size_t memberIndex) const;

	virtual const int & Int(const char * memberName) const;

	virtual long long & Int64(size_t memberIndex);

	virtual long long & Int64(const char * memberName);

	virtual unsigned long long & UInt64(size_t memberIndex);

	virtual unsigned long long & UInt64(const char * memberName);

	virtual float & Flt(size_t memberIndex);

	virtual float & Flt(const char * memberName);

	virtual const float & Flt(size_t memberIndex) const;

	virtual const float & Flt(const char * memberName) const;

	virtual double & Dbl(size_t memberIndex);

	virtual double & Dbl(const char * memberName);

	virtual Math3D::Vector4 & Vec(size_t memberIndex);

	virtual Math3D::Vector4 & Vec(const char * memberName);

	virtual Math3D::Matrix44Ptr & Mtx(size_t memberIndex);

	virtual Math3D::Matrix44Ptr & Mtx(const char * memberName);

	virtual void * & Ptr(size_t memberIndex);

	virtual void * & Ptr(const char * memberName);

	virtual RecordBase * & Ref(size_t memberIndex);

	virtual RecordBase * & Ref(const char * memberName);

	virtual InstanceMethodP & InstMethod(size_t memberIndex);

	virtual InstanceMethodP & InstMethod(const char * memberName);

	virtual ClassMethodPointer & ClassMethod(size_t memberIndex);
	
	virtual ClassMethodPointer & ClassMethod(const char * memberName);
	
	static const DynamicRecord * ReinterpretCast(const RecordBase * record);
	
	static DynamicRecord * ReinterpretCast(RecordBase * record);
	
	//void DebugPrint(int indent = 0) const;

protected: 
	const size_t & Index(const char * memberName) const;
	
	void ShallowCopyValues(const DynamicRecord & that);
	void TransferOwner(DynamicRecord * newOwner);
	void Clear();
	bool Owns(const DynamicRecord * that) const;
	size_t FindOwningReference(const DynamicRecord * that) const;

private: 
	PrimitiveValue & GetMemberValue(size_t memberIndex);
	const PrimitiveValue & GetMemberValue(size_t memberIndex) const;
	void SetMember(size_t memberIndex, const PrimitiveValue & primitiveValue);
	void SetOwner(DynamicRecord * owner);
protected: 
	Schema mSchema;   ///< Schema that defines the type of this record. 
private: 
	DynamicRecord * mOwner ;   ///< DynamicRecord that owns this one. 
	size_t mOffsetFirstDynamicMember ;   ///< Offset of first dynamic (that is, non-native) member in this object. 
	vector< PrimitiveValue >    mPrimitiveValues ;   ///< Dynamic (non-native) members of this object. 
} ;

#endif // !DYNAMICRECORD_H 