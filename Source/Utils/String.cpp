#include "String.h"

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

unsigned int String::Size() const
{
    return length;
}

bool String::Contains(const String& _sub) const
{
    if (_sub.Size() > Size())
    {
        return false;
    }
    // Iterate through each position of the main string to search for the substring
    for (unsigned int _i = 0; _i <= Size() - _sub.Size(); ++_i)
    {
        bool _match = true;
        for (unsigned int j = 0; j < _sub.Size(); ++j)
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