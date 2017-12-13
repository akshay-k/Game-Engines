// Core.cpp : Defines the entry point for the console application.
#include<iostream>
#include"RTTI.h"
using namespace std;

class Rect: public RTTI {
	RTTI_INTERFACE();
	
};
RTTI_DEFINITIONS(Rect);

class Square : public Rect {
	RTTI_INTERFACE_WITH_PARENT(Rect);
};
RTTI_DEFINITIONS(Square);

int main()
{
	Rect *r = new Rect();
	Square *s = new Square();
	cout << r->GetTypeIdInstance().Name()  << endl;
	cout << s->GetTypeIdInstance().Name() << endl;
	cout << s->IsA(r->GetTypeIdInstance());
    return 0;
}

