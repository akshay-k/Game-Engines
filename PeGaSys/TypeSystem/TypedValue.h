#pragma once
#ifndef TYPEDVALUE_H
#define TYPEDVALED_H
#include<assert.h>
#include"Primitive.h"
using namespace std;

//TypedValue class to represent a single typed value
class TypedValue {
	PrimitiveTypeE mType;
	PrimitiveValue mValue;
	TypeQualiferE mQualifiers;

public: 
	explicit TypedValue(PrimitiveTypeE type = TYPE_UNKNOWN) : mType(type), mQualifiers(TYPE_QUALIFIER_NONE) { memset(&mValue, 0, sizeof(mValue)); } 
	explicit TypedValue(bool b) : mType(TYPE_BOOL), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mB = b; } 
	explicit TypedValue(char c) : mType(TYPE_INT8), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mI8 = c; } 
	explicit TypedValue(unsigned char uc) : mType(TYPE_UINT8), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mU8 = uc; } 
	explicit TypedValue(short s) : mType(TYPE_INT16), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mI16 = s; } 
	explicit TypedValue(unsigned short us) : mType(TYPE_UINT16), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mU16 = us; } 
	explicit TypedValue(int i) : mType(TYPE_INT), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mI = i; } 
	explicit TypedValue(unsigned u) : mType(TYPE_UINT), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mU32 = u; } 
	explicit TypedValue(long long i) : mType(TYPE_INT64), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mI64 = i; } 
	explicit TypedValue(unsigned long long u) : mType(TYPE_UINT64), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mU64 = u; } 
	explicit TypedValue(float f) : mType(TYPE_FLOAT), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mF = f; } 
	explicit TypedValue(double f64) : mType(TYPE_DOUBLE), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mF64 = f64; } 
	explicit TypedValue(const Math3D::Vector4 & v) : mType(TYPE_VECTOR), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mV = v; } 
	explicit TypedValue(Math3D::Matrix44Ptr x) : mType(TYPE_MATRIX), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mX = x; } 
	//explicit TypedValue(Mat44Ptr x) : mType(TYPE_MATRIX), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mX = reinterpret_cast< Math::Matrix44Ptr >(x); } 
	explicit TypedValue(char * s) : mType(TYPE_STRING), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mS = s; } 
	explicit TypedValue(void * p) : mType(TYPE_POINTER), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mP = p; } 
	explicit TypedValue(FunctionP f) : mType(TYPE_FUNCTION), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mFnc = f; } 
	explicit TypedValue(InstanceMethodP instM) : mType(TYPE_INSTANCE_METHOD), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mIMF = instM; } 
	explicit TypedValue(ClassMethodPointer clsM) : mType(TYPE_CLASS_METHOD), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mCMF = clsM; } 
	explicit TypedValue(class RecordBase * r) : mType(TYPE_REFERENCE), mQualifiers(TYPE_QUALIFIER_NONE) { mValue.mR = r; } 
	explicit TypedValue(const char * s) : mType(TYPE_STRING), mQualifiers(TYPE_QUALIFIER_CONST_REFERENT) { mValue.mS = const_cast< char * >(s); } 
	explicit TypedValue(const void * p) : mType(TYPE_POINTER), mQualifiers(TYPE_QUALIFIER_CONST_REFERENT) { mValue.mP = const_cast< void * >(p); } 
	TypedValue(class RecordBase * r, TypeQualiferE typeQualifier) : mType(TYPE_REFERENCE), mQualifiers(typeQualifier) { mValue.mR = r; }
	

	
	void SetType(PrimitiveTypeE type) { mType = type; } 
	const PrimitiveTypeE & GetType() const { return mType; } 
	const PrimitiveValue & GetValue() const { return mValue; } 
	bool & GetBool() { 
		assert(mType == TYPE_BOOL && mQualifiers != TYPE_QUALIFIER_PRIVATE); 
		return mValue.mB; 
	} 
	const bool & GetBool() const { 
		assert(mType == TYPE_BOOL && mQualifiers != TYPE_QUALIFIER_PRIVATE); 
		return mValue.mB; 
	}
	const RecordBasePtr & GetReference() const { 
		assert(mType == TYPE_REFERENCE && mQualifiers != TYPE_QUALIFIER_PRIVATE); 
		return mValue.mR; 
	} 
	RecordBasePtr & GetReference() { 
		assert(mType == TYPE_REFERENCE && mQualifiers != TYPE_QUALIFIER_PRIVATE); 
		return mValue.mR; 
	}
	bool IsConstValue() const { return (mQualifiers & TYPE_QUALIFIER_CONST_VALUE) ? true : false; } 
	void SetConstValue() { mQualifiers = static_cast< TypeQualiferE >(mQualifiers | TYPE_QUALIFIER_CONST_VALUE); }
	bool IsConstReferent() const { return (mQualifiers & TYPE_QUALIFIER_CONST_REFERENT) ? true : false; } 
	void SetConstReferent() { mQualifiers = static_cast< TypeQualiferE >(mQualifiers | TYPE_QUALIFIER_CONST_REFERENT); }
	void SetBool(const bool value) { 
		assert(mType == TYPE_BOOL);
		assert(!IsConstValue());
		mValue.mB = value; 
	}

	void SetMatrix( Math3D::Matrix44Ptr value ) { 
		assert( mType == TYPE_MATRIX) ; 
		assert( ! IsConstValue() ) ; 
		mValue.mX = value ; 
	}

	void SetString( char * value ) { 
		assert( mType == TYPE_STRING) ;
		assert( ! IsConstValue() ) ;
		mValue.mS = value ; 
	}

	void SetConstString( const char * value ) { 
		assert( mType == TYPE_STRING) ;
		SetConstValue() ; 
		SetConstReferent() ; 
		mValue.mS = const_cast< char * >( value ) ; 
	}

	void SetPointer( void * value ) { 
		assert( mType == TYPE_POINTER) ;
		assert( ! IsConstValue() ) ; 
		mValue.mP = value ; 
	}

	void SetFunction( const FunctionP value ) { 
		assert( mType == TYPE_FUNCTION) ;
		assert( ! IsConstValue() ) ;
		mValue.mFnc = value ; 
	}

	void SetInstanceMethod( const InstanceMethodP value ) { 
		assert( mType == TYPE_INSTANCE_METHOD) ;
		assert( ! IsConstValue() ) ;
		mValue.mIMF = value ; 
	}

	void SetClassMethod( const ClassMethodPointer value ) { 
		assert( mType == TYPE_CLASS_METHOD) ;
		assert( ! IsConstValue() ) ; 
		mValue.mCMF = value ; 
	}

	void SetReference( RecordBase * value ) { 
		assert( mType == TYPE_REFERENCE) ;
		assert( ! IsConstValue() ) ; 
		mValue.mR = value ; 
	}

	void CopyMatrix( const Math3D::Matrix44Ptr & value )  { 
		assert( mType == TYPE_MATRIX) ; 
		assert( ! IsConstReferent() ) ; 
		* mValue.mX = * value ; 
	}

	void CopyString( const char * value ) { 
		assert( mType == TYPE_STRING) ; 
		assert( ! IsConstReferent() ) ; 
		memcpy( mValue.mS , value , strlen( value ) ) ; 
	}

	bool operator==( const TypedValue & that ) const { return operator==(that); }
	bool operator!=( const TypedValue & that ) const { return ! operator==( that ) ; } 


	TypedValue & operator= (const TypedValue & rhs) { 
		mType = rhs.mType;
		memcpy( & mValue , & rhs.mValue , sizeof(mValue) ) ;
		mQualifiers = rhs.mQualifiers;
		return *this;
	}

};
#endif // !TYPEDVALUE_H

