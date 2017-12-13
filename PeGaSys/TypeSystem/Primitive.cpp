#include"Primitive.h"

const size_t & SizeOfType(PrimitiveTypeE type) { 
	return sTypeSizeAlignmentMap[type].mSizeOf; 
}

const size_t & AlignmentOfType(PrimitiveTypeE type) { 
	return sTypeSizeAlignmentMap[type].mAlignmentOf;
}

PrimitiveValue::~PrimitiveValue() {

}
PrimitiveValue::PrimitiveValue() {

}