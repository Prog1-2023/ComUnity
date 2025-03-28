#include "Serialization.h"

#include <fstream>
#include <direct.h> 
using namespace filesystem;

Serialization::Serialization()
{
	storedValues = Array<ValueAttachedToObject*>();
}

Serialization::~Serialization()
{
	for (ValueAttachedToObject* _valAttached : storedValues)
	{
		for (pair<string, Array<SerializedValue*>> _secondPair : _valAttached->values)
		{
			for (SerializedValue* _value : _secondPair.second)
			{
				delete _value;
			}
		}
		delete _valAttached;
	}
}
