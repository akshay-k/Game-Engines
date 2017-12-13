#include "Schema.h"
#include<assert.h>
#include<iostream>
using namespace std;

static const size_t BITS_PER_BYTE = 8;

Schema::Schema() : mMembers(), mMemberDictionary(), mContainingSchema(nullptr), mSizeOf(0), mAlignment(0) {}

Schema::Schema(size_t numMembers) : mMembers(), mMemberDictionary(), mContainingSchema(nullptr), 
mSizeOf(0), mAlignment(0) { mMembers.reserve(numMembers); }

Schema::Schema(const char * schemaName, PrimitiveTypeE type) : mMembers(), mMemberDictionary(), 
mContainingSchema(nullptr), mSizeOf(0), mAlignment(0) { 
	mSizeOf = SizeOfType(type); 
	AddMember(type,mSizeOf);
	AddPointerTo(); 
}

Schema::Schema(const char * schemaName, Schema & containingSchema) : mMembers(), mMemberDictionary(), 
mContainingSchema(nullptr), mSizeOf(0), mAlignment(0) { 
	Register(schemaName, containingSchema); 
}

Schema::Schema(Schema * schema, IsPointerE) : mMembers(), mMemberDictionary(), 
mContainingSchema(nullptr), mSizeOf(0), mAlignment(0) { 
	AddMember(TYPE_POINTER, SizeOfType(TYPE_POINTER));
	Finalize(); 
}

Schema::~Schema() {
	DeleteNestedSchemas(); 
	if (mContainingSchema) {   // Another Schema contains this one. 
		Unregister() ;  // Remove this Schema from its container. 
	} 
}

/* static */ bool Schema::IsValidIdentifierName(const char * schemaName) {
	for (const char * character = schemaName; *character != '\0'; ++character) {   
		// For each character in schemaName... 
		if( character != schemaName ) {   // Character is NOT the first one. 
			if( ! isalnum( * character ) && ( * character != '_' ) ) {   
				// Character is neither an alphanumeric nor an underscore. 
				return false ;  // Therefore it is not a valid schema name. 
			} 
		} else {   // Character is the first one. 
			if( ! isalpha( * character ) && ( * character != '_' ) ) {   
				// Character is neither an alphabetic nor an underscore. 
				return false ;  // Therefore it is not a valid schema name. 
			} 
		} 
	} 
	return true ; 
}

bool Schema::HasMember(const char * memberName) const { 
	MemberDictionaryT::const_iterator iter = mMemberDictionary.find(CharPtr(memberName)); 
	return iter != mMemberDictionary.end(); 
}

const size_t & Schema::GetIndexOfMember(const char * memberName) const { 
	MemberDictionaryT::const_iterator iter = mMemberDictionary.find(CharPtr(memberName)); 
	if (iter != mMemberDictionary.end()) { return iter->second; } 
	return MEMBER_INDEX_NONE; 
}

const char * Schema::GetNameOfMember(size_t soughtMemberIndex) const {
	for (MemberDictionaryT::const_iterator iter = mMemberDictionary.begin(); iter != mMemberDictionary.end(); ++iter) {   
		// For each member in Schema... 
		const size_t & memberIndex = iter->second ; 
		if( memberIndex == soughtMemberIndex ) {   // Found sought member. 
			return iter->first;  // Return its name. 
		} 
	} 
	return nullptr ; 
}
		
void Schema::ReserveMembers(size_t numMembers) { mMembers.reserve(numMembers); }

size_t Schema::AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes) { 
	const size_t memberIndex = mMembers.size(); 
	mMembers.push_back(Member(type, qualifiers, BITS_PER_BYTE * memberOffsetInBytes));
	UpdateSizeOfAndAlignment(memberSizeInBytes, memberAlignment); 
	return memberIndex; 
}

size_t Schema::AddMember(PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes) { 
	return AddMember(type, TYPE_QUALIFIER_NONE, memberSizeInBytes, memberAlignment, memberOffsetInBytes); 
}

size_t Schema::AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers, size_t memberSizeInBytes, size_t memberAlignment) { 
	const size_t memberOffset = (TYPE_VOID == type) ? mSizeOf : OffsetInBytesOfMemberWithAlignment(memberAlignment); 
	return AddMember(type, qualifiers, memberSizeInBytes, memberAlignment, memberOffset); 
}

