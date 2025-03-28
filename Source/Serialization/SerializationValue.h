#pragma once
#include "../Utils/Macro.h"

#define SERIALIZE(RefOfOwner,Class,Status,Type,Name) SerializeValue(RefOfOwner,#Class,#Type,#Name,&Name)
#define SERIALIZE_PTR(RefOfOwner,Class,Status,Type,Name) SerializeValue(RefOfOwner,#Class,#Type,#Name,Name)

void SerializeValue(void* _ref, const string& _className,const string& _type, const string& _name, void* _value);
