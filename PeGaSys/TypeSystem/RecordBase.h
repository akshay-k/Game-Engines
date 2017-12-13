#pragma once
#ifndef RECORDBASE_H
#define RECORDBASE_H
#include"IRecord.h"
#include"Arguments.h"
#include"RTTI.h"

class RecordBase : public IRecord { 
	RTTI_INTERFACE(); 
public: 
	IGeneric * QueryInterface(const TypeInfo & typeInfo); 
	void Invoke(const char * methodName, Arguments & args); 
	void InvokeDescendants(const char * methodName, Arguments & args); 
};

typedef RecordBase*  RecordBasePtr;

#endif // !RECORDBASE_H
