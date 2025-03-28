#pragma once
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>
#include <cctype>
#include "../Utils/Macro.h"

using namespace std;

template <typename Type>
struct Vector2
{
	Type x;
	Type y;

#pragma region DefaultValues
	//Vector (0,0)
	inline static Vector2<Type> Zero() { return Vector2<Type>(); }
	//Vector (1,1)
	inline static Vector2<Type> One() { return Vector2<Type>(Type(1)); }
	//Vector (1,0)
	inline static Vector2<Type> Up() { return Vector2<Type>(Type(1), Type()); }
	//Vector (0,1)
	inline static Vector2<Type> Right() { return Vector2<Type>(Type(),Type(1)); }
#pragma endregion


#pragma region Constructors
	Vector2()
	{
		x = Type();
		y = Type();
	}
	Vector2(const Type& _value)
	{
		x = _value;
		y = _value;
	}
	Vector2(const Type& _x, const Type& _y)
	{
		x = _x;
		y = _y;
	}
	Vector2(const Vector2& _other)
	{
		x = _other.x;
		y = _other.y;
	}
	Vector2(const aiVector3D& _other)
	{
		x = _other.x;
		y = _other.y;
	}
	Vector2(const initializer_list<Type>& _list)
	{
		const initializer_list<Type>::value_type* _begin = _list.begin();
		x = *_begin;
		// write the first value if there's only one
		// look for the second value if there's more than 1 value
		// if there's more than 2 values, they will be ignored
		y = _list.size() == 1 ? *_begin : *(_begin + 1);
	}
	Vector2(Vector2&& _other)
	{
		// take all values in other and put in this instance then put other in default value
		*this = move(_other);
	}
#pragma endregion	


#pragma region Methods

	float Length()
	{
		return sqrtf((x * x) + (y * y));
	}
	float Dot(const Vector2<Type>& _other)
	{
		return (x * _other.x) + (y * _other.y);
	}
	float Distance(const Vector2<Type>& _other)
	{
		return (x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y);
	}
	float AngleBetween(Vector2<Type>& _other)
	{
		Type _angle = Dot(_other) / (Length() * _other.Length());
		_angle = acos(_angle) * 180.0f / M_PI;
		return _angle;
	}
	Vector2<Type> Normalize()
	{
		Type _length = Length();
		Type _x = round(x / _length);
		Type _y = round(y / _length);
		return Vector2<Type>(_x,_y);
	}

#pragma endregion


#pragma region Operators
	void operator += (const Vector2& _other)
	{
		x += _other.x;
		y += _other.y;
	}
	void operator -= (const Vector2& _other)
	{
		x -= _other.x;
		y -= _other.y;
	}
	void operator *= (const Vector2& _other)
	{
		x *= _other.x;
		y *= _other.y;
	}
	void operator /= (const Vector2& _other)
	{
		x /= _other.x;
		y /= _other.y;
	}

	void operator += (const Type& _value)
	{
		x += _value;
		y += _value;
	}
	void operator -= (const Type& _value)
	{
		x -= _value;
		y -= _value;
	}
	void operator *= (const Type& _value)
	{
		x *= _value;
		y *= _value;
	}
	void operator /= (const Type& _value)
	{
		x /= _value;
		y /= _value;
	}

	Vector2<Type> operator + (const Vector2& _other)
	{
		return Vector2<Type>(x + _other.x, y + _other.y);
	}
	Vector2<Type> operator - (const Vector2& _other)
	{
		return Vector2<Type>(x - _other.x, y - _other.y);
	}
	Vector2<Type> operator * (const Vector2& _other)
	{
		return Vector2<Type>(x * _other.x, y * _other.y);
	}
	Vector2<Type> operator / (const Vector2& _other)
	{
		return Vector2<Type>(x / _other.x, y / _other.y);
	}

	bool operator == (const Vector2& _other) const noexcept
	{
		return x == _other.x && y == _other.y;
	}
	bool operator != (const Vector2& _other) const noexcept
	{
		return x != _other.x && y != _other.y;
	}
	bool operator < (const Vector2& _other) const noexcept
	{
		return x < _other.x && y < _other.y;
	}
	bool operator <= (const Vector2& _other) const noexcept
	{
		return x <= _other.x && y <= _other.y;
	}
	bool operator > (const Vector2& _other) const noexcept
	{
		return x > _other.x && y > _other.y;
	}
	bool operator >= (const Vector2& _other) const noexcept
	{
		return x >= _other.x && y >= _other.y;
	}

	void operator ++ ()
	{
		++x;
		++y;
	}
	void operator -- ()
	{
		--x;
		--y;
	}

	Vector2<Type> operator -()
	{
		return *this * -1.0f;
	}

	Vector2<Type>& operator = (Vector2<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);

		return *this;
	}

	Vector2<Type> operator = (const Vector2<Type>& _other)
	{
		return *this = Vector2<Type>(_other);
	}
	
	Vector2<Type> operator = (const aiVector3D& _other)
	{
		return *this = Vector2<Type>(_other);
	}


	friend ostream& operator << (ostream& _stream, const Vector2<Type>& _otherVec)
	{
		return _stream << "X: " << _otherVec.x << " Y: " << _otherVec.y;
	}

#pragma endregion

};

#pragma region Using
using Vector2c = Vector2<char>;
using Vector2s = Vector2<short>;
using Vector2us = Vector2<unsigned short>;
using Vector2ui = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
#pragma endregion