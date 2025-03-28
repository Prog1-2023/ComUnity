#pragma once
#include <initializer_list>
#include <exception>
#include <cctype>

using namespace std;

template<typename Type>
struct Vector2
{
	Type x;
	Type y;

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
	Vector2(const initializer_list<Type>& _list)
	{
		const initializer_list<Type>::value_type* _begin = _list.begin();
		x = *_begin;
		y = _list.size() == 1 ? x : *(_begin + 1);
	}
	Vector2(const Vector2& _other)
	{
		x = _other.x;
		y = _other.y;
	}
	Vector2(Vector2&& _other) noexcept
	{
		*this = move(_other);
	}
	Vector2(const aiVector3D& _other)
	{
		x = _other.x;
		y = _other.y;
	}
#pragma endregion

#pragma region Methods

	float Length()
	{
		return sqrtf(pow(x, 2) + pow(y, 2));
	}

	static float Dot(Vector2<Type> _otherVec)
	{
		return (x * _otherVec.x) + (y * _otherVec.y);
	}

	float Magnitude()
	{
		return sqrtf((x * x - y * y));
	}

	Vector2 Normalize()
	{
		float _length = Length();
		return this * _length;
	}

#pragma endregion

#pragma region Operators

	// Compute
	Vector2<Type> operator + (const Vector2<Type>& _otherVec)
	{
		Vector2<Type> _result;
		_result.x = x + _otherVec.x;
		_result.y = y + _otherVec.y;
		return _result;
	}
	Vector2<Type> operator - (const Vector2<Type>& _otherVec)
	{
		Vector2<Type> _result;
		_result.x = x - _otherVec.x;
		_result.y = y - _otherVec.y;
		return _result;
	}
	Vector2<Type> operator * (const Vector2<Type>& _otherVec)
	{
		Vector2<Type> _result;
		_result.x = x * _otherVec.x;
		_result.y = y * _otherVec.y;
		return _result;
	}
	Vector2<Type> operator / (const Vector2<Type>& _otherVec)
	{
		Vector2<Type> _result;
		_result.x = x / _otherVec.x;
		_result.y = y / _otherVec.y;

		return _result;
	}
	Vector2<Type> operator / (const float _value)
	{
		Vector2<Type> _result;
		_result.x = x / _value;
		_result.y = y / _value;

		return _result;
	}
	Vector2<Type>& operator = (Vector2<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);

		return *this;
	}

	Vector2<Type> operator - () const
	{
		return *this * -1.0f;
	}
	Vector2<Type> operator * () const
	{
		return *this * *this;
	}

	// Assignations
	void operator += (const Type _factor)
	{
		x += _factor;
		y += _factor;
	}
	void operator -= (const Type _factor)
	{
		x -= _factor;
		y -= _factor;
	}
	void operator *= (const Type _factor)
	{
		x *= _factor;
		y *= _factor;
	}
	void operator /= (const Type _factor)
	{
		x /= _factor;
		y /= _factor;
	}

	void operator += (const Vector2<Type>& _otherVec)
	{
		x += _otherVec.x;
		y += _otherVec.y;
	}
	void operator -= (const Vector2<Type>& _otherVec)
	{
		x -= _otherVec.x;
		y -= _otherVec.y;
	}
	void operator *= (const Vector2<Type>& _otherVec)
	{
		x *= _otherVec.x;
		y *= _otherVec.y;
	}
	void operator /= (const Vector2<Type>& _otherVec)
	{
		x /= _otherVec.x;
		y /= _otherVec.y;
	}

	void operator ++()
	{
		++x;
		++y;
	}
	void operator --()
	{
		--x;
		--y;
	}

	//Comparaison
	bool operator > (const Vector2<Type>& _otherVec) const noexcept
	{
		return x > _otherVec.x && y > _otherVec.y;
	}
	bool operator = (const Vector2<Type>& _otherVec) const noexcept
	{
		return   x = _otherVec.x && y = _otherVec.y;
	}
	bool operator < (const Vector2<Type>& _otherVec) const noexcept
	{
		return   x < _otherVec.x && y < _otherVec.y;
	}
	bool operator <= (const Vector2<Type>& _otherVec) const noexcept
	{
		return   x <= _otherVec.x && y <= _otherVec.y;
	}
	bool operator != (const Vector2<Type>& _otherVec) const noexcept
	{
		return   x != _otherVec.x && y != _otherVec.y;
	}
	bool operator == (const Vector2<Type>& _otherVec) const noexcept
	{
		return  x == _otherVec.x && y == _otherVec.y;
	}

	//Streams
	friend ostream& operator << (ostream& _stream, const Vector2<Type>& _otherVec)
	{
		return _stream << "X: " << _otherVec.x << " Y: " << _otherVec.y;
	}

	Vector2<Type> operator = (const Vector2<Type>& _otherVec)
	{
		return *this = Vector2<Type>(_otherVec);
	}
	Vector2<Type> operator = (const aiVector3D& _otherVec)
	{
		return *this = Vector2<Type>(_otherVec);
	}
#pragma endregion
};


template<typename Type>
ostream& operator << (ostream& _stream, const Vector2<Type>& _otherVec)
{
	return _stream << "X: " << _otherVec.x << " Y: " << _otherVec.y;
}

using Vector2c = Vector2<char>;
using Vector2us = Vector2<unsigned short>;
using Vector2s = Vector2<short>;
using Vector2ui = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;