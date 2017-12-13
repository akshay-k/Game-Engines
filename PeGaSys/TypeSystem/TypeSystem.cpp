#include<iostream>
#include"Schema.h"
#include"DynamicRecord.h"
using namespace std;

void display(Arguments *args) {
	printf("Hi!");
}

Arguments * noArgs = new Arguments();

int main()
{
	Schema* s = new Schema();
	s->AddMember(PrimitiveTypeE::TYPE_BOOL, TypeQualiferE::TYPE_QUALIFIER_NONE);
	//s->AddNamedMember("Hello0", PrimitiveTypeE::TYPE_INSTANCE_METHOD, 0);
	
	DynamicRecord *d = new DynamicRecord(*s);
	InstanceMethodP *imp = new InstanceMethodP();
	imp->object = d;
	imp->function = *display;
	d->AddMethod("Hello",*imp);
	d->Invoke("Hello", *noArgs);
	d->GetSchema()->Print();
	return 0;
}

