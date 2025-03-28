#pragma once

#define SIZE_CAST(_variableName, _listSize) const unsigned int& ##_variableName = static_cast<const unsigned int>(_listSize)
#define FOREACH(_variableName, _listSize) SIZE_CAST(_variableName, _listSize); for (unsigned int _index = 0; _index < _variableName; _index++)
