#pragma once
#include "../Utils/CoreMinimal.h"
#include "../UI/Singleton.h"
#include "SerializationValue.h"

struct SerializedValue
{
	unsigned int status;
	string type;
	string name;
	string value;

public:
	SerializedValue() = default;
	SerializedValue(const unsigned int _status, const string& _type, const string& _name, const string& _value)
	{
		status = _status;
		type = _type;
		name = _name;
		value = _value;
	}
};


class Serialization : public Singleton<Serialization>
{
	SERIALIZE(READ) int testValue1 = 0;
	SERIALIZE(WRITE) bool testValue2 = true;
	map<string, vector<SerializedValue*>> storedValues;

public:
	Serialization();
	~Serialization();

public:
	void StartSerialization();
private:
	void ReadFile(const vector<string> _allFiles);
	bool Contains(const string& _toCheck, const string& _toCompare);
	bool ContainsInVector(const string& _toCheck, vector<string> _toCompare);
	SerializedValue* RetreiveValue(string _line);
	unsigned int GetSerializeStatus(const string& _line);
	string GetNextWord(string& _line);
	string GetValue(string& _line);
	
	void SearchFileInDirectory(const string& _path, vector<string>& _allFiles);
	string GetFileName(const path& _file);
};