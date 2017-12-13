#include "TypeInfo.h"

TypeInfo::TypeInfo(const char * strName) : mName(strName) {}
TypeInfo::~TypeInfo() {};

bool TypeInfo::operator==(const TypeInfo & that) const { return mName == that.mName; };
bool TypeInfo::operator!=(const TypeInfo & that) const { return mName != that.mName; };

const char * TypeInfo::Name() const { return mName; };


const TypeInfo * TypeInfo::InvalidType = new TypeInfo(0);
