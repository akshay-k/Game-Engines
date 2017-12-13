#pragma once
#ifndef SCHEMA_H
#define SCHEMA_H
#include "Member.h"
#include<map>
#include<vector>
using namespace std;
class Schema
{
public: 
	enum IsPointerE { IS_POINTER };
	Schema(); 
	explicit Schema(size_t numMembers); 
	Schema(const char * schemaName, PrimitiveTypeE type); 
	Schema(const char * schemaName, Schema & containingSchema); 
	Schema(Schema *, IsPointerE); ~Schema(); 
	const Member &  operator[](size_t memberIndex) const { return mMembers[memberIndex]; } 
	const Member &  GetMember(const char * memberName) const { return operator[](GetIndexOfMember(memberName)); }
	bool HasMember(const char * memberName) const; const size_t & GetIndexOfMember(const char * memberName) const; 
	const char * GetNameOfMember(size_t memberIndex) const; 
	const size_t Offset(size_t memberIndex) const { return mMembers[memberIndex].GetOffsetInBytes(); } 
	const size_t &  SizeOf() const { return mSizeOf; } 
	const size_t GetNumMembers() const { return mMembers.size(); } 
	const size_t Capacity() const { return mMembers.capacity(); } 
	void ReserveMembers(size_t numMembers); 
	size_t AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes); 
	size_t AddMember(PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes); 
	size_t AddMember(PrimitiveTypeE type, size_t memberOffsetInBytes); 
	size_t AddMember(const Schema & schemaOfMember, size_t memberOffsetInBytes); 
	size_t AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers, size_t memberSizeInBytes, size_t memberAlignment); 
	size_t AddMember(PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberAlignment); 
	size_t AddMember(PrimitiveTypeE type, TypeQualiferE qualifiers); 
	//size_t AddMember(PrimitiveTypeE type); 
	size_t AddMember(const Schema & schemaOfMember); 
	size_t AddNamedMember(const char * name, size_t memberSizeInBytes, size_t memberAlignment, size_t memberOffsetInBytes); 
	size_t AddNamedMember(const char * name, PrimitiveTypeE type, size_t memberOffsetInBytes); 
	//size_t AddNamedMember(const char * name, const Schema & schemaOfMember, size_t memberOffsetInBytes); 
	size_t AddNamedMember(const char * name, size_t memberSizeInBytes, size_t memberAlignment); 
	//size_t AddNamedMember(const char * name, PrimitiveTypeE type, TypeQualiferE qualifiers); 
	//size_t AddNamedMember(const char * name, PrimitiveTypeE type); 
	//size_t AddNamedMember(const char * name, const Schema & schemaOfMember);
	//void RemoveDynamicMember(size_t memberIndex, bool preserveOrder);
	void Finalize();
	void Extend(const Schema & base); 
	size_t Alignment() const; 
	/*
	void PlacementNewRecord(void * address) const; 
	void PlacementNewRecords(void * address, size_t numRecords) const; 
	void * NewRecord() const; 
	void * NewRecords(size_t numRecords) const; 
	void PlacementDeleteRecord(void * recordAddress) const; 
	void PlacementDeleteRecords(void * recordAddress, size_t numRecords) const; 
	void DeleteRecord(void * recordAddress) const; 
	void DeleteRecords(void * recordAddress, size_t numRecords) const; 
	*/
	Schema * AddNested(const char * nestedSchemaName); 
	Schema * GetNested(const char * unqualifiedNestedSchemaName) const; 
	Schema * FindNested(const char * qualifiedNestedSchemaName) const; 
	Schema * AddPointerTo(); 
	Schema * GetPointerTo() const; 
	Schema & Ptr() const { return *GetPointerTo(); } 
	Schema * FindRoot(); 
	const char * FindMyName() const; 
	void DeleteNestedSchemas(); 
	//bool IsFunction() const; 
	//TODO:: 
	void Clear() { printf("There is no code here. Schema::Clear()"); };
	void Print(int indent = 0) const;
	bool IsValidIdentifierName(const char * schemaName);
	

	static const size_t MEMBER_INDEX_NONE = ~size_t(0); /// index value indicating no-such-member.
	/// Schemas representing primitive types. 
	
	static Schema * sVoid ; 
	static Schema * sBool ;
	static Schema * sInt8 ; 
	static Schema * sUInt8 ; 
	static Schema * sInt16 ; 
	static Schema * sUInt16 ; 
	static Schema * sInt ; 
	static Schema * sUInt ; 
	static Schema * sInt64 ; 
	static Schema * sUInt64 ; 
	static Schema * sFloat ; 
	static Schema * sDouble ; 
	static Schema * sExtended ; 
	static Schema * sQuad ; 
	static Schema * sVector ; 
	static Schema * sMatrix ;
	static void MakePrimitiveSchemas();

private: 
	//typedef AllocatorAdapter< Member > MemberAllocatorT; 
	//typedef vector< Member, MemberAllocatorT > MembersT;
	//typedef AllocatorAdapter< size_t > MemberIndexAllocatorT; 
	typedef char * CharPtr;
	typedef /*const*/ CharPtr NameT;   // TODO: FIXME: Reinstate "const". 
	//typedef map< NameT , size_t , hash< NameT > , MemberIndexAllocatorT /**/ > MemberDictionaryT ;
	typedef map< NameT, size_t> MemberDictionaryT;
	typedef map< NameT, Schema * >  SchemaRegistryT;
	Schema(const Schema & that);             ///< Catch attempt to copy Schema. 
	//Schema & operator=( const Schema & that ) ; ///< Catch attempt to copy Schema.
	void Register(const char * schemaName, Schema & containingSchema);
	MemberDictionaryT::iterator FindMemberWithIndex(size_t soughtMemberIndex);
	//size_t CopyMember(PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberOffsetInBits); 
	//size_t CopyNamedMember(const char * name, PrimitiveTypeE type, size_t memberSizeInBytes, size_t memberOffsetInBits);
	//bool CandidateMemberOverlapsExistingMember(size_t offset, size_t size) const; 
	size_t OffsetInBytesOfMemberWithAlignment(size_t alignment) const; 
	void UpdateSizeOfAndAlignment(size_t sizeInBytesOfLastMember, size_t memberAlignment); 
	//void CopyMember(const Schema & base, size_t baseMemberIndex);
	Schema * FindNested_WritableString(char * qualifiedNestedSchemaName) const; 
	void Unregister();

	//IAllocator *        mAllocator;   ///< Allocator used to allocate nested Schemas and Members. 
	//MembersT mMembers ;   ///< Array of instance members. 
	vector<Member> mMembers;
	MemberDictionaryT mMemberDictionary ;   ///< Map from name to member index. 
	Schema * mContainingSchema ;   ///< Schema that contains this one. 
	SchemaRegistryT mNestedSchemas ;   ///< Schemas that reside in the namespace of this one. 
	size_t mSizeOf ;   ///< Size in bytes of a record that this Schema describes, including padding and alignment. 
	size_t mAlignment ;   ///< Alignment in bytes of address of a record that this Schema describes.
	//static size_t sCount;   ///< Global count of Schema objects, used for detecting memory leaks. static const char * const REMOVED_MEMBER_NAME     ;   ///  Placeholder name for a member that was removed

};
#endif //SCHEMA_H