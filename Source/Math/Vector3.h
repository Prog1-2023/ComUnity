#pragma once
#include "../Utils/CoreMinimal.h"

using namespace std;
template <typename Type>
struct Vector3
{
	Type x;
	Type y;
	Type z;

	//will return a (0,0,0) Vector
	static Vector3 Zero()
	{
		return Vector3(0.0f);
	}
	//will return a (1,1,1) Vector
	static Vector3 One()
	{
		return Vector3(1.0f);
	}

#pragma region Constructors

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
	Vector3(const Type& _x, const Type& _y, const Type& _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3(const initializer_list<Type>& _list)
	{
		const initializer_list<Type>::value_type* _begin = _list.begin();
		x = *_begin;
		y = _list.size() == 1 ? x : *(_begin + 1);
		z = _list.size() == 1 ? x : *(_begin + 2);
	}
	Vector3(const Vector3<Type>& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}
	Vector3(Vector3<Type>&& _other) noexcept
	{
		*this = move(_other);
	}
	Vector3(const aiVector3D& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}

#pragma endregion

#pragma region Operators

	Vector3<Type> operator + (const Vector3<Type>& _otherVec) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x + _otherVec.x;
		_result.y = y + _otherVec.y;
		_result.z = z + _otherVec.z;

		return _result;
	}
	Vector3<Type> operator - (const Vector3<Type>& _otherVec) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x - _otherVec.x;
		_result.y = y - _otherVec.y;
		_result.z = z - _otherVec.z;

		return _result;
	}
	Vector3<Type> operator * (const Vector3<Type>& _otherVec) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x * _otherVec.x;
		_result.y = y * _otherVec.y;
		_result.z = z * _otherVec.z;

		return _result;
	}
	Vector3<Type> operator / (const Vector3<Type>& _otherVec) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x / _otherVec.x;
		_result.y = y / _otherVec.y;
		_result.z = z / _otherVec.z;

		return _result;
	}
	Vector3<Type> operator = (const Vector3<Type>& _other)
	{
		x = move(_other.x);
		y = move(_other.y);
		z = move(_other.z);

		return *this;
	}

	Vector3<Type> operator - () const
	{
		return *this * -1.0f;
	}
	Vector3<Type> operator * () const
	{
		return *this * *this;
	}

	void operator += (const Type _factor)
	{
		x += _factor;
		y += _factor;
		z += _factor;
	}
	void operator -= (const Type _factor)
	{
		x -= _factor;
		y -= _factor;
		z -= _factor;
	}
	void operator *= (const Type _factor)
	{
		x *= _factor;
		y *= _factor;
		z *= _factor;
	}
	void operator /= (const Type _factor)
	{
		x /= _factor;
		y /= _factor;
		z /= _factor;
	}

	void operator += (const Vector3<Type>& _otherVec)
	{
		x += _otherVec.x;
		y += _otherVec.y;
		z += _otherVec.z;
	}
	void operator -= (const Vector3<Type>& _otherVec)
	{
		x -= _otherVec.x;
		y -= _otherVec.y;
		z -= _otherVec.z;
	}
	void operator *= (const Vector3<Type>& _otherVec)
	{
		x *= _otherVec.x;
		y *= _otherVec.y;
		z *= _otherVec.z;
	}
	void operator /= (const Vector3<Type>& _otherVec)
	{
		x /= _otherVec.x;
		y /= _otherVec.y;
		z /= _otherVec.z;
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

	bool operator > (const Vector3<Type>& _otherVec) const noexcept
	{
		return x > _otherVec.x
			&& y > _otherVec.y
			&& z > _otherVec.z;
	}
	bool operator >= (const Vector3<Type>& _otherVec) const noexcept
	{
		return x >= _otherVec.x
			&& y >= _otherVec.y
			&& z >= _otherVec.z;
	}
	bool operator < (const Vector3<Type>& _otherVec) const noexcept
	{
		return x < _otherVec.x
			&& y < _otherVec.y
			&& z < _otherVec.z;
	}
	bool operator <= (const Vector3<Type>& _otherVec) const noexcept
	{
		return x <= _otherVec.x
			&& y <= _otherVec.y
			&& z <= _otherVec.z;
	}
	bool operator != (const Vector3<Type>& _otherVec) const noexcept
	{
		return x != _otherVec.x
			&& y != _otherVec.y
			&& z != _otherVec.z;
	}
	bool operator == (const Vector3<Type>& _otherVec) const noexcept
	{
		return x == _otherVec.x
			&& y == _otherVec.y
			&& z == _otherVec.z;
	}

	/*Vector3<Type> operator = (const Vector3<Type>& _other)
	{
		return *this = Vector3<Type>(_other);
	}*/
	Vector3<Type> operator = (const aiVector3D& _other)
	{
		return *this = Vector3<Type>(_other);
	}

	//friend ostream& operator << (ostream& _stream, const Vector3<Type>& _otherVec)
	//{
	//	return _stream << "x: " << _otherVec.x << " y: " << _otherVec.y << " z: " << _otherVec.z;
	//}
#pragma endregion

#pragma region Methods
	//return the Length of the vector
	__forceinline float Length(Vector3<Type> _vector)
	{
		return sqrt(pow(_vector.x, 2) + pow(_vector.y, 2) + pow(_vector.z, 2));
	}

	//return the angle of two vector using their Length and the angle 
	__forceinline float Scalar(Vector3<Type> _a, Vector3<Type> _b, float _angle)
	{
		return Length(_a) * Length(_b) * cos(_angle);
	}

	//return the Dot product of two vector
	__forceinline float Dot(Vector3<Type> _a, Vector3<Type> _b)
	{
		return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
	}

	//return the Cross product of two vector
	__forceinline Vector3<Type> Cross(Vector3<Type> _a, Vector3<Type> _b)
	{
		float _x = _a.y * _b.z - _a.z * _b.y;
		float _y = _a.z * _b.x - _a.x * _b.z;
		float _z = _a.x * _b.y - _a.y * _b.x;

		return Vector3<Type>(_x, _y, _z);
	}

#pragma endregion

};

//template <typename Type>
//ostream& operator << (ostream& _stream, const Vector3<Type>& _otherVec)
//{
//	return _stream << "x: " << _otherVec.x << " y: " << _otherVec.y << " z: " << _otherVec.z;
//}

using Vector3c = Vector3<char>;
using Vector3us = Vector3<unsigned short>;
using Vector3s = Vector3<short>;
using Vector3ui = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;