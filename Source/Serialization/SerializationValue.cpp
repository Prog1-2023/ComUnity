#include "SerializationValue.h"
#include "Serialization.h"

void SerializeValue(void* _ref, const string& _className, const string& _type, const string& _name, void* _value)
{
	Array<ValueAttachedToObject*>& _map = Serialization::GetInstance().GetStoredValues();

	SerializedValue* _newSerializedValue = new SerializedValue(_name, _type, _value);

	// Contains the object
	for (ValueAttachedToObject* _ValAttached : _map)
	{
		if (_ValAttached->object == _ref)
		{
			_ValAttached->values[_className].Add(_newSerializedValue);
			return;
		}
	}
	// Don't contains the object so create a new one
	ValueAttachedToObject* _newValue = new ValueAttachedToObject();
	_newValue->object = _ref;
	_newValue->values[_className].Add(_newSerializedValue);

	_map.Add(_newValue);
}
