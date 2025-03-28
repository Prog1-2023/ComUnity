#pragma once
#include "CoreMinimal.h"

class String
{
	char* data;
	unsigned int length;

public:
	FORCEINLINE char* GetData() const { return data; }
	FORCEINLINE unsigned int GetSize() const { return length; }
public:
	// Default constructor
	String();

	// Constructor with text
	String(const char* _text);

	// Copy constructor
	String(const String& _other);

	// Destructor
	~String();

private:
	// Calculate the length of a string
	static unsigned int ComputeLength(const char* _str);

public:
	// Check if the string contains a substring
	bool Contains(const String& _sub) const;

	// Get a substring from a string
	String SubString(unsigned int start, unsigned int length) const;

	// Find the first occurrence of a string
	int FindFirstOf(const String& chars) const;

	// Find the last occurrence of a string
	int FindLastOf(const String& _string) const;

	// Copy the content of an existing string to another existing string
	String& operator=(const String& _other);

	// Indexing operator
	char& operator[](unsigned int _index) const;

	// Concatenation
	String operator+(const String& _other) const;

	// Concatenation assignment
	String& operator+=(const String& _other);

	// Equality operators
	bool operator==(const String& _other) const;

	// Output operator
	friend ostream& operator << (ostream& _stream, const String& _string);

	// Convert an integer to a string
	static String ItoS(int _int);

	// Convert a float to a string
	static String FtoS(float _value);

	// Convert a string to a int
	static int StoI(String _string);

	// Convert a string to float
	static float StoF(String _string);

	static vector<string> Split(const string& _toSplit, const string& _delimiter);

};
