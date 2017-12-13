#pragma once
#include"AbstractFactory.h"
template <class AbstractProductT, class TypeIdentifierT = const char * > class FactoryRegistry
{
public:
	typedef Factory< AbstractProductT, TypeIdentifierT > FactoryT;
	typedef map< TypeIdentifierT, FactoryT * > MapT;
	FactoryRegistry(void) {}
	~FactoryRegistry() {}
	void Add(const TypeIdentifierT & typeIdentifier, FactoryT * pFactory)
	{
		mFactoryMap[typeIdentifier] = pFactory;
	}
	void Remove(const TypeIdentifierT & typeIdentifier) {
		mFactoryMap.erase(typeIdentifier);
	}
	FactoryT * Find(const TypeIdentifierT & concreteClassIdentifier)
	{
		MapT::iterator pFactory = mFactoryMap.find(concreteClassIdentifier);
		return pFactory->second;
	}
	AbstractProductT * Create(const TypeIdentifierT & concreteClassIdentifier, size_t numToCreate = 1)
	{
		FactoryT * factory = Find(concreteClassIdentifier);
		if (factory != NULL)
		{
			AbstractProductT * product = factory->CreateObjects(numToCreate);
			return product;
		}
		return NULL;
	}

	template <typename T> 
	T * Create(const char* id, size_t numToCreate = 1)
	{
		IGeneric * pObj = Create(id, numToCreate);
		T * pReturnValue = DynamicCastPtr< T >(pObj);
		return pReturnValue;
	}
	//typename map< TypeIdentifierT, FactoryT >::Iterator BeginM(void) { return mFactoryMap.Begin(); }
	//typename map< TypeIdentifierT, FactoryT >::Iterator EndM(void) { return mFactoryMap.End(); }
private:
	MapT mFactoryMap; ///< map of concrete factories associated with abstract factory
	FactoryRegistry(const FactoryRegistry &); ///< Disallow copying
	//FactoryRegistry & operator=(const FactoryRegistry &); ///< Disallow copying
};