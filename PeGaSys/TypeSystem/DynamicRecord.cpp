#include "DynamicRecord.h"

DynamicRecord * DynamicRecord::GetRoot() {
	DynamicRecord * ancestor = this; // Maybe this is the root. 
	while (ancestor->GetOwner() != nullptr) {
		ancestor = ancestor->GetOwner();
	}
	return ancestor;
}

size_t DynamicRecord::Add(const char * name, PrimitiveTypeE type, TypeQualiferE qualifiers) {
	if (Schema::MEMBER_INDEX_NONE == mOffsetFirstDynamicMember) {   // This is the first non-native member. 
		mOffsetFirstDynamicMember = mSchema.GetNumMembers(); // Remember offset of first non-native member. 
	}
	mPrimitiveValues.push_back(PrimitiveValue());
	return mSchema.AddNamedMember(name, type, qualifiers);
}

size_t DynamicRecord::Add(const char * name, const TypedValue & initialValue /* reference to allow for declared alignment */, TypeQualiferE qualifiers) {
	const size_t memberIndex = Add(name, initialValue.GetType(), qualifiers);
	SetMember(memberIndex, initialValue.GetValue());
	return memberIndex;
}

size_t DynamicRecord::AddMethod(const char * name, InstanceMethodP method) {
	TypedValue tvMethod(method);
	const size_t memberIndex = Add(name, tvMethod, TYPE_QUALIFIER_CONST_REFERENT);
	return memberIndex;
}

size_t DynamicRecord::AddNonOwning(const char * name, DynamicRecord * objectToReference,
	TypeQualiferE qualifiers) {
	const size_t memberIndex = Add(name, TYPE_REFERENCE, qualifiers);
	GetMemberValue(memberIndex).mR = objectToReference; return memberIndex;
}

size_t DynamicRecord::AddOwning(const char * name, DynamicRecord * objectToAdopt,
	TypeQualiferE qualifiers) {
	const size_t memberIndex = Add(name, TYPE_REFERENCE, static_cast< TypeQualiferE >(TYPE_QUALIFIER_OWNS_REFERENT | qualifiers));
	GetMemberValue(memberIndex).mR = objectToAdopt; objectToAdopt->SetOwner(this);
	return memberIndex;
}

char* Indent(int j) {
	char *arr = new char[j];
	for (int i = 0; i < j; i++)        //num_space_req < 20  
	{
		arr[i] = ' ';
	}
	arr[j] = '\0';
	return arr;
}

//void DynamicRecord::DebugPrint(int indent) const {
//	const size_t numMembers = mSchema.GetNumMembers(); 
//	for (size_t idx = 0; idx < numMembers; ++idx) {   // For each member.. 
//		const PrimitiveValue & pv = GetMemberValue( idx ) ;
//		const Member & member = mSchema[ idx ] ; 
//		const char * strName = mSchema.GetNameOfMember( idx ) ; 
//		assert( strName != 0 ) ; 
//		printf( "%s[%i] '%s' = " , Indent(indent) , idx , strName ) ; 
//		switch( member.GetType() ) { 
//		case TYPE_BOOL              : 
//			printf( "(bool) %s\n" , pv.mB ? "true" : "false" ) ; 
//			break ; 
//		case TYPE_INT8              : 
//			printf( "(int8) %hhi\n" , pv.mI8 ) ; 
//			break ; 
//		case TYPE_UINT8             : 
//			printf( "(uint8) %hhu\n" , pv.mU8 ) ; 
//			break ; 
//		case TYPE_INT16             : 
//			printf( "(int16) %hi\n" , pv.mI16 ) ; 
//			break ; 
//		case TYPE_UINT16            : 
//			printf( "(uint16) %hu\n" , pv.mU16 ) ; 
//			break ; 
//		case TYPE_INT               : 
//			printf( "(int) %i\n" , pv.mI ) ; 
//			break ; 
//		case TYPE_UINT              : 
//			printf( "(uint) %u\n" , pv.mU32 ) ; 
//			break ; 
//		case TYPE_INT64             : 
//			printf( "(int64) %lli\n" , pv.mI64 ) ; 
//			break ; 
//		case TYPE_UINT64            : 
//			printf( "(uint64) %llu\n" , pv.mU64 ) ; 
//			break ; 
//		case TYPE_FLOAT             : 
//			printf( "(float) %g\n" , pv.mF ) ; 
//			break ; 
//		case TYPE_DOUBLE            : 
//			printf( "(double) %g\n" , pv.mF64 ) ; 
//			break ; 
//		case TYPE_QUAD              : 
//			printf( "(quad) %Lg\n" , pv.mF128 ) ; 
//			break ; 
//		case TYPE_STRING            : 
//			printf( "(str) '%s'\n" , pv.mS ) ; 
//			break ; 
//		case TYPE_VECTOR            : 
//			printf( "(vec) %g %g %g %g\n" , pv.mV.getX() , pv.mV.getY() , pv.mV.getZ() , pv.mV.getW() ) ; 
//			break ; 
//		case TYPE_MATRIX            : 
//			printf( "(mat)\n" ) ; 
//			break ; 
//		case TYPE_POINTER           : 
//			printf( "(ptr) %p\n" , pv.mP ) ; 
//			break ; 
//		case TYPE_FUNCTION          : 
//			printf( "(function) %p\n" , pv.mFnc ) ; 
//			break ; 
//		case TYPE_INSTANCE_METHOD   :
//			printf( "(instmethod) %p\n" , pv.mIMF ) ; 
//			break ; 
//		case TYPE_CLASS_METHOD      : 
//			 printf( "(clsMethod) %p\n" , pv.mCMF ) ; 
//			 break ; 
//		case TYPE_REFERENCE         : 
//			printf( "(ref) %p\n" , pv.mR ) ; 
//			const DynamicRecord * dynRec = ( pv.mR != nullptr ) ? ReinterpretCast( pv.mR ) : nullptr ; 
//			if( ( dynRec != nullptr ) && Owns( dynRec ) ) {   
//				// This record owns current member record; recurse to print child. 
//				dynRec->DebugPrint( indent + 4 ) ; 
//			} 
//			break ; 
//		} 
//	} 
//}

