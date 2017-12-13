#include"TypeInfoRegistry.h"

void AddNameForType(const char * strTypeName, const TypeInfo * typeInfo) {
	sNameToType[strTypeName] = typeInfo;
}

void RemoveName(const char * strTypeName) {
	sNameToType.erase(strTypeName);
}

const TypeInfo * GetTypeFromName(const char * strTypeName) {
	if (sNameToType.find(strTypeName) == sNameToType.end()) {
		// Name is not registered yet. 
		return TypeInfo::InvalidType;
	}
	else {
		// Name is registered so return its associated type. 
		return sNameToType[strTypeName];
	}
}