size_t Schema::AddMember(PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberAlignment) { 
	return AddMember(type, TYPE_QUALIFIER_NONE, memberSizeInBytes, memberAlignment); 
}

size_t Schema::AddMember(PrimitiveTypeE type, size_t memberOffsetInBytes) { 
	size_t memberSizeInBytes = SizeOfType(type); size_t memberAlignment = AlignmentOfType(type); 
	return AddMember(type, memberSizeInBytes, memberAlignment, memberOffsetInBytes); 
}

size_t Schema::AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers) { 
	size_t memberSizeInBytes = SizeOfType(type); 
	size_t memberAlignment = AlignmentOfType(type); 
	return AddMember(type, qualifiers, memberSizeInBytes, memberAlignment); 
}

size_t Schema::AddMember(const Schema & schemaOfMember, size_t memberOffsetInBytes) { 
	const size_t memberIndex = mMembers.size(); 
	mMembers.push_back(Member(&schemaOfMember, BITS_PER_BYTE * memberOffsetInBytes)); 
	UpdateSizeOfAndAlignment(schemaOfMember.SizeOf(), schemaOfMember.Alignment()); 
	return memberIndex; 
}

size_t Schema::AddMember(const Schema & schemaOfMember) { 
	const size_t memberOffset = OffsetInBytesOfMemberWithAlignment(schemaOfMember.Alignment()); 
	return AddMember(schemaOfMember, memberOffset); 
}

size_t Schema::AddNamedMember(const char * name, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes) { 
	const size_t memberIndex = AddMember(TYPE_OPAQUE, memberSizeInBytes, memberAlignment, memberOffsetInBytes); 
	mMemberDictionary[CharPtr(name)] = memberIndex; 
	return memberIndex; 
}

size_t Schema::AddNamedMember(const char * name, size_t memberSizeInBytes, size_t memberAlignment) { 
	const size_t memberIndex = AddMember(TYPE_OPAQUE, memberSizeInBytes, memberAlignment); 
	mMemberDictionary[CharPtr(name)] = memberIndex; 
	return memberIndex; 
}

size_t Schema::AddNamedMember(const char * name, PrimitiveTypeE type, size_t memberOffsetInBytes) { 
	const size_t memberIndex = AddMember(type, memberOffsetInBytes); mMemberDictionary[CharPtr(name)] = memberIndex; 
	return memberIndex; 
}

void Schema::Finalize() { mSizeOf = OffsetInBytesOfMemberWithAlignment(mAlignment); }

size_t Schema::OffsetInBytesOfMemberWithAlignment(size_t alignment) const { 
	const size_t discrepancy = (alignment - mSizeOf % alignment) % alignment; 
	const size_t offsetOfMember = mSizeOf + discrepancy; 
	return offsetOfMember; 
}

void Schema::UpdateSizeOfAndAlignment(size_t sizeInBytesOfLastMember, size_t memberAlignment) { 
	const size_t indexOfLastMember = mMembers.size() - 1; 
	const size_t offsetInBitsOfLastMember = mMembers[indexOfLastMember].GetOffsetInBits(); 
	const size_t offsetInBytesOfLastMember = (offsetInBitsOfLastMember + (BITS_PER_BYTE - 1)) / BITS_PER_BYTE; 
	mSizeOf = offsetInBytesOfLastMember + sizeInBytesOfLastMember; 
	mAlignment = mAlignment > memberAlignment ? mAlignment : memberAlignment; 
}

size_t Schema::Alignment() const { return mAlignment; }

Schema::MemberDictionaryT::iterator Schema::FindMemberWithIndex(size_t soughtMemberIndex) {
	for (MemberDictionaryT::iterator iter = mMemberDictionary.begin(); iter != mMemberDictionary.end(); ++iter) {   
		// For each member in Schema... 
		const size_t & memberIndex = iter->second ; 
		if( memberIndex == soughtMemberIndex ) {   // Found sought member. 
			return iter ; 
		} 
	} 
	return mMemberDictionary.end() ; 
}

void Schema::Register(const char * schemaName, Schema & containingSchema) { 
	containingSchema.mNestedSchemas[CharPtr(schemaName)] = this; 
	mContainingSchema = &containingSchema; 
}

