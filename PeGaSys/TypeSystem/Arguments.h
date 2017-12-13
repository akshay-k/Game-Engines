#pragma once
#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include "TypedValue.h"

class Arguments {
	size_t args_capacity;
	size_t args_actual;
	TypedValue * args;
public:
	~Arguments() {
		delete[] args;
	}
	Arguments() {
		args = nullptr;
		args_actual = 0;
		args_capacity = 0;
	}

	
	Arguments(TypedValue a, TypedValue b) {
		args = new TypedValue[2];
		args[0] = a;
		args[1] = b;
		args_actual = 2;
		args_capacity = 2;
	}
	
	Arguments(TypedValue *a, size_t args_length) {
		args = a;
		args_actual = args_length;
		args_capacity = args_length;
	}
};

#endif // !ARGUMENTS_H
