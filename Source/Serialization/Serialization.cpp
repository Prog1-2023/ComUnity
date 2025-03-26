#include "Serialization.h"

#include <fstream>
#include <direct.h> 
using namespace filesystem;

#include "../FString.h"


Serialization::Serialization()
{
	storedValues = map<string, vector<SerializedValue*>>();
}

Serialization::~Serialization()
{
	for (pair<string,vector<SerializedValue*>> _pair : storedValues)
	{
		for (SerializedValue* _value : _pair.second)
		{
			delete _value;
		}
	}
}

void Serialization::StartSerialization()
{
	FString _str = FString("azerty");

	_str.Contains("rty");



	return ;
	const size_t size = 1024;
	char buffer[size];
	Assert(getcwd(buffer, size),"Can't Read Directory for Serialization");

	path _path = buffer;
	_path = _path.remove_filename();
	_path = _path += "Source";

	string _pathstring = _path.string();
	vector<string> _allFiles = vector<string>();

	SearchFileInDirectory(_pathstring,_allFiles);

	ReadFile(_allFiles);
}

void Serialization::ReadFile(const vector<string> _allFiles)
{
	for (string _file : _allFiles)
	{
		ifstream _stream = ifstream(_file);

		if (!_stream)
			return;

		string _line;

		while (getline(_stream, _line))
		{
			if (Contains(_line, "SERIALIZE"))
			{
				SerializedValue* _value = RetreiveValue(_line);

				if (_value)
				{
					const path& _filePath = _file;
					string _fileName = GetFileName(_filePath);
					storedValues[_fileName].push_back(_value);
				}
			}
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

bool Serialization::ContainsInVector(const string& _toCheck, vector<string> _toCompare)
{
	for (string _string : _toCompare)
	{
		if (Contains(_toCheck, _string))
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

	return -1;
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

void Serialization::SearchFileInDirectory(const string& _path, vector<string>& _allFiles)
{
	vector<string> _typeToIgnore = { ".vert", ".frag", ".hpp" };
	vector<string> _typeToFind = { ".h", ".cpp" }; //TODO cpp remove ? 
	vector<string> _fileToIgnore = { "Serialization.cpp" , "SerializationValue.h" };

 	for (const directory_entry& _entry : directory_iterator(_path))
	{
		path _filepath = _entry.path();
		string _file = _filepath.filename().string();

		if (ContainsInVector(_file, _fileToIgnore) || ContainsInVector(_file, _typeToIgnore))
			continue;

		else if (ContainsInVector(_file, _typeToFind))
		{
			_allFiles.push_back(_filepath.string());
		}
		else
		{
			SearchFileInDirectory(_filepath.string(), _allFiles);
		}
	}
}

string Serialization::GetFileName(const path& _file)
{
	string _fileName = _file.filename().string();
	string _newName = "";

	for (char _char : _fileName)
	{
		if (_char == '.')
			return _newName;
		_newName += _char;
	}

	return _newName;
}
