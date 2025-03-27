#pragma once
#include <iostream>
using namespace std;

class String
{
    char* data;
    unsigned int length;

    // Calculate the length of a string
    static unsigned int ComputeLength(const char* _str);

public:
    // Default constructor
    String();
    // Constructor with text
    String(const char* _text);
    // Copy constructor
    String(const String& _other);
    // Destructor
    ~String();

    // Get the length of the string
    unsigned int Size() const;
    // Check if the string contains a substring
    bool Contains(const String& _sub) const;

    // Copy the content of an existing string to another existing string
    String& operator=(const String& _other);

    // Indexing operator
    char& operator[](unsigned int _index) const;

    // Concatenation
    String operator+(const String& _other) const;

    // += operator
    String& operator+=(const String& _other);

    // Equality operators
    bool operator==(const String& _other) const;

    friend ostream& operator << (ostream& _stream, const String& _string);
};