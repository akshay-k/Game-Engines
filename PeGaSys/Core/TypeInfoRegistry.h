#pragma once
#ifndef TYPEINFOREGISTRY_H
#define TYPEINFOREGISTRY_H
#include"TypeInfo.h"
#include<map>
#include<string>
using namespace std;

typedef map< const char *, const TypeInfo * > NameToTypeDictionaryT;

static NameToTypeDictionaryT sNameToType;   ///< Map a type name to its type identifier.

void AddNameForType(const char * strTypeName, const TypeInfo * typeInfo);

void RemoveName(const char * strTypeName);

const TypeInfo * GetTypeFromName(const char * strTypeName);


#endif // !TYPEINFOREGISTRY_H

