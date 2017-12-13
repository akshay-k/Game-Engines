#include "RecordBase.h"

RTTI_DEFINITIONS(RecordBase);

IGeneric * RecordBase::QueryInterface(const TypeInfo & typeInfo) {
	if (TypeId< RecordBase >() == typeInfo) {
		return static_cast< RecordBase * >(this);
	}
	else {
		return nullptr;
	}
}

void RecordBase::Invoke(const char * methodName, Arguments & args) {
	const size_t iMember = GetSchema()->GetIndexOfMember(methodName);
	if (iMember != Schema::MEMBER_INDEX_NONE) {   // Child has member with given name. 
		const Member & member = GetSchema()->operator[](iMember);
		if (member.GetType() == TYPE_INSTANCE_METHOD) {   // Member is a class method. 
			const InstanceMethodP methodPtr = InstMethod(iMember);
			(methodPtr.function)(&args);
		}
		else if (member.GetType() == TYPE_CLASS_METHOD) {   // Member is a class method. 
			const ClassMethodPointer methodPtr = ClassMethod(iMember);
			methodPtr.function(this, &args);
		}
	}
}

void RecordBase::InvokeDescendants(const char * methodName, Arguments & args) {
	for (size_t iChild = 0; iChild < GetSchema()->GetNumMembers(); ++iChild) {   // For each child... 
		const Member & member = GetSchema()->operator[](iChild);
		if ((member.GetType() == TYPE_REFERENCE) && (member.HasQualifier(TYPE_QUALIFIER_OWNS_REFERENT))) {
			// Child is a record owned by this one. 
			RecordBase * record = Ref(iChild);
			record->Invoke(methodName, args); // Invoke given method on child. 
			record->InvokeDescendants(methodName, args);    // Invoke given method on grandchildren. 
		}
	}
}
