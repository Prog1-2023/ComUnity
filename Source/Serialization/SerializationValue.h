#pragma once
#include <iostream>

using namespace std;

#define SERIALIZE(Ref,Class,Status,Type,Name) SerializeValue(Ref,#Class,Status,#Type,#Name,new Type(Name))

#define READ 0
#define WRITE 1

void SerializeValue(void* _ref, const string& _className, const int _status, const string& _type, const string& _name, void* _value);