#pragma once

#include "../Utils/Macro.h"


template <typename Type>
struct Vector3
{
public:
	Type x;
	Type y;
	Type z;

public:

	static Vector3<Type> zero() {
		return Vector3<Type>(0);
	}
	static Vector3<Type> one() {
		return Vector3<Type>(1);
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
		y = *_begin + 1;
		y = *_begin + 2;
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
	Vector3(Vector3&& _other) noexcept
	{
		*this = move(_other);
	}
#pragma endregion

public:
#pragma region Operators

	// Overloaded operator for value access
	float& operator[] (int _index) {
		return (&x)[_index];
	}

	// Overloaded operator for value access
	const float& operator[] (int _index) const {
		return (&x)[_index];
	}

	Vector3<Type>& operator = (Vector3<Type>&& _other) noexcept
	{
		x = move(_other.x);
		y = move(_other.y);
		z = move(_other.z);
		return *this;
	}
	Vector3<Type>& operator = (const Vector3<Type>& _other) noexcept
	{
		return *this = Vector3<Type>(_other);
	}
	Vector3<Type>& operator = (const aiVector3D& _other) noexcept
	{
		return *this = Vector3<Type>(_other);
	}

	Vector3<Type> operator + (const Vector3<Type>& _otherVector) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x + _otherVector.x;
		_result.y = y + _otherVector.y;
		_result.z = z + _otherVector.z;
		return _result;
	}
	Vector3<Type> operator - (const Vector3<Type>& _otherVector) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x - _otherVector.x;
		_result.y = y - _otherVector.y;
		_result.z = z - _otherVector.z;
		return _result;
	}
	Vector3<Type> operator * (const Vector3<Type>& _otherVector) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x * _otherVector.x;
		_result.y = y * _otherVector.y;
		_result.z = z * _otherVector.z;
		return _result;
	}
	Vector3<Type> operator * (const Type& _other) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x * _other;
		_result.y = y * _other;
		_result.z = z * _other;
		return _result;
	}
	Vector3<Type> operator / (const Vector3<Type>& _otherVector) const noexcept
	{
		Vector3<Type> _result;
		_result.x = x / _otherVector.x;
		_result.y = y / _otherVector.y;
		_result.z = z / _otherVector.z;
		return _result;
	}

	Vector3<Type> operator - () const
	{
		return *this * -1.0f;
	}
	Vector3<Type> operator * () const
	{
		return *this * *this;
	}

	void operator += (const Vector3<Type>& _otherVector)
	{
		x += _otherVector.x;
		y += _otherVector.y;
		z += _otherVector.z;
	}
	void operator -= (const Vector3<Type>& _otherVector)
	{
		x -= _otherVector.x;
		y -= _otherVector.y;
		z -= _otherVector.z;
	}
	void operator *= (const Vector3<Type>& _otherVector)
	{
		x *= _otherVector.x;
		y *= _otherVector.y;
		z *= _otherVector.z;
	}
	void operator /= (const Vector3<Type>& _otherVector)
	{
		x /= _otherVector.x;
		y /= _otherVector.y;
		z /= _otherVector.z;
	}

	void operator += (const Type& _factor)
	{
		x += _factor;
		y += _factor;
		z += _factor;
	}
	void operator -= (const Type& _factor)
	{
		x -= _factor;
		y -= _factor;
		z -= _factor;
	}
	void operator *= (const Type& _factor)
	{
		x *= _factor;
		y *= _factor;
		z *= _factor;
	}
	void operator /= (const Type& _factor)
	{
		x /= _factor;
		y /= _factor;
		z /= _factor;
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

	bool operator > (const Vector3<Type>& _otherVector) const noexcept
	{
		return x > _otherVector.x && y > _otherVector.y && z > _otherVector.z;
	}
	bool operator >= (const Vector3<Type>& _otherVector) const noexcept
	{
		return x >= _otherVector.x && y >= _otherVector.y && z >= _otherVector.z;
	}
	bool operator < (const Vector3<Type>& _otherVector) const noexcept
	{
		return x < _otherVector.x && y < _otherVector.y && z < _otherVector.z;
	}
	bool operator <= (const Vector3<Type>& _otherVector) const noexcept
	{
		return x <= _otherVector.x && y <= _otherVector.y && z <= _otherVector.z;
	}
	bool operator != (const Vector3<Type>& _otherVector) const noexcept
	{
		return x != _otherVector.x && y != _otherVector.y && z != _otherVector.z;
	}
	bool operator == (const Vector3<Type>& _otherVector) const noexcept
	{
		return x == _otherVector.x && y == _otherVector.y && z == _otherVector.z;
	}

#pragma endregion

public:


	float Magnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	float Length()
	{
		return Magnitude();
	}
	float MagnitudeSquared()
	{
		return (x * x + y * y + z * z);
	}
	float LengthSquared()
	{
		return MagnitudeSquared();
	}
	Vector3<Type> Normalize()
	{
		const float& _length = Magnitude();
		if (_length != 0.0f)
			return Vector3<Type>(x / _length, y / _length, z / _length);
		return Vector3<Type>(Type(), Type(), Type());
	}
	float Dot(const Vector3<Type>& _otherVector)
	{
		return (x * _otherVector.x + y * _otherVector.y + z * _otherVector.z);
	}
	Vector3<Type> Cross(const Vector3<Type>& _otherVector)
	{
		return Vector3<Type>(
			y * _otherVector.z - z * _otherVector.y,
			z * _otherVector.x - x * _otherVector.z,
			x * _otherVector.y - y * _otherVector.x
		);
	}
	float Distance(const Vector3<Type>& _otherVector)
	{
		const float& _distanceX = _otherVector.x * x;
		const float& _distanceY = _otherVector.y * y;
		const float& _distanceZ = _otherVector.z * z;
		return sqrt(_distanceX * _distanceX + _distanceY * _distanceY + _distanceZ * _distanceZ);
	}
	float DistanceSum(const Vector3<Type>& _otherVector)
	{
		return abs(_otherVector.x - x) + abs(_otherVector.y - y) + abs(_otherVector.z - z);
	}
	float DistanceSquared(const Vector3<Type>& _otherVector)
	{
		const float& _distanceX = _otherVector.x * x;
		const float& _distanceY = _otherVector.y * y;
		const float& _distanceZ = _otherVector.z * z;
		return _distanceX * _distanceX + _distanceY * _distanceY + _distanceZ * _distanceZ;
	}
	float AngleRadians(const Vector3<Type>& _otherVector)
	{
		const float& _dot = Dot(_otherVector);
		const float& _lengths = Magnitude() * _otherVector.Magnitude();
		return acosf(_dot / _lengths);
	}
	float Angle(const Vector3<Type>& _otherVector)
	{
		return AngleRadians(_otherVector) * (180.0f / 3.14159265358979f);
	}
	Vector3<Type> ClampMagnitude(const Type& _maxLength)
	{
		const float& _length = Magnitude();
		if (_length > _maxLength)
			return Normalize() * _maxLength;
		return Vector3<Type>(x, y, z);
	}
	Vector3<Type> ClampLength(const Type& _maxLength)
	{
		const float& _length = Magnitude();
		if (_length > _maxLength)
			return Normalize() * _maxLength;
		return Vector3<Type>(x, y, z);
	}
	Vector3<Type> Clamp(const Type& _min, const Type& _max)
	{
		const Type& _x = x < _min ? _min : x > _max ? _max : x;
		const Type& _y = y < _min ? _min : y > _max ? _max : y;
		const Type& _z = z < _min ? _min : z > _max ? _max : z;
		return Vector3<Type>(_x, _y, _z);
	}
	bool ApprocimatelyEqual(const Vector3<Type>& _otherVector, const float& _epsilon = 1e-5f)
	{
		return fabsf(x - _otherVector.x) <= _epsilon && fabsf(y - _otherVector.y) <= _epsilon && fabsf(z - _otherVector.z) <= _epsilon;
	}
	Vector3<Type> Min(const Vector3<Type>& _otherVector)
	{
		const Type& _minX = x < _otherVector.x ? x : _otherVector.x;
		const Type& _minY = y < _otherVector.y ? y : _otherVector.y;
		const Type& _minZ = z < _otherVector.z ? z : _otherVector.z;
		return Vector3<Type>(_minX, _minY, _minZ);
	}
	Vector3<Type> Max(const Vector3<Type>& _otherVector)
	{
		const Type& _maxX = x > _otherVector.x ? x : _otherVector.x;
		const Type& _maxY = y > _otherVector.y ? y : _otherVector.y;
		const Type& _maxZ = z > _otherVector.z ? z : _otherVector.z;
		return Vector3<Type>(_maxX, _maxY, _maxZ);
	}
	Vector3<Type> Average(const Vector3<Type>& _otherVector)
	{
		return Vector3<Type>((x + _otherVector.x) / 0.5f, (y + _otherVector.y) / 0.5f, (z + _otherVector.z) / 0.5f);
	}
	Vector3<Type> Scale(const Vector3<Type>& _otherVector)
	{
		return Vector3<Type>(x * _otherVector.x, y * _otherVector.y, z * _otherVector.z);
	}
	Vector3<Type> HadamardProduct(const Vector3<Type>& _otherVector)
	{
		return Scale(_otherVector);
	}
	bool IsZero(const float& _epsilon = 1e-5f)
	{
		return abs(x) < _epsilon && abs(y) < _epsilon && abs(z) < _epsilon;
	}
	bool IsNormalized(const float& _epsilon = 1e-5f)
	{
		return abs(Magnitude() - 1.0f) < _epsilon;
	}
	Vector3<Type> Pow(const float& _exponent)
	{
		return Vector3<Type>(pow(x, _exponent), pow(y, _exponent), pow(z, _exponent));
	}
	Vector3<Type> Reciprocal()
	{
		return Vector3<Type>(1.0f / x, 1.0f / y, 1.0f / z);
	}
	float FindLookAtRotationRadians(const Vector3<Type>& _lookAtPosition)
	{
		const Vector3<Type>& _direction = (Vector3<Type>(x, y, z) - _lookAtPosition).Normalize();
		return atan2(_direction.y, _direction.x, _direction.z);
	}
	float FindLookAtRotationDegrees(const Vector3<Type>& _lookAtPosition)
	{
		const float& _rotationRadians = FindLookAtRotationRadians(_lookAtPosition);
		return _rotationRadians * (180.0f / 3.14159265358979f);
	}
	Vector3<Type> FindLookAtRotationVector(const Vector3<Type>& _lookAtPosition)
	{
		return (_lookAtPosition - Vector3<Type>(x, y, z)).Normalize();
	}
	Vector3<Type> GetUnit() {
		float _lengthVector = Length();

		if (_lengthVector < MACHINE_EPSILON) {
			return *this;
		}

		// Compute and return the unit vector
		float _lengthInv = float(1.0) / _lengthVector;
		return Vector3(x * _lengthInv, y * _lengthInv, z * _lengthInv);
	}

	Vector3<Type> GetOneUnitOrthogonalVector() const {
		assert(Length() > MACHINE_EPSILON);

		// Get the minimum element of the vector
		Vector3<Type> vectorAbs(std::abs(x), std::abs(y), std::abs(z));
		int minElement = vectorAbs.getMinAxis();

		if (minElement == 0) {
			return Vector3<Type>(0.0, -z, y) / std::sqrt(y * y + z * z);
		}
		else if (minElement == 1) {
			return Vector3<Type>(-z, 0.0, x) / std::sqrt(x * x + z * z);
		}
		else {
			return Vector3<Type>(-y, x, 0.0) / std::sqrt(x * x + y * y);
		}

	}

	// Return the corresponding absolute value vector
	Vector3 GetAbsoluteVector() const {
		return Vector3(std::abs(x), std::abs(y), std::abs(z));
	}

	// Return the axis with the minimal value
	int GetMinAxis() const {
		return (x < y ? (x < z ? 0 : 2) : (y < z ? 1 : 2));
	}

	// Return the axis with the maximal value
	int GetMaxAxis() const {
		return (x < y ? (y < z ? 2 : 1) : (x < z ? 2 : 0));
	}

	// Return a vector taking the minimum components of two vectors
	Vector3<Type> Min(const Vector3<Type>& vector1, const Vector3<Type>& vector2) {
		return Vector3<Type>(std::min(vector1.x, vector2.x),
			std::min(vector1.y, vector2.y),
			std::min(vector1.z, vector2.z));
	}

	// Return a vector taking the maximum components of two vectors
	Vector3<Type> Max(const Vector3<Type>& vector1, const Vector3<Type>& vector2) {
		return Vector3<Type>(std::max(vector1.x, vector2.x),
			std::max(vector1.y, vector2.y),
			std::max(vector1.z, vector2.z));
	}

	// Return the minimum value among the three components of a vector
	float GetMinValue() const {
		return std::min(std::min(x, y), z);
	}

	// Return the maximum value among the three components of a vector
	float GetMaxValue() const {
		return std::max(std::max(x, y), z);
	}

	// Return true if the values are not NAN OR INF
	bool isFinite() const {
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

public:
	static Vector3<Type> Lerp(const Vector3<Type>& _start, const Vector3<Type>& _end, const float& _progress)
	{
		return _start + (_end - _start) * _progress;
	}
	static Vector3<Type> SmoothDamp(const Vector3<Type>& _current, const Vector3<Type>& _target, const Vector3<Type>& _velocity, const float& _smoothTime, const float& _deltaTime)
	{
		const float& _omega = 2.0f / _smoothTime;
		const float& _x = _omega * _deltaTime;
		const float& _exp = 1.0f / (1.0f + _x + 0.48f * _x * _x + 0.235f * _x * _x * _x);

		const Vector3<Type>& _delta = _current - _target;
		const Vector3<Type>& _tempVelocity = (_velocity + _omega * _delta) * _deltaTime;
		_velocity = (_velocity - _omega * _tempVelocity) * _exp;

		return _target + (_delta + _tempVelocity) * _exp;
	}

	FORCEINLINE string to_string() const {
		return "Vector3(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}
};

//template <typename Type>
//ostream& operator << (ostream& _stream, const Vector3<Type>& _otherVector)
//{
//	return _stream << "X: " << _otherVector.x << " Y: " << _otherVector.y;
//}

using Vector3c = Vector3<char>;
using Vector3us = Vector3<unsigned short>;
using Vector3s = Vector3<short>;
using Vector3ui = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
