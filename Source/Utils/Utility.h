#pragma once

#include "SubclassOf.h"
#include "Macro.h"

template <typename Type>
Type* Spawn(const SubclassOf<Type>& _ref)
{
    Type* _type = new Type(_ref.GetObject());
    return _type;
}