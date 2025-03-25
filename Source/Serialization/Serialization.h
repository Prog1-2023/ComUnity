#pragma once
#include "../Utils/CoreMinimal.h"
#include "../UI/Singleton.h"

#define SERIALIZE(args1)
#define READ 0
#define WRITE 1

struct SerializedValue
{
	unsigned int status;
	string type;
	string value;

public:
	SerializedValue() = default;
	SerializedValue(const unsigned int _status, const string& _type, const string& _value)
	{
		status = _status;
		type = _type;
		value = _value;
	}
};


class Serialization : public Singleton<Serialization>
{
	SERIALIZE(READ) int testValue1 = 0;
	SERIALIZE(WRITE) bool testValue2 = true;
	vector<SerializedValue> values;


public:
	Serialization();
	~Serialization();

public:
	void StartSerialization();
private:
	void ReadFile(const string& _path);
	bool Contains(const string& _toCheck, const string& _toCompare);
	SerializedValue RetreiveValue(const string& _line);
	unsigned int GetSerializeStatus(const string& _line);
	string GetType(const string& _line);
};