Schema * Schema::AddNested(const char * nestedSchemaName) { 
	Schema * newSchema = new Schema(nestedSchemaName, *this);
	return newSchema; 
}

Schema * Schema::GetNested(const char * unqualifiedNestedSchemaName) const {
	SchemaRegistryT::const_iterator item = mNestedSchemas.find(CharPtr(unqualifiedNestedSchemaName)); 
	if (item != mNestedSchemas.end()) {   // Found nested schema with the given name. 
		return item->second ; 
	} 
	return nullptr ;  // Did not find nested Schema with the given name. 
}

Schema * Schema::FindNested_WritableString(char * qualifiedNestedSchemaName) const { 
	// Extract the first scope in the qualified name: 
	char * endOfFirstScopeName = strchr( qualifiedNestedSchemaName , '.' ) ; 
	if( endOfFirstScopeName != nullptr ) {   // Name has a scope resolution specifier. 
		* endOfFirstScopeName = '\0' ; 
		// Terminate name at delimiter so that first part contains scope and second part contains rest. 
		Schema * nestedContainer = GetNested( qualifiedNestedSchemaName ) ; 
		assert( nestedContainer != nullptr ) ; 
		char * restOfName = endOfFirstScopeName + 1 ; 
		return nestedContainer->FindNested_WritableString( restOfName ) ; // Tail recursion. 
	} else {   // Name has no scope resolution specifier. 
		return GetNested( qualifiedNestedSchemaName ) ; 
	} 
}

Schema * Schema::FindNested(const char * qualifiedNestedSchemaName) const { 
	char nameCopy[256]; 
	assert(strlen(qualifiedNestedSchemaName) < sizeof(nameCopy)); 
	strncpy_s(nameCopy, qualifiedNestedSchemaName, sizeof(nameCopy)); 
	return FindNested_WritableString(nameCopy); 
}

Schema * Schema::AddPointerTo() { 
	Schema * newSchema = new Schema(this, IS_POINTER); 
	newSchema->Register("sPtrName", *this);
	return newSchema; 
}

Schema * Schema::GetPointerTo() const {
	SchemaRegistryT::const_iterator item = mNestedSchemas.find(CharPtr("sPtrName")); 
	if (item != mNestedSchemas.end()) {   // Found nested schema with the given name. 
		return item->second ; 
	} 
	return nullptr ;  // Did not find nested Schema with the given name. 
}

Schema * Schema::FindRoot() {
	if (!mContainingSchema) {   // This Schema has no parent, so it is the root. 
		return this ; 
	} else {   // This Schema has a parent, so return its root. 
		return mContainingSchema->FindRoot() ; 
	} 
}

const char * Schema::FindMyName() const {
	if (mContainingSchema) {
		for (SchemaRegistryT::iterator iter = mContainingSchema->mNestedSchemas.begin(); 
			iter != mContainingSchema->mNestedSchemas.end(); ++iter) {   // For each nested Schema in the container... 
			if( iter->second == this ) {   // Found this Schema in its container. 
				return iter->first ; 
			} 
		} 
	} 
	return nullptr ;  // Since this Schema has no container, it has no name. 
}

void Schema::DeleteNestedSchemas() {
	while (!mNestedSchemas.empty()) {   // For each nested Schema in this one... 
		SchemaRegistryT::iterator iter = mNestedSchemas.begin() ; 
		Schema * nestedSchema = iter->second ; 
		nestedSchema->DeleteNestedSchemas() ; // Recurse to delete nested Schemas before deleting container. 
		nestedSchema->~Schema() ; // Explicitly call destructor since this class performed allocation and construction. 
								  // Free the nested Schema. 
		free( nestedSchema ) ; // Schema dtor (which calls Unregister) already Erased nestedSchema from its container (this). 
										   // So do NOT call mNestedSchemas.Erase( iter ) here. 
	} 
}

