#pragma once
#include <iostream>
#include <any>

using namespace std;

#define SERIALIZE(RefOfOwner,Class,Status,Type,Name) SerializeValue(RefOfOwner,#Class,Status,#Type,#Name,&Name)

#define READ 0
#define WRITE 1

void SerializeValue(void* _ref, const string& _className, const int _status, const string& _type, const string& _name, void* _value);