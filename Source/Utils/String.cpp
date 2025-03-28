#include "String.h"
#include <string>

unsigned int String::ComputeLength(const char* _str)
{
	unsigned int _len = 0;
	while (_str && _str[_len] != '\0')
	{
		_len++;
	}
	return _len;
}

String::String()
{
	length = 0;
	data = new char[1];
	data[0] = '\0';
}

String::String(const char* _text)
{
	if (!_text)
	{
		length = 0;
		data = new char[1];
		data[0] = '\0';
		return;
	}

	length = ComputeLength(_text);
	data = new char[length + 1];
	for (unsigned int _i = 0; _i < length; ++_i)
	{
		data[_i] = _text[_i];
	}
	data[length] = '\0';
}

String::String(const String& _other)
{
	length = _other.length;
	data = new char[length + 1];
	for (unsigned int _i = 0; _i < length; ++_i)
	{
		data[_i] = _other.data[_i];
	}
	data[length] = '\0';
}

String::~String()
{
	delete[] data;
}

char& String::operator[](unsigned int _index) const
{
	if (_index >= length)
	{
		throw out_of_range("Index out of bounds");
	}
	return data[_index];
}

bool String::Contains(const String& _sub) const
{
	if (_sub.GetSize() > GetSize())
	{
		return false;
	}
	// Iterate through each position of the main string to search for the substring
	for (unsigned int _i = 0; _i <= GetSize() - _sub.GetSize(); ++_i)
	{
		bool _match = true;
		for (unsigned int j = 0; j < _sub.GetSize(); ++j)
		{
			if (data[_i + j] != _sub[j])
			{
				_match = false;
				break;
			}
		}
		// If a match is found
		if (_match)
			return true;
	}
	return false; // No match found
}

String String::SubString(unsigned int _start, unsigned int _index) const
{
	if (_start >= length) return String("");

	if (_start + _index > length)
	{
		_index = length - _start;
	}

	char* _subData = new char[_index + 1];

	for (unsigned int _i = 0; _i < _index; ++_i)
	{
		_subData[_i] = data[_start + _i];
	}

	_subData[_index] = '\0';

	String _result = _subData;
	delete[] _subData;

	return _result;
}

int String::FindFirstOf(const String& _string) const
{
	for (unsigned int _i = 0; _i < length; ++_i)
	{
		for (unsigned int _j = 0; _j < _string.length; ++_j)
		{
			if (data[_i] == _string.data[_j])
			{
				return static_cast<int>(_i);
			}
		}
	}
	return -1;
}

int String::FindLastOf(const String& _string) const
{
	for (int _i = static_cast<int>(length) - 1; _i >= 0; --_i)
	{
		for (unsigned int j = 0; j < _string.length; ++j)
		{
			if (data[_i] == _string.data[j])
			{
				return _i;
			}
		}
	}
	return -1;
}

String String::operator+(const String& _other) const
{
	String _result;
	_result.length = length + _other.length;
	_result.data = new char[_result.length + 1];

	for (unsigned int _i = 0; _i < length; ++_i)
	{
		_result.data[_i] = data[_i];
	}

	for (unsigned int _i = 0; _i < _other.length; ++_i)
	{
		_result.data[length + _i] = _other.data[_i];
	}

	_result.data[_result.length] = '\0';
	return _result;
}

String& String::operator+=(const String& _other)
{
	char* newData = new char[length + _other.length + 1];

	for (unsigned int i = 0; i < length; ++i)
	{
		newData[i] = data[i];
	}

	for (unsigned int i = 0; i < _other.length; ++i)
	{
		newData[length + i] = _other.data[i];
	}

	newData[length + _other.length] = '\0';

	delete[] data;
	data = newData;
	length += _other.length;

	return *this;
}

bool String::operator==(const String& _other) const
{
	if (length != _other.length) return false;
	for (unsigned int i = 0; i < length; ++i)
	{
		if (data[i] != _other.data[i]) return false;
	}
	return true;
}

String& String::operator=(const String& _other)
{
	if (this != &_other) // Check if it's not the same object
	{
		delete[] data;
		length = _other.length;
		data = new char[length + 1];
		for (unsigned int i = 0; i < length; ++i)
		{
			data[i] = _other.data[i];
		}
		data[length] = '\0';
	}
	return *this;
}

ostream& operator<<(ostream& _stream, const String& _string)
{
	if (_string.data)
	{
		_stream << _string.data;
	}
	return _stream;
}

String String::ItoS(int _value)
{
	string _str = std::to_string(_value);
	return String(_str.c_str());
}

String String::FtoS(float _value)
{
	string _str = std::to_string(_value);
	return String(_str.c_str());
}

int String::StoI(String _string)
{
	return stoi(_string.GetData());
}

float String::StoF(String _string)
{
	return stof(_string.GetData());
}

vector<string> String::Split(const string& _toSplit, const string& _delimiter)
{
	vector<string> _result = vector<string>();
	size_t _start = 0;
	size_t _end = 0;
	while ((_end = _toSplit.find(_delimiter, _start)) != string::npos)
	{
		_result.push_back(_toSplit.substr(_start, _end - _start));
		_start = _end + _delimiter.length();
	}
	_result.push_back(_toSplit.substr(_start));
	return _result;
}
