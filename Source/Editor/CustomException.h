#pragma once
#include "../Utils/Macro.h"

class CustomException : public exception
{
    using Error = char const*;

public:
    CustomException(const Error _error) : exception(_error)
    {

    }

private:
    NO_DISCARD virtual Error what() const override
    {
        return (CAST(string, DEBUG_INFO)
            + CAST(string, SUPER::what())).c_str();
    }
public:
    NO_DISCARD Error What() const
    {
        return what();
    }
};