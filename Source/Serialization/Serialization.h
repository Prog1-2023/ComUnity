#pragma once
#include "../Utils/CoreMinimal.h"
#include "../UI/Singleton.h"

struct SerializedValue
{
	unsigned int status;
	string name;
	string type;
	void* variable;

public:
	SerializedValue() = default;
	SerializedValue(const unsigned int _status, const string& _name, const string& _type, void* _variable)
	{
		status = _status;
		name = _name;
		type = _type;
		variable = _variable;
	}
};

struct ValueAttachedToObject
{
	void* object;
	map<string, vector<SerializedValue*>> values;

	ValueAttachedToObject()
	{
		object = nullptr;
		values = map<string, vector<SerializedValue*>>();
	}
};


class Serialization : public Singleton<Serialization>
{
	vector<ValueAttachedToObject*> storedValues;
public:
	Serialization();
	~Serialization();

public:
	FORCEINLINE vector<ValueAttachedToObject*>& GetStoredValues() { return storedValues; }
};