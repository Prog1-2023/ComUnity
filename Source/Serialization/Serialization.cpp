#include "Serialization.h"
#include <fstream>

Serialization::Serialization()
{
	values = vector<SerializedValue>();
}

Serialization::~Serialization()
{

}

void Serialization::StartSerialization()
{
	const string& _path = "C:/Users/PUEC1602/Documents/GitHub/ComUnity/Source/Serialization/Serialization.h";
	ReadFile(_path);
}

void Serialization::ReadFile(const string& _path)
{
	ifstream _stream = ifstream(_path);

	if (!_stream)
		return;

	string _line;

	while (getline(_stream, _line))
	{
		if (Contains(_line,"SERIALIZE"))
		{
			SerializedValue _value = RetreiveValue(_line);
		}
	}
}

bool Serialization::Contains(const string& _toCheck, const string& _toCompare)
{
	int _compareSize = int(_toCompare.size());
	int _identicalLetterFound = 0;
	int _compareIndex = 0;

	int _stringSize = int(_toCheck.size());
	for (int _i = 0; _i < _stringSize; _i++)
	{
		if (_toCheck[_i] == _toCompare[_compareIndex])
		{
			_identicalLetterFound++;
			_compareIndex++;
		}
		else
		{
			_compareIndex = 0;
			if (_identicalLetterFound > 0)
				_identicalLetterFound = 0;
		}
		if (_identicalLetterFound == _compareSize)
			return true;
	}
	return false;
}

SerializedValue Serialization::RetreiveValue(const string& _line)
{
	const unsigned int _status = GetSerializeStatus(_line);
	const string& _type = GetType(_line);
	return SerializedValue();
}

unsigned int Serialization::GetSerializeStatus(const string& _line)
{
	if (Contains(_line, "READ"))
		return 0;
	else if (Contains(_line, "WRITE"))
		return 1;
}

string Serialization::GetType(const string& _line)
{
	string _newLine = _line.substr(_line.find_first_of(' '));
	_newLine = _newLine.substr(_line.find_first_of(' '));
	cout << _newLine;
	return "";
}
