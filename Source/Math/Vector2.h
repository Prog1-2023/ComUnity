#pragma once
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>
#include <cctype>
#include "../Utils/Macro.h"

using namespace std;

template <typename T>
struct Vector2
{
	T x;
	T y;

#pragma region DefaultValues
	//Vector (0,0)
	inline static Vector2<T> Zero() { return Vector2<T>(); }
	//Vector (1,1)
	inline static Vector2<T> One() { return Vector2<T>(T(1)); }
	//Vector (1,0)
	inline static Vector2<T> Up() { return Vector2<T>(T(1), T()); }
	//Vector (0,1)
	inline static Vector2<T> Right() { return Vector2<T>(T(),T(1)); }
#pragma endregion


#pragma region Constructors
	Vector2()
	{
		x = T();
		y = T();
	}
	Vector2(const T& _value)
	{
		x = _value;
		y = _value;
	}
	Vector2(const T& _x, const T& _y)
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
	Vector2(const initializer_list<T>& _list)
	{
		const initializer_list<T>::value_type* _begin = _list.begin();
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
	float Dot(const Vector2<T>& _other)
	{
		return (x * _other.x) + (y * _other.y);
	}
	float Distance(const Vector2<T>& _other)
	{
		return (x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y);
	}
	float AngleBetween(Vector2<T>& _other)
	{
		T _angle = Dot(_other) / (Length() * _other.Length());
		_angle = acos(_angle) * 180.0f / M_PI;
		return _angle;
	}
	Vector2<T> Normalize()
	{
		T _length = Length();
		T _x = round(x / _length);
		T _y = round(y / _length);
		return Vector2<T>(_x,_y);
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

	void operator += (const T& _value)
	{
		x += _value;
		y += _value;
	}
	void operator -= (const T& _value)
	{
		x -= _value;
		y -= _value;
	}
	void operator *= (const T& _value)
	{
		x *= _value;
		y *= _value;
	}
	void operator /= (const T& _value)
	{
		x /= _value;
		y /= _value;
	}

	Vector2<T> operator + (const Vector2& _other)
	{
		return Vector2<T>(x + _other.x, y + _other.y);
	}
	Vector2<T> operator - (const Vector2& _other)
	{
		return Vector2<T>(x - _other.x, y - _other.y);
	}
	Vector2<T> operator * (const Vector2& _other)
	{
		return Vector2<T>(x * _other.x, y * _other.y);
	}
	Vector2<T> operator / (const Vector2& _other)
	{
		return Vector2<T>(x / _other.x, y / _other.y);
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

	Vector2<T> operator -()
	{
		return *this * -1.0f;
	}

	Vector2<T>& operator = (Vector2<T>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);

		return *this;
	}

	Vector2<T> operator = (const Vector2<T>& _other)
	{
		return *this = Vector2<T>(_other);
	}
	
	Vector2<T> operator = (const aiVector3D& _other)
	{
		return *this = Vector2<T>(_other);
	}


	friend ostream& operator << (ostream& _stream, const Vector2<T>& _otherVec)
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