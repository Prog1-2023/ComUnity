#pragma once
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>
#include <cctype>

using namespace std;

#include "../Serialization/SerializationValue.h"

template <typename Type>
struct Vector3
{
	Type x;
	Type y;
	Type z;

#pragma region DefaultValues
	//Vector (0,0,0)
	FORCEINLINE static Vector3<Type> Zero() { return Vector3<Type>(); }
	//Vector (1,1,1)
	FORCEINLINE static Vector3<Type> One() { return Vector3<Type>(Type(1)); }
	//Vector (1,0,0)
	FORCEINLINE static Vector3<Type> Right() { return Vector3<Type>(Type(1), Type(), Type()); }
	//Vector (0,1,0)
	FORCEINLINE static Vector3<Type> Up() { return Vector3<Type>(Type(), Type(1), Type()); }
	//Vector (0,0,1)
	FORCEINLINE static Vector3<Type> Forward() { return Vector3<Type>(Type(), Type(), Type(1)); }
#pragma endregion


#pragma region Contructors
	Vector3()
	{
		x = Type();
		y = Type();
		z = Type();
	}
	Vector3(const Type& _value)
	{
		x = _value;
		y = _value;
		z = _value;
	}
	Vector3(const Type& _x, const Type& _y)
	{
		x = _x;
		y = _y;
		z = Type();
	}
	Vector3(const Type& _x, const Type& _y, const Type& _z)
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
	Vector3(const initializer_list<Type>& _list)
	{
		const initializer_list<Type>::value_type* _begin = _list.begin();
		x = *_begin;
		// write the first value if there's only one
		// look for the second value if there's more than 1 value
		// if there's more than 2 values, they will be ignored
		y = _list.size() == 1 ? *_begin : *(_begin + 1);
		z = _list.size() == 1 ? Type() : *(_begin + 2);
	}
	Vector3(Vector3&& _other)
	{
		// take all values in other and put in this instance then put other in default value
		*this = move(_other);
	}
#pragma endregion


#pragma region Methods

	void SetSerializeValue()
	{
		SERIALIZE(this,Vector3f,WRITE,float,x);
		SERIALIZE(this,Vector3f,WRITE,float,y);
		SERIALIZE(this,Vector3f,WRITE,float,z);
	}

	float Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	float Dot(const Vector3<Type>& _other) const
	{
		return (x * _other.x) + (y * _other.y) + (z * _other.z);
	}
	float Distance(const Vector3<Type>& _other) const
	{
		return (x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y) + (z - _other.z) * (z - _other.z);
	}
	float AngleBetween(Vector3<Type>& _other) const
	{
		Type _angle = Dot(_other) / (Length() * _other.Length());
		_angle = acos(_angle) * 180.0f / M_PI;
		return _angle;
	}
	Vector3<Type> Normalize() const
	{
		Type _length = Length();
		Type _x = round(x / _length);
		Type _y = round(y / _length);
		Type _z = round(z / _length);
		return Vector3<Type>(_x, _y,_z);
	}
	Vector3<Type> Cross(const Vector3<Type>& _other) const
	{
		return Vector3<Type>(y * _other.z - z * _other.y, z * _other.x - x * _other.z, x * _other.y - y * _other.x);
	}

	static vec3 CreateVecFromVector(const Vector3<Type>& _vector)
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

	void operator += (const Type& _value)
	{
		x += _value;
		y += _value;
		z += _value;
	}
	void operator -= (const Type& _value)
	{
		x -= _value;
		y -= _value;
		z -= _value;
	}
	void operator *= (const Type& _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
	}
	void operator /= (const Type& _value)
	{
		x /= _value;
		y /= _value;
		y /= _value;
	}

	Vector3<Type> operator + (const Vector3& _other)
	{
		return Vector3<Type>(x + _other.x, y + _other.y, z + _other.z);
	}
	Vector3<Type> operator - (const Vector3& _other)
	{
		return Vector3<Type>(x - _other.x, y - _other.y, z - _other.z);
	}
	Vector3<Type> operator * (const Vector3& _other)
	{
		return Vector3<Type>(x * _other.x, y * _other.y, z * _other.z);
	}
	Vector3<Type> operator / (const Vector3& _other)
	{
		return Vector3<Type>(x / _other.x, y / _other.y, z / _other.z);
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

	Vector3<Type> operator -()
	{
		return *this * -1.0f;
	}
	Vector3<Type>& operator = (Vector3<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);
		z = move(_other.z);

		return *this;
	}
	Vector3<Type>& operator = (const Vector3<Type>& _other)
	{
		return *this = Vector3<Type>(_other);
	}
	Vector3<Type>& operator = (const aiVector3D& _other)
	{
		return *this = Vector3<Type>(_other);
	}

	friend ostream& operator << (ostream& _stream, const Vector3<Type>& _otherVec)
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