void DynamicRecord::ShallowCopyValues(const DynamicRecord & that) {
	const size_t srcNumMembers = that.mSchema.GetNumMembers();
	mPrimitiveValues.reserve(srcNumMembers); // Reserve space for the members. 
	for (size_t idx = 0; idx < srcNumMembers; ++idx) {   // For each member in source object. 
		mPrimitiveValues.push_back(that.mPrimitiveValues[idx]);
	}
}

void DynamicRecord::TransferOwner(DynamicRecord * newOwner) {
	DynamicRecord * oldOwner = const_cast< DynamicRecord * >(GetOwner()); // This is the only place where mOwner is treated as mutable. 
	const size_t idxRefMember = oldOwner->FindOwningReference(this);
	PrimitiveValue & oldOwnerRefMember_ = oldOwner->mPrimitiveValues[idxRefMember];
	oldOwnerRefMember_.mR = nullptr;
	mOwner = nullptr;
	SetOwner(newOwner);
}

void DynamicRecord::Clear() {
	const size_t numMembers = mSchema.GetNumMembers();
	for (size_t idx = mOffsetFirstDynamicMember; idx < numMembers; ++idx) {   // For each dynamic member... 
		const Member & member = mSchema[idx];
		if ((member.GetType() == TYPE_REFERENCE) && member.HasQualifier(TYPE_QUALIFIER_OWNS_REFERENT)) {
			// Member is an owning reference. 
			RecordBasePtr & record = GetMemberValue(idx).mR;
			if (record != nullptr) {
				DynamicRecord * dynRec = ReinterpretCast(record);
				delete dynRec; record = nullptr;
			}
		}
	}
	mSchema.Clear();
}

size_t DynamicRecord::FindOwningReference(const DynamicRecord * that) const {
	for (size_t idx = 0; idx < mPrimitiveValues.size(); ++idx) {   // For each member in this object... 
		const Member & member = mSchema[idx];
		if ((member.GetType() == TYPE_REFERENCE) && member.HasQualifier(TYPE_QUALIFIER_OWNS_REFERENT)) {
			// Member is an owning reference. 
			const PrimitiveValue & pv = mPrimitiveValues[idx];
			if (pv.mR == that) {
				return idx;
			}
		}
	}
	return Schema::MEMBER_INDEX_NONE;
}

PrimitiveValue & DynamicRecord::GetMemberValue(size_t memberIndex) {
	const size_t dynamicMemberIndex = memberIndex - mOffsetFirstDynamicMember;
	return mPrimitiveValues[dynamicMemberIndex];
}

DynamicRecord::DynamicRecord() : mOwner(nullptr), mOffsetFirstDynamicMember(Schema::MEMBER_INDEX_NONE) {}

DynamicRecord::DynamicRecord(Schema &schema) {
	mOwner = nullptr;
	mOffsetFirstDynamicMember = Schema::MEMBER_INDEX_NONE;
	mSchema = schema;
}

DynamicRecord::DynamicRecord(const DynamicRecord & that) { mSchema.Extend(that.mSchema); ShallowCopyValues(that); }

const Schema * DynamicRecord::GetSchema() const { return &mSchema; }

DynamicRecord * DynamicRecord::GetOwner() { return mOwner; }

