
#pragma once
#include<map>
using namespace std;

#define ConcreteFactory( AbstractProductT, ConcreteProductT , IdType) \
class ConcreteProductT ## Factory : public Factory<AbstractProductT,IdType> \
{ \
public: \
ConcreteProductT ## Factory() {} \
~ConcreteProductT ## Factory() {} \
private: \
virtual AbstractProductT * CreateObjects( size_t numToCreate ) \
{ \
AbstractProductT * product = new ConcreteProductT [ numToCreate ] ; \
return product ; \
} \
} ;

template <class AbstractProductT, class TypeIdentifierT = const char * > 
class Factory
{
public:
	typedef map< TypeIdentifierT, Factory * > MapT;
	/// Initialize an abstract factory.
	Factory() {}
	/// Destruct an abstract factory.
	virtual ~Factory() {}
	/** Instantiate an object of the class associated with this (concrete) factory.
	\return address of concrete product
	*/
	virtual AbstractProductT * CreateObjects(size_t numToCreate) = 0;
	/* This is pseudo-code that each Factory concrete class must implement.
	{
	AbstractProductT * product = NEW AbstractProductT [ numToCreate ] ;
	ASSERT( product != NULL ) ;
	return product ;
	}
	*/
private:
	Factory(const Factory &); ///< disallow copying
	Factory & operator=(const Factory &); ///< disallow copying
};