void Schema::Unregister() {
	for (SchemaRegistryT::iterator iter = mContainingSchema->mNestedSchemas.begin(); iter != mContainingSchema->mNestedSchemas.end(); ++iter) {   
		// For each nested Schema in the container... 
		if( iter->second == this ) {   // Found this Schema in its container. 
			mContainingSchema->mNestedSchemas.erase( iter ) ; 
			break ; 
		} 
	} 
}
/*
void Schema::MakePrimitiveSchemas() {
	if (sVoid != nullptr) {   // Schemas for primitives already exist. 
		return ; 
	} 
	sVoid = new Schema( "void"      , TYPE_VOID     ) ;
	sBool = new Schema( "bool"      , TYPE_BOOL     ) ;
	sInt8 = new Schema( "int8"      , TYPE_INT8     ) ;
	sUInt8 = new Schema( "uint8"     , TYPE_UINT8    ) ; 
	sInt16 = new Schema( "int16"     , TYPE_INT16    ) ; 
	sUInt16 = new Schema( "uint16"    , TYPE_UINT16   ) ; 
	sInt = new Schema( "int"       , TYPE_INT      ) ; 
	sUInt = new Schema( "uint"      , TYPE_UINT     ) ; 
	sInt64 = new Schema( "int64"     , TYPE_INT64    ) ; 
	sUInt64 = new Schema( "uint64"    , TYPE_UINT64   ) ; 
	sFloat = new Schema( "float"     , TYPE_FLOAT    ) ; 
	sDouble = new Schema( "double"    , TYPE_DOUBLE   ) ; 
	sExtended = new Schema( "extended"  , TYPE_EXTENDED ) ; 
	sQuad = new Schema( "quad"      , TYPE_QUAD     ) ; 
	sVector = new Schema( "Vector"    , TYPE_VECTOR   ) ; 
	sMatrix = new Schema( "Matrix"    , TYPE_MATRIX   ) ; 
}
*/

Schema* Schema::sVoid = new Schema("void", TYPE_VOID);
Schema* Schema::sBool = new Schema("bool", TYPE_BOOL);
Schema* Schema::sInt8 = new Schema("int8", TYPE_INT8);
Schema* Schema::sUInt8 = new Schema("uint8", TYPE_UINT8);
Schema* Schema::sInt16 = new Schema("int16", TYPE_INT16);
Schema* Schema::sUInt16 = new Schema("uint16", TYPE_UINT16);
Schema* Schema::sInt = new Schema("int", TYPE_INT);
Schema* Schema::sUInt = new Schema("uint", TYPE_UINT);
Schema* Schema::sInt64 = new Schema("int64", TYPE_INT64);
Schema* Schema::sUInt64 = new Schema("uint64", TYPE_UINT64);
Schema* Schema::sFloat = new Schema("float", TYPE_FLOAT);
Schema* Schema::sDouble = new Schema("double", TYPE_DOUBLE);
Schema* Schema::sExtended = new Schema("extended", TYPE_EXTENDED);
Schema* Schema::sQuad = new Schema("quad", TYPE_QUAD);
Schema* Schema::sVector = new Schema("Vector", TYPE_VECTOR);
Schema* Schema::sMatrix = new Schema("Matrix", TYPE_MATRIX);

void Schema::Print(int indent) const {
	static const char spaces[] = "                                                    "; 
	const char * indentSpaces = &spaces[strlen(spaces) - 4 * indent]; 
	if (mContainingSchema) { 
		printf("%s%s (%p)\n", indentSpaces, FindMyName(), this); 
	}
	else { 
		printf("%s(orphan -- root?) %p\n", indentSpaces, FindMyName(), this); 
	} 
	if (mNestedSchemas.begin() != mNestedSchemas.end()) { 
		printf("%sRecursive NestedSchemas:\n", indentSpaces); 
	} 
	for (SchemaRegistryT::const_iterator iter = mNestedSchemas.begin(); iter != mNestedSchemas.end(); ++iter) {   
		// For each nested Schema in the container... 
		iter->second->Print( indent + 1 ) ; 
	}
	/*
	if( ! mNestedSchemas.empty() ) { 
		printf( "%sNestedSchemas:\n" , indentSpaces ) ; 
		mNestedSchemas.Print(0) ; 
	} 
	*/
	if( ! mMemberDictionary.empty() ) { 
		printf( "%sMembers:\n" , indentSpaces ) ; 
		for (MemberDictionaryT::const_iterator iter = mMemberDictionary.begin(); iter != mMemberDictionary.end(); ++iter) {
			// For each nested Schema in the container... 
			printf("%s : %d \n",iter->first, mMembers[iter->second].GetType());
		}
	} 
	
	printf( "\n" ) ; 
}

void Schema::Extend(const Schema & base) {

}



