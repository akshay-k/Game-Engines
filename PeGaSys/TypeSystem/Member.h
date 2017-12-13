#ifndef MEMBER_H
#define MEMBER_H
#include"Primitive.h"
class Schema;
class Member {
public: 
	static const unsigned sTypeMask = 0x1f; 
	static const unsigned sOffsetMax = 0xffff; 
	static const unsigned sAlignmentMax = 0xff; 
	Member(); 
	Member(PrimitiveTypeE type, TypeQualiferE typeQualifier, size_t offsetInBits);
	Member(PrimitiveTypeE type, size_t offsetInBits); 
	Member(const Schema * schema, TypeQualiferE typeQualifier, size_t offsetInBits);
	Member(const Schema * schema, size_t offsetInBits); 
	const size_t &  GetOffsetInBits() const { return mOffsetInBits; } 
	size_t GetOffsetInBytes() const { return GetOffsetInBits() >> 3; } 
	PrimitiveTypeE GetType() const { return static_cast< PrimitiveTypeE >(mType);}
	const TypeQualiferE & GetQualifiers() { return mQualifiers; }
	bool HasQualifier(TypeQualiferE qualifier) const { return (mQualifiers & qualifier) ? true : false; }
	const Schema *  GetSchema() const { return mSchema; } 
	void Clear() { mOffsetInBits = 0; mType = TYPE_INVALID; mQualifiers = TYPE_QUALIFIER_NONE; mSchema = nullptr; }
private: 
	size_t mOffsetInBits;   ///< Offset, in bits, from start of object 
	unsigned char   mType ;   ///< Type of this member variable 
	TypeQualiferE mQualifiers ;   ///< Qualifiers on the type of this member variable 
	const Schema *  mSchema ;   ///< Address of Schema, when mType is TYPE_AGGREGATE 
};
#endif // !MEMBER_H
