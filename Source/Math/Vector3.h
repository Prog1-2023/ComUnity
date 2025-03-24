#pragma once
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>
#include <cctype>

#include "../Utils/Macro.h"

using namespace std;

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

#pragma region DefaultValues
	//Vector (0,0,0)
	FORCEINLINE static Vector3<T> Zero() { return Vector3<T>(); }
	//Vector (1,1,1)
	FORCEINLINE static Vector3<T> One() { return Vector3<T>(T(1)); }
	//Vector (1,0,0)
	FORCEINLINE static Vector3<T> Right() { return Vector3<T>(T(1), T(), T()); }
	//Vector (0,1,0)
	FORCEINLINE static Vector3<T> Up() { return Vector3<T>(T(), T(1), T()); }
	//Vector (0,0,1)
	FORCEINLINE static Vector3<T> Forward() { return Vector3<T>(T(), T(), T(1)); }
#pragma endregion


#pragma region Contructors
	Vector3()
	{
		x = T();
		y = T();
		z = T();
	}
	Vector3(const T& _value)
	{
		x = _value;
		y = _value;
		z = _value;
	}
	Vector3(const T& _x, const T& _y)
	{
		x = _x;
		y = _y;
		z = T();
	}
	Vector3(const T& _x, const T& _y, const T& _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3(const Vector3& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}
	Vector3(const aiVector3D& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}
	Vector3(const initializer_list<T>& _list)
	{
		const initializer_list<T>::value_type* _begin = _list.begin();
		x = *_begin;
		// write the first value if there's only one
		// look for the second value if there's more than 1 value
		// if there's more than 2 values, they will be ignored
		y = _list.size() == 1 ? *_begin : *(_begin + 1);
		z = _list.size() == 1 ? T() : *(_begin + 2);
	}
	Vector3(Vector3&& _other)
	{
		// take all values in other and put in this instance then put other in default value
		*this = move(_other);
	}
#pragma endregion


#pragma region Methods

	float Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	float Dot(const Vector3<T>& _other) const
	{
		return (x * _other.x) + (y * _other.y) + (z * _other.z);
	}
	float Distance(const Vector3<T>& _other) const
	{
		return (x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y) + (z - _other.z) * (z - _other.z);
	}
	float AngleBetween(Vector3<T>& _other) const
	{
		T _angle = Dot(_other) / (Length() * _other.Length());
		_angle = acos(_angle) * 180.0f / M_PI;
		return _angle;
	}
	Vector3<T> Normalize() const
	{
		T _length = Length();
		T _x = round(x / _length);
		T _y = round(y / _length);
		T _z = round(z / _length);
		return Vector3<T>(_x, _y,_z);
	}
	Vector3<T> Cross(const Vector3<T>& _other) const
	{
		return Vector3<T>(y * _other.z - z * _other.y, z * _other.x - x * _other.z, x * _other.y - y * _other.x);
	}

	static vec3 CreateVecFromVector(const Vector3<T>& _vector)
	{
		vec3 _newVec = vec3(_vector.x, _vector.y, _vector.z);
		return _newVec;
	}


#pragma endregion


#pragma region Operators
	void operator += (const Vector3& _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
	}
	void operator -= (const Vector3& _other)
	{
		x -= _other.x;
		y -= _other.y;
		z -= _other.z;
	}
	void operator *= (const Vector3& _other)
	{
		x *= _other.x;
		y *= _other.y;
		z *= _other.z;
	}
	void operator /= (const Vector3& _other)
	{
		x /= _other.x;
		y /= _other.y;
		z /= _other.z;
	}

	void operator += (const T& _value)
	{
		x += _value;
		y += _value;
		z += _value;
	}
	void operator -= (const T& _value)
	{
		x -= _value;
		y -= _value;
		z -= _value;
	}
	void operator *= (const T& _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
	}
	void operator /= (const T& _value)
	{
		x /= _value;
		y /= _value;
		y /= _value;
	}

	Vector3<T> operator + (const Vector3& _other)
	{
		return Vector3<T>(x + _other.x, y + _other.y, z + _other.z);
	}
	Vector3<T> operator - (const Vector3& _other)
	{
		return Vector3<T>(x - _other.x, y - _other.y, z - _other.z);
	}
	Vector3<T> operator * (const Vector3& _other)
	{
		return Vector3<T>(x * _other.x, y * _other.y, z * _other.z);
	}
	Vector3<T> operator / (const Vector3& _other)
	{
		return Vector3<T>(x / _other.x, y / _other.y, z / _other.z);
	}

	bool operator == (const Vector3& _other) const noexcept
	{
		return x == _other.x && y == _other.y && z == _other.z;
	}
	bool operator != (const Vector3& _other) const noexcept
	{
		return x != _other.x && y != _other.y && z != _other.z;
	}
	bool operator < (const Vector3& _other) const noexcept
	{
		return x < _other.x && y < _other.y && z < _other.z;
	}
	bool operator <= (const Vector3& _other) const noexcept
	{
		return x <= _other.x && y <= _other.y && z <= _other.z;
	}
	bool operator > (const Vector3& _other) const noexcept
	{
		return x > _other.x && y > _other.y && z > _other.z;
	}
	bool operator >= (const Vector3& _other) const noexcept
	{
		return x >= _other.x && y >= _other.y && z >= _other.z;
	}

	void operator ++ ()
	{
		++x;
		++y;
		++z;
	}
	void operator -- ()
	{
		--x;
		--y;
		--z;
	}

	Vector3<T> operator -()
	{
		return *this * -1.0f;
	}
	Vector3<T>& operator = (Vector3<T>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);
		z = move(_other.z);

		return *this;
	}
	Vector3<T>& operator = (const Vector3<T>& _other)
	{
		return *this = Vector3<T>(_other);
	}
	Vector3<T>& operator = (const aiVector3D& _other)
	{
		return *this = Vector3<T>(_other);
	}

	friend ostream& operator << (ostream& _stream, const Vector3<T>& _otherVec)
	{
		return _stream << "X: " << _otherVec.x << " Y: " << _otherVec.y << " Z: " << _otherVec.z;
	}
#pragma endregion

};

#pragma region Using
using Vector3c = Vector3<char>;
using Vector3s = Vector3<short>;
using Vector3us = Vector3<unsigned short>;
using Vector3ui = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
#pragma endregion