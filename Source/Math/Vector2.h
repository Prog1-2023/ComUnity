#pragma once

#include <initializer_list>
#include <exception>
#include <cmath>
#include <cctype>

using namespace std;

template <typename Type>
struct Vector2
{
	Type x;
	Type y;

public:
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
	Vector2(const aiVector3D& _other)
	{
		x = _other.x;
		y = _other.y;
	}
	Vector2(Vector2&& _other) noexcept
	{
		*this = move(_other);
	}
#pragma endregion

public:
#pragma region Operators
	Vector2<Type>& operator = (Vector2<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);
		return *this;
	}
	Vector2<Type>& operator = (const Vector2<Type>& _other) noexcept
	{
		return *this = Vector2<Type>(_other);
	}
	Vector2<Type>& operator = (const aiVector3D& _other) noexcept
	{
		return *this = Vector2<Type>(_other);
	}

	Vector2<Type> operator + (const Vector2<Type>& _otherVector) const noexcept
	{
		Vector2<Type> _result;
		_result.x = x + _otherVector.x;
		_result.y = y + _otherVector.y;
		return _result;
	}
	Vector2<Type> operator - (const Vector2<Type>& _otherVector) const noexcept
	{
		Vector2<Type> _result;
		_result.x = x - _otherVector.x;
		_result.y = y - _otherVector.y;
		return _result;
	}
	Vector2<Type> operator * (const Vector2<Type>& _otherVector) const noexcept
	{
		Vector2<Type> _result;
		_result.x = x * _otherVector.x;
		_result.y = y * _otherVector.y;
		return _result;
	}
	Vector2<Type> operator / (const Vector2<Type>& _otherVector) const noexcept
	{
		Vector2<Type> _result;
		_result.x = x / _otherVector.x;
		_result.y = y / _otherVector.y;
		return _result;
	}

	Vector2<Type> operator - () const
	{
		return *this * -1.0f;
	}
	Vector2<Type> operator * () const
	{
		return *this * *this;
	}

	void operator += (const Vector2<Type>& _otherVector)
	{
		x += _otherVector.x;
		y += _otherVector.y;
	}
	void operator -= (const Vector2<Type>& _otherVector)
	{
		x -= _otherVector.x;
		y -= _otherVector.y;
	}
	void operator *= (const Vector2<Type>& _otherVector)
	{
		x *= _otherVector.x;
		y *= _otherVector.y;
	}
	void operator /= (const Vector2<Type>& _otherVector)
	{
		x /= _otherVector.x;
		y /= _otherVector.y;
	}

	void operator += (const Type& _factor)
	{
		x += _factor;
		y += _factor;
	}
	void operator -= (const Type& _factor)
	{
		x -= _factor;
		y -= _factor;
	}
	void operator *= (const Type& _factor)
	{
		x *= _factor;
		y *= _factor;
	}
	void operator /= (const Type& _factor)
	{
		x /= _factor;
		y /= _factor;
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

	bool operator > (const Vector2<Type>& _otherVector) const noexcept
	{
		return x > _otherVector.x && y > _otherVector.y;
	}
	bool operator >= (const Vector2<Type>& _otherVector) const noexcept
	{
		return x >= _otherVector.x && y >= _otherVector.y;
	}
	bool operator < (const Vector2<Type>& _otherVector) const noexcept
	{
		return x < _otherVector.x && y < _otherVector.y;
	}
	bool operator <= (const Vector2<Type>& _otherVector) const noexcept
	{
		return x <= _otherVector.x && y <= _otherVector.y;
	}
	bool operator != (const Vector2<Type>& _otherVector) const noexcept
	{
		return x != _otherVector.x && y != _otherVector.y;
	}
	bool operator == (const Vector2<Type>& _otherVector) const noexcept
	{
		return x == _otherVector.x && y == _otherVector.y;
	}


	Type& operator[] (int index) {
		return (&x)[index];
	}
	const Type& operator[] (int index) const {
		return (&x)[index];
	}


#pragma endregion

public:
	float Magnitude()
	{
		return sqrtf(x * x + y * y);
	}
	float Length()
	{
		return Magnitude();
	}
	float MagnitudeSquared()
	{
		return (x * x + y * y);
	}
	float LengthSquared()
	{
		return MagnitudeSquared();
	}
	Vector2<Type> Normalize()
	{
		const float& _length = Magnitude();
		if (_length != 0.0f)
			return Vector2<Type>(x / _length, y / _length);
		return Vector2<Type>(Type(), Type());
	}
	float Dot(const Vector2<Type>& _otherVector)
	{
		return (x * _otherVector.x + y * _otherVector.y);
	}
	float Distance(const Vector2<Type>& _otherVector)
	{
		const float& _distanceX = _otherVector.x * x;
		const float& _distanceY = _otherVector.y * y;
		return sqrt(_distanceX * _distanceX + _distanceY * _distanceY);
	}
	float DistanceSum(const Vector2<Type>& _otherVector)
	{
		return abs(_otherVector.x - x) + abs(_otherVector.y - y);
	}
	float DistanceSquared(const Vector2<Type>& _otherVector)
	{
		const float& _distanceX = _otherVector.x * x;
		const float& _distanceY = _otherVector.y * y;
		return _distanceX * _distanceX + _distanceY * _distanceY;
	}
	float AngleRadians(const Vector2<Type>& _otherVector)
	{
		const float& _dot = Dot(_otherVector);
		const float& _lengths = Magnitude() * _otherVector.Magnitude();
		return acosf(_dot / _lengths);
	}
	float Angle(const Vector2<Type>& _otherVector)
	{
		return AngleRadians(_otherVector) * (180.0f / 3.14159265358979f);
	}
	Vector2<Type> ClampMagnitude(const Type& _maxLength)
	{
		const float& _length = Magnitude();
		if (_length > _maxLength)
			return Normalize() * _maxLength;
		return Vector2<Type>(x, y);
	}
	Vector2<Type> ClampLength(const Type& _maxLength)
	{
		const float& _length = Magnitude();
		if (_length > _maxLength)
			return Normalize() * _maxLength;
		return Vector2<Type>(x, y);
	}
	Vector2<Type> Clamp(const Type& _min, const Type& _max)
	{
		const Type& _x = x < _min ? _min : x > _max ? _max : x;
		const Type& _y = y < _min ? _min : y > _max ? _max : y;
		return Vector2<Type>(_x, _y);
	}
	bool ApprocimatelyEqual(const Vector2<Type>& _otherVector, const float& _epsilon = 1e-5f)
	{
		return fabsf(x - _otherVector.x) <= _epsilon && fabsf(y - _otherVector.y) <= _epsilon;
	}
	Vector2<Type> Min(const Vector2<Type>& _otherVector)
	{
		const Type& _minX = x < _otherVector.x ? x : _otherVector.x;
		const Type& _minY = y < _otherVector.y ? y : _otherVector.y;
		return Vector2<Type>(_minX, _minY);
	}
	Vector2<Type> Max(const Vector2<Type>& _otherVector)
	{
		const Type& _maxX = x > _otherVector.x ? x : _otherVector.x;
		const Type& _maxY = y > _otherVector.y ? y : _otherVector.y;
		return Vector2<Type>(_maxX, _maxY);
	}
	Vector2<Type> Average(const Vector2<Type>& _otherVector)
	{
		return Vector2<Type>((x + _otherVector.x) / 0.5f, (y + _otherVector.y) / 0.5f);
	}
	Vector2<Type> Scale(const Vector2<Type>& _otherVector)
	{
		return Vector2<Type>(x * _otherVector.x, y * _otherVector.y);
	}
	Vector2<Type> HadamardProduct(const Vector2<Type>& _otherVector)
	{
		return Scale(_otherVector);
	}
	bool IsZero(const float& _epsilon = 1e-5f)
	{
		return abs(x) < _epsilon && abs(y) < _epsilon;
	}
	bool IsNormalized(const float& _epsilon = 1e-5f)
	{
		return abs(Magnitude() - 1.0f) < _epsilon;
	}
	Vector2<Type> Pow(const float& _exponent)
	{
		return Vector2<Type>(pow(x, _exponent), pow(y, _exponent));
	}
	Vector2<Type> Reciprocal()
	{
		return Vector2<Type>(1.0f / x, 1.0f / y);
	}
	float FindLookAtRotationRadians(const Vector2<Type>& _lookAtPosition)
	{
		const Vector2<Type>& _direction = (Vector2<Type>(x, y) - _lookAtPosition).Normalize();
		return atan2(_direction.y, _direction.x);
	}
	float FindLookAtRotationDegrees(const Vector2<Type>& _lookAtPosition)
	{
		const float& _rotationRadians = FindLookAtRotationRadians(_lookAtPosition);
		return _rotationRadians * (180.0f / 3.14159265358979f);
	}
	Vector2<Type> FindLookAtRotationVector(const Vector2<Type>& _lookAtPosition)
	{
		return (_lookAtPosition - Vector2<Type>(x, y)).Normalize();
	}
	Vector2<Type> GetVectorByDegree(const float& _degrees)
	{
		float _radians = _degrees * (3.14159265358979f / 180.0f);
		return Vector2<Type>(cos(_radians), sin(_radians));
	}
	Vector2<Type> GetVectorByRadian(const float& _radians)
	{
		return Vector2<Type>(cos(_radians), sin(_radians));
	}
	Vector2<Type> RotateVectorByDegree(const float& _degrees)
	{
		const float& _radians = _degrees * (3.14159265358979f / 180.0f);

		const Type& _newX = x * cos(_radians) - y * sin(_radians);
		const Type& _newY = x * sin(_radians) + y * cos(_radians);
		return Vector2<Type>(_newX, _newY);
	}
	Vector2<Type> RotateVectorByRadians(const float& _radians)
	{
		const Type& _newX = x * cos(_radians) - y * sin(_radians);
		const Type& _newY = x * sin(_radians) + y * cos(_radians);
		return Vector2<Type>(_newX, _newY);
	}

public:
	static Vector2<Type> Lerp(const Vector2<Type>& _start, const Vector2<Type>& _end, const float& _progress)
	{
		return _start + (_end - _start) * _progress;
	}
	static Vector2<Type> SmoothDamp(const Vector2<Type>& _current, const Vector2<Type>& _target, const Vector2<Type>& _velocity, const float& _smoothTime, const float& _deltaTime)
	{
		const float& _omega = 2.0f / _smoothTime;
		const float& _x = _omega * _deltaTime;
		const float& _exp = 1.0f / (1.0f + _x + 0.48f * _x * _x + 0.235f * _x * _x * _x);

		const Vector2<Type>& _delta = _current - _target;
		const Vector2<Type>& _tempVelocity = (_velocity + _omega * _delta) * _deltaTime;
		_velocity = (_velocity - _omega * _tempVelocity) * _exp;

		return _target + (_delta + _tempVelocity) * _exp;
	}
};

//template <typename Type>
//ostream& operator << (ostream& _stream, const Vector2<Type>& _otherVector)
//{
//	return _stream << "X: " << _otherVector.x << " Y: " << _otherVector.y;
//}

using Vector2c = Vector2<char>;
using Vector2us = Vector2<unsigned short>;
using Vector2s = Vector2<short>;
using Vector2ui = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