const DynamicRecord * DynamicRecord::GetOwner() const { return mOwner; }

void DynamicRecord::Reserve(size_t numMembers) {
	mSchema.ReserveMembers(numMembers);
	mPrimitiveValues.reserve(numMembers);
}

DynamicRecord::~DynamicRecord() {};
bool & DynamicRecord::Bool(size_t memberIndex) { return GetMemberValue(memberIndex).mB; }

bool & DynamicRecord::Bool(const char * memberName) { return Bool(Index(memberName)); }

int & DynamicRecord::Int(size_t memberIndex) { return GetMemberValue(memberIndex).mI; }

int & DynamicRecord::Int(const char * memberName) { return Int(Index(memberName)); }

const int & DynamicRecord::Int(size_t memberIndex) const { return GetMemberValue(memberIndex).mI; }

const int & DynamicRecord::Int(const char * memberName) const { return Int(Index(memberName)); }

long long & DynamicRecord::Int64(size_t memberIndex) { return GetMemberValue(memberIndex).mI64; }

long long & DynamicRecord::Int64(const char * memberName) { return Int64(Index(memberName)); }

unsigned long long & DynamicRecord::UInt64(size_t memberIndex) { return GetMemberValue(memberIndex).mU64; }

unsigned long long & DynamicRecord::UInt64(const char * memberName) { return UInt64(Index(memberName)); }

float & DynamicRecord::Flt(size_t memberIndex) { return GetMemberValue(memberIndex).mF; }

float & DynamicRecord::Flt(const char * memberName) { return Flt(Index(memberName)); }

const float & DynamicRecord::Flt(size_t memberIndex) const { return GetMemberValue(memberIndex).mF; }

const float & DynamicRecord::Flt(const char * memberName) const { return Flt(Index(memberName)); }

double & DynamicRecord::Dbl(size_t memberIndex) { return GetMemberValue(memberIndex).mF64; }

double & DynamicRecord::Dbl(const char * memberName) { return Dbl(Index(memberName)); }

Math3D::Vector4 & DynamicRecord::Vec(size_t memberIndex) { return GetMemberValue(memberIndex).mV; }

Math3D::Vector4 & DynamicRecord::Vec(const char * memberName) { return Vec(Index(memberName)); }

Math3D::Matrix44Ptr & DynamicRecord::Mtx(size_t memberIndex) { return GetMemberValue(memberIndex).mX; }

Math3D::Matrix44Ptr & DynamicRecord::Mtx(const char * memberName) { return Mtx(Index(memberName)); }

void * & DynamicRecord::Ptr(size_t memberIndex) { return GetMemberValue(memberIndex).mP; }

void * & DynamicRecord::Ptr(const char * memberName) { return Ptr(Index(memberName)); }

RecordBase * & DynamicRecord::Ref(size_t memberIndex) { return GetMemberValue(memberIndex).mR; }

RecordBase * & DynamicRecord::Ref(const char * memberName) { return Ref(Index(memberName)); }

InstanceMethodP & DynamicRecord::InstMethod(size_t memberIndex) { return GetMemberValue(memberIndex).mIMF; }

InstanceMethodP & DynamicRecord::InstMethod(const char * memberName) { return InstMethod(Index(memberName)); }

ClassMethodPointer & DynamicRecord::ClassMethod(size_t memberIndex) { return GetMemberValue(memberIndex).mCMF; }

ClassMethodPointer & DynamicRecord::ClassMethod(const char * memberName) { return ClassMethod(Index(memberName)); }

const DynamicRecord * DynamicRecord::ReinterpretCast(const RecordBase * record) {
const DynamicRecord * dynRec = ReinterpretCastPtr< const DynamicRecord >(record);
return dynRec;
}

DynamicRecord * DynamicRecord::ReinterpretCast(RecordBase * record) {
	DynamicRecord * dynRec = ReinterpretCastPtr< DynamicRecord >(record);
	return dynRec;
}

const size_t & DynamicRecord::Index(const char * memberName) const { return mSchema.GetIndexOfMember(memberName); }

bool DynamicRecord::Owns(const DynamicRecord * that) const { 
	return FindOwningReference(that) != Schema::MEMBER_INDEX_NONE; 
}

const PrimitiveValue & DynamicRecord::GetMemberValue(size_t memberIndex) const {
	return const_cast<DynamicRecord *>(this)->GetMemberValue(memberIndex);
}
void DynamicRecord::SetMember(size_t memberIndex, const PrimitiveValue & primitiveValue) {
	memcpy(&GetMemberValue(memberIndex), &primitiveValue,
		sizeof(GetMemberValue(memberIndex)));
}

void DynamicRecord::SetOwner(DynamicRecord * owner) { mOwner = owner; }