#pragma once
#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include<map>
#include<vector>
#include<math.h>
#include"Matrix44.h"
class IRecord;
class Arguments;
class RecordBase;
typedef RecordBase* RecordBasePtr;

enum PrimitiveTypeE {
	TYPE_UNKNOWN,   ///< Unknown type -- used for forward references during parsing 
	// Common primitive types. 
	TYPE_VOID           ,   ///< Void (no value) 
	TYPE_BOOL           ,   ///< Boolean 
	TYPE_INT8           ,   ///< 8-bit integer (signed) 
	TYPE_UINT8          ,   ///< 8-bit integer (unsigned) 
	TYPE_INT16          ,   ///< 16-bit integer (signed) 
	TYPE_UINT16         ,   ///< 16-bit integer (unsigned) 
	TYPE_INT            ,   ///< 32-bit integer (signed) 
	TYPE_UINT           ,   ///< 32-bit integer (unsigned) 
	TYPE_INT64          ,   ///< 64-bit integer (signed) 
	TYPE_UINT64         ,   ///< 64-bit integer (unsigned) 
	TYPE_FLOAT          ,   ///< Single-precision (32-bit) floating-point value 
	TYPE_DOUBLE         ,   ///< Double-precision (64-bit) floating-point value 
	TYPE_EXTENDED       ,   ///< Extended precision (80-bit) floating-point value. 
	TYPE_QUAD           ,   ///< Quad-precision (128-bit) floating-point value. 
	// Atypical primitives that nevertheless have hardware support. 
	TYPE_VECTOR         ,   ///< 4-vector 
	TYPE_MATRIX         ,   ///< 4x4 matrix 
	// Compound type that gets special treatment. 
	TYPE_STRING         ,   ///< character (text) string 
	// Meta-types 
	TYPE_POINTER        ,   ///< pointer to a type defined elsewhere. 
	TYPE_FUNCTION       ,   ///< pointer to a function or static (a.k.a. class) method 
	TYPE_INSTANCE_METHOD,   ///< pointer to an instance member function that is invoked on object operated on.  
							///< Can be used to wrap instance methods.
	TYPE_CLASS_METHOD   ,   ///< pointer to a class member function that takes a IRecord* as its first argument for the object operated on.  
							///< Can be used to wrap native instance methods. 
	TYPE_AGGREGATE      ,   ///< Aggregate type, such as a struct or array, that has a Schema. 
	TYPE_OPAQUE         ,   ///< Opaque type that has no Schema; only its size and alignment are known. 
	TYPE_REFERENCE      ,   ///< reference to a object whose type a Schema describes. 
	TYPE_INVALID            ///< Invalid type, e.g. unassigned or used to indicate an error. 
};
typedef enum PrimitiveTypeE PrimitiveTypeE;

/*
static const char * PrimitiveTypeStrings[] = { "Void", "Bool", "Pointer", "Unknown", "Char", "String",
	"UShortInt", "ShortInt", "UInt", "Int", "ULongInt", "LongInt",
	"Float", "Double",
	"Vector", "Composite"};
const char * getTextForPrimitiveType(int);
*/
/* ------------------------------------------------------------------------------------------------------- */
/*
typedef struct Vec4 {
	float x, y, z, w;
}Vec4;

typedef struct Mat44 {
	void ** mat;
}Mat44;

typedef Mat44* Matrix44Ptr;
*/
typedef struct InstanceMethodP {
	void* object;
	void(*function) (Arguments * arguments);
}InstanceMethodP;

typedef struct FunctionP {
	void (* function) (Arguments * arguments);
}FunctionP;

typedef struct ClassMethodPointer {
	void(*function) (IRecord * irecord, Arguments * arguments);
}ClassMethodPointer;

