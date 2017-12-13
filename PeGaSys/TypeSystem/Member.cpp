#include"Member.h"

static const unsigned short OFFSET_IN_BITS_INVALID = 0xffff;
Member::Member() : mOffsetInBits(OFFSET_IN_BITS_INVALID), mType(TYPE_INVALID),
mQualifiers(TYPE_QUALIFIER_NONE), mSchema(nullptr) { };

Member::Member(PrimitiveTypeE type, TypeQualiferE qualifiers, size_t offsetInBits) :
	mOffsetInBits(static_cast<unsigned short>(offsetInBits)), mType(static_cast<unsigned char>(type)),
	mQualifiers(qualifiers), mSchema(nullptr) { };

Member::Member(PrimitiveTypeE type, size_t offsetInBits) :
	mOffsetInBits(static_cast<unsigned short>(offsetInBits)), mType(static_cast<unsigned char>(type)),
	mQualifiers(TYPE_QUALIFIER_NONE), mSchema(nullptr) { };

Member::Member(const Schema * schema, TypeQualiferE qualifiers, size_t offsetInBits) :
	mOffsetInBits(static_cast<unsigned short>(offsetInBits)), mType(static_cast<unsigned char>(TYPE_AGGREGATE)),
	mQualifiers(qualifiers), mSchema(schema) { };

Member::Member(const Schema * schema, size_t offsetInBits) :
	mOffsetInBits(static_cast<unsigned short>(offsetInBits)), mType(static_cast<unsigned char>(TYPE_AGGREGATE)),
	mQualifiers(TYPE_QUALIFIER_NONE), mSchema(schema) { };


