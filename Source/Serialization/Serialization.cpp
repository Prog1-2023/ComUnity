#include "Serialization.h"
#include <fstream>
#include <direct.h> 

Serialization::Serialization()
{
	values = vector<SerializedValue*>();
}

Serialization::~Serialization()
{
	for (SerializedValue* _value : values)
	{
		delete _value;
	}
}

void Serialization::StartSerialization()
{
	const size_t size = 1024;
	// Allocate a character array to store the directory path
	char buffer[size];

	// Call _getcwd to get the current working directory and store it in buffer
	if (getcwd(buffer, size) != NULL) {
		// print the current working directory
		cout << "Current working directory: " << buffer << endl;
	}
	else {
		// If _getcwd returns NULL, print an error message
		cerr << "Error getting current working directory" << endl;
	}

	//const string& _path = "C:/Users/PUEC1602/Documents/GitHub/ComUnity/Source/Serialization/Serialization.h";
	//ReadFile(_path);
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
			SerializedValue* _value = RetreiveValue(_line);
			values.push_back(_value);
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

SerializedValue* Serialization::RetreiveValue(string _line)
{
	const unsigned int _status = GetSerializeStatus(_line);
	const string& _type = GetNextWord(_line);
	const string& _name = GetNextWord(_line);
	const string& _value = GetValue(_line);
	return new SerializedValue(_status, _type, _name, _value);
}

unsigned int Serialization::GetSerializeStatus(const string& _line)
{
	if (Contains(_line, "READ"))
		return 0;
	else if (Contains(_line, "WRITE"))
		return 1;
}

string Serialization::GetNextWord(string& _line)
{
	_line = _line.substr(_line.find_first_of(' ') + 1);

	string _type = "";

	for(char _char : _line)
	{
		if (_char == ' ')
			break;

		_type += _char;
	}
	return _type;
}

string Serialization::GetValue(string& _line)
{
	_line = _line.substr(_line.find_first_of('=') + 1);

	int _index = 0;
	for (string::iterator _it = _line.begin(); _it != _line.end(); _it++, _index++)
	{
		if (_line.at(_index) == ' ')
		{
			_line.erase(_it);
		}
	}
	_line.pop_back();
	return _line;
}