/* ------------------------------------------------------------------------------------------------------- */
typedef enum TypeQualiferE {
	TYPE_QUALIFIER_NONE = 0, 
	TYPE_QUALIFIER_CONST_VALUE = 1,   /// Value of this variable itself is immutable.  
									  /// For pointers, this means the value of the pointer, not the referent, cannot change 
	TYPE_QUALIFIER_CONST_REFERENT   = 2 ,   /// Referent is immutable via this (pointer or reference) variable.  
											/// Only applies to pointer types. 
	TYPE_QUALIFIER_OWNS_REFERENT    = 4 ,   /// Object owns referent. 
	TYPE_QUALIFIER_PRIVATE          = 8 ,   /// Direct access to variable not allowed 
	//TYPE_QUALIFIER_VOLATILE         = 16 , 
	//TYPE_QUALIFIER_RESTRICT         = 32 , 
	//TYPE_QUALIFIER_ATOMIC           = 64
}TypeQualiferE;
/*
static const char * TypeQualifierStrings[] = { "None", "ConstValue", "ConstReferent"};
const char * getTextForTypeQualifier(int);*/
/* ------------------------------------------------------------------------------------------------------- */
typedef struct TypeSizeAlignmentMapEntry {
	PrimitiveTypeE mType;   ///< Primitive data type. 
	size_t mSizeOf ;   ///< Size in bytes of that type. 
	size_t mAlignmentOf ;   ///< Alignment in bytes of that type.
} TypeSizeAlignmentMapEntry;
static const TypeSizeAlignmentMapEntry sTypeSizeAlignmentMap[] = { 
	{ TYPE_UNKNOWN          , 0                           , 0 } ,
	{ TYPE_VOID             , 0                           , 0 } ,
	{ TYPE_BOOL             , sizeof(bool)              , sizeof(bool) } ,
	{ TYPE_INT8             , sizeof(signed char)       , sizeof(signed char) } ,
	{ TYPE_UINT8            , sizeof(unsigned char)     , sizeof(unsigned char) } ,
	{ TYPE_INT16            , sizeof(short)             , sizeof(short) } ,
	{ TYPE_UINT16           , sizeof(unsigned short)    , sizeof(unsigned short) } ,
	{ TYPE_INT              , sizeof(int)               , sizeof(int) } ,
	{ TYPE_UINT             , sizeof(unsigned int)      , sizeof(unsigned int) } ,
	{ TYPE_INT64            , sizeof(long long)         , sizeof(long long) } ,
	{ TYPE_UINT64           , sizeof(long long)         , sizeof(long long) } ,
	{ TYPE_FLOAT            , sizeof(float)             , sizeof(float) } ,
	{ TYPE_DOUBLE           , sizeof(double)            , sizeof(double) } ,
	{ TYPE_EXTENDED         , sizeof(long double)       , sizeof(long double) }  ,
	// NOTE: "long double" in Microsoft Visual C++ is just "double". ,   
	{ TYPE_QUAD             , sizeof( long double )       , sizeof( long double )        } ,   
	{ TYPE_VECTOR           , sizeof( Math3D::Vector4 )              , 4 * sizeof( float )          } ,
	// See __declspec(align(16)) in vec4.h ,   
	{ TYPE_MATRIX           , sizeof( Math3D::Matrix44 )             , 4 * sizeof( float )          } , 
	// See __declspec(align(16)) in mat4.h ,   
	{ TYPE_STRING           , sizeof( char * )            , sizeof( char * )             } ,   
	{ TYPE_POINTER          , sizeof( void *)             , sizeof( void * )             } ,   
	{ TYPE_FUNCTION         , sizeof( FunctionP )         , sizeof( FunctionP )          } ,   
	{ TYPE_INSTANCE_METHOD  , sizeof( InstanceMethodP )   , 2 * sizeof( FunctionP )      } ,
	// Note alignment is of 2 pointers whereas size is likely that of 4 pointers ,   
	{ TYPE_CLASS_METHOD     , sizeof(ClassMethodPointer) , sizeof(ClassMethodPointer) } ,
	{ TYPE_AGGREGATE        , ~0UL                        , ~0UL                         } ,   
	{ TYPE_OPAQUE           , ~0UL                        , ~0UL                         } ,   
	{ TYPE_REFERENCE        , sizeof( void * )            , sizeof( void * )             } ,   
	{ TYPE_INVALID          , 0                           , 0                            } } ;

const size_t & SizeOfType(PrimitiveTypeE type); //{ return sTypeSizeAlignmentMap[type].mSizeOf; }
const size_t & AlignmentOfType(PrimitiveTypeE type);// { return sTypeSizeAlignmentMap[type].mAlignmentOf; }

/* ------------------------------------------------------------------------------------------------------- */
typedef void * VoidPtr;

typedef union PrimitiveValue {
	bool                mB;   ///< boolean 
	signed char         mI8     ;   ///< 8-bit signed integer 
	unsigned char       mU8     ;   ///< 8-bit unsigned integer 
	short               mI16    ;   ///< 16-bit signed integer
	unsigned short      mU16    ;   ///< 16-bit unsigned integer 
	int mI ;   ///< 32-bit signed integer 
	unsigned            mU32    ;   ///< 32-bit unsigned integer 
	long long mI64    ;   ///< 64-bit signed integer 
	unsigned long long mU64    ;   ///< 64-bit signed integer 
	float               mF      ;   ///< single-precision (32-bit) float 
	double              mF64    ;   ///< double-precision (64-bit) float 
	long double         mF128   ;   ///< quad-precision (128-bit) float 
	Math3D::Vector4      mV      ;   ///< vector
	Math3D::Matrix44Ptr   mX;   ///< matrix 
	char        *       mS ;   ///< string 
	VoidPtr mP ;   ///< pointer 
	FunctionP mFnc ;   ///< function 
	InstanceMethodP mIMF ;   ///< instance member function 
	ClassMethodPointer mCMF ;   ///< class member function 
	RecordBase* mR ;   ///< reference

	~PrimitiveValue();
	PrimitiveValue();
}PrimitiveValue;

/*
const char * getTextForPrimitiveType(int enumVal)
{
	return PrimitiveTypeStrings[enumVal];
}
const char * getTextForTypeQualifier(int enumVal)
{
	return TypeQualifierStrings[enumVal];
}
*/

#endif // !PRIMITIVE_H

