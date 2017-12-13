#pragma once
#include"IGeneric.h"
class AbstractProductT : public IGeneric {
public:
	virtual IGeneric * QueryInterface(const TypeInfo &uId)
	{
		if (IsA(uId))
			return static_cast<AbstractProductT *> (this);
		else
			return NULL;
	}
};
