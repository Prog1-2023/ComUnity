#pragma once

#include "../Utils/Macro.h"

template <typename Type>
struct Vector4
{
	Type x;
	Type y;
	Type z;
	Type w;

public:
#pragma region Constructors
	Vector4()
	{
		x = Type();
		y = Type();
		z = Type();
	}
	Vector4(const Type& _value)
	{
		x = _value;
		y = _value;
		z = _value;
	}
	Vector4(const Type& _x, const Type& _y, const Type& _z, const Type& _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	Vector4(const initializer_list<Type>& _list)
	{
		const initializer_list<Type>::value_type* _begin = _list.begin();
		x = *_begin;
		y = *_begin + 1;
		z = *_begin + 2;
		w = *_begin + 3;
	}
	Vector4(const Vector4& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;
	}
	Vector4(Vector4&& _other) noexcept
	{
		*this = move(_other);
	}
#pragma endregion

public:
#pragma region Operators
	Vector4<Type>& operator = (Vector4<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);
		z = move(_other.z);
		w = move(_other.w);
		return *this;
	}
	Vector4<Type>& operator = (const Vector4<Type>& _other) noexcept
	{
		return *this = Vector4<Type>(_other);
	}
	Vector4<Type>& operator = (const aiVector3D& _other) noexcept
	{
		return *this = Vector4<Type>(_other);
	}

	Vector4<Type> operator + (const Vector4<Type>& _otherVector) const noexcept
	{
		Vector4<Type> _result;
		_result.x = x + _otherVector.x;
		_result.y = y + _otherVector.y;
		_result.z = z + _otherVector.z;
		_result.w = w + _otherVector.w;
		return _result;
	}
	Vector4<Type> operator - (const Vector4<Type>& _otherVector) const noexcept
	{
		Vector4<Type> _result;
		_result.x = x - _otherVector.x;
		_result.y = y - _otherVector.y;
		_result.z = z - _otherVector.z;
		_result.w = w - _otherVector.w;
		return _result;
	}
	Vector4<Type> operator * (const Vector4<Type>& _otherVector) const noexcept
	{
		Vector4<Type> _result;
		_result.x = x * _otherVector.x;
		_result.y = y * _otherVector.y;
		_result.z = z * _otherVector.z;
		_result.w = w * _otherVector.w;
		return _result;
	}
	Vector4<Type> operator / (const Vector4<Type>& _otherVector) const noexcept
	{
		Vector4<Type> _result;
		_result.x = x / _otherVector.x;
		_result.y = y / _otherVector.y;
		_result.z = z / _otherVector.z;
		_result.w = w / _otherVector.w;
		return _result;
	}

	Vector4<Type> operator - () const
	{
		return *this * -1.0f;
	}
	Vector4<Type> operator * () const
	{
		return *this * *this;
	}

	void operator += (const Vector4<Type>& _otherVector)
	{
		x += _otherVector.x;
		y += _otherVector.y;
		z += _otherVector.z;
		w += _otherVector.w;
	}
	void operator -= (const Vector4<Type>& _otherVector)
	{
		x -= _otherVector.x;
		y -= _otherVector.y;
		z -= _otherVector.z;
		w -= _otherVector.w;
	}
	void operator *= (const Vector4<Type>& _otherVector)
	{
		x *= _otherVector.x;
		y *= _otherVector.y;
		z *= _otherVector.z;
		w *= _otherVector.w;
	}
	void operator /= (const Vector4<Type>& _otherVector)
	{
		x /= _otherVector.x;
		y /= _otherVector.y;
		z /= _otherVector.z;
		w /= _otherVector.w;
	}

	void operator += (const Type& _factor)
	{
		x += _factor;
		y += _factor;
		z += _factor;
		w += _factor;
	}
	void operator -= (const Type& _factor)
	{
		x -= _factor;
		y -= _factor;
		z -= _factor;
		w -= _factor;
	}
	void operator *= (const Type& _factor)
	{
		x *= _factor;
		y *= _factor;
		z *= _factor;
		w *= _factor;
	}
	void operator /= (const Type& _factor)
	{
		x /= _factor;
		y /= _factor;
		z /= _factor;
		w /= _factor;
	}

	void operator ++ ()
	{
		++x;
		++y;
		++z;
		++w;
	}
	void operator -- ()
	{
		--x;
		--y;
		--z;
		--w;
	}

	bool operator > (const Vector4<Type>& _otherVector) const noexcept
	{
		return x > _otherVector.x && y > _otherVector.y && z > _otherVector.z && w > _otherVector.w;
	}
	bool operator >= (const Vector4<Type>& _otherVector) const noexcept
	{
		return x >= _otherVector.x && y >= _otherVector.y && z >= _otherVector.z && w >= _otherVector.w;
	}
	bool operator < (const Vector4<Type>& _otherVector) const noexcept
	{
		return x < _otherVector.x && y < _otherVector.y && z < _otherVector.z && w < _otherVector.w;
	}
	bool operator <= (const Vector4<Type>& _otherVector) const noexcept
	{
		return x <= _otherVector.x && y <= _otherVector.y && z <= _otherVector.z && w <= _otherVector.w;
	}
	bool operator != (const Vector4<Type>& _otherVector) const noexcept
	{
		return x != _otherVector.x && y != _otherVector.y && z != _otherVector.z && w != _otherVector.w;
	}
	bool operator == (const Vector4<Type>& _otherVector) const noexcept
	{
		return x == _otherVector.x && y == _otherVector.y && z == _otherVector.z && w == _otherVector.w;
	}

	//Implicit cast
	operator vec4() const { return vec4(x, y, z, w); }
#pragma endregion

public:
	std::string ToString() const { return "Vec4 ( " + std::to_string(x) + " : " + std::to_string(y) + " : " + std::to_string(z) + " : " + std::to_string(w) + " )"; }


public:
	//Here make your own methods utils of the class Vector4.
	//It's not a priority, since, at the moment, this class is only used for RGBA.
};

//template <typename Type>
//ostream& operator << (ostream& _stream, const Vector4<Type>& _otherVector)
//{
//	return _stream << "X: " << _otherVector.x << " Y: " << _otherVector.y;
//}

using Vector4c = Vector4<char>;
using Vector4us = Vector4<unsigned short>;
using Vector4s = Vector4<short>;
using Vector4ui = Vector4<unsigned int>;
using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
