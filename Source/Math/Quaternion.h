/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2010-2024 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

#ifndef REACTPHYSICS3D_QUATERNION_H
#define REACTPHYSICS3D_QUATERNION_H

// Libraries
//#include <reactphysics3d/decimal.h>
//#include <reactphysics3d/mathematics/Vector3.h>

/// ReactPhysics3D namespace
#include "../Utils/CoreMinimal.h"
//#include "mathematics.h"


// Class Quaternion
/**
 * This class represents a quaternion. We use the notation :
 * q = (x*i, y*j, z*k, w) to represent a quaternion.
 */
template <typename Type>
struct Quaternion {

public:

	// -------------------- Attributes -------------------- //

	/// Component x
	Type x;

	/// Component y
	Type y;

	/// Component z
	Type z;

	/// Component w
	Type w;

	// -------------------- Methods -------------------- //

	/// Constructor
	Quaternion();

	/// Constructor with arguments
	Quaternion(Type newX, Type newY, Type newZ, Type newW);

	/// Constructor with the component w and the vector v=(x y z)
	Quaternion(Type newW, const Vector3<Type>& v);

	/// Constructor with the component w and the vector v=(x y z)
	Quaternion(const Vector3<Type>& v, Type newW);

	/// Create a unit quaternion from a rotation matrix
	Quaternion(const Matrix3x3<Type>& matrix);

	/// Set all the values
	void setAllValues(Type newX, Type newY, Type newZ, Type newW);

	/// Set the quaternion to zero
	void setToZero();

	/// Set to the identity quaternion
	void setToIdentity();

	/// Return the vector v=(x y z) of the quaternion
	Vector3<Type> getVectorV() const;

	/// Return the length of the quaternion
	Type length() const;

	/// Return the square of the length of the quaternion
	Type lengthSquare() const;

	/// Normalize the quaternion
	void normalize();

	/// Inverse the quaternion
	void inverse();

	/// Return the unit quaternion
	Quaternion<Type> getUnit() const;

	/// Return the conjugate quaternion
	Quaternion<Type> getConjugate() const;

	/// Return the inverse of the quaternion
	Quaternion<Type> getInverse() const;

	/// Return the orientation matrix corresponding to this quaternion
	Matrix3x3<Type> getMatrix() const;

	/// Return the identity quaternion
	static Quaternion<Type> identity();

	/// Return a quaternion constructed from Euler angles (in radians)
	static Quaternion<Type> fromEulerAngles(Type angleX, Type angleY, Type angleZ);

	/// Return a quaternion constructed from Euler angles (in radians)
	static Quaternion fromEulerAngles(const Vector3<Type>& eulerAngles);

	/// Dot product between two quaternions
	Type dot(const Quaternion<Type>& quaternion) const;

	/// Compute the rotation angle (in radians) and the rotation axis
	void getRotationAngleAxis(Type& angle, Vector3<Type>& axis) const;

	/// Return true if the values are not NAN OR INF
	bool isFinite() const;

	/// Return true if it is a unit quaternion
	bool isUnit() const;

	/// Return true if it is a valid quaternion
	bool isValid() const;

	/// Compute the spherical linear interpolation between two quaternions
	static Quaternion<Type> slerp(const Quaternion<Type>& quaternion1, const Quaternion<Type>& quaternion2, Type t);

	/// Overloaded operator for the addition
	Quaternion<Type> operator+(const Quaternion<Type>& quaternion) const;

	/// Overloaded operator for the substraction
	Quaternion<Type> operator-(const Quaternion<Type>& quaternion) const;

	/// Overloaded operator for addition with assignment
	Quaternion<Type>& operator+=(const Quaternion<Type>& quaternion);

	/// Overloaded operator for substraction with assignment
	Quaternion<Type>& operator-=(const Quaternion<Type>& quaternion);

	/// Overloaded operator for the multiplication with a constant
	Quaternion<Type> operator*(Type nb) const;

	/// Overloaded operator for the multiplication
	Quaternion<Type> operator*(const Quaternion<Type>& quaternion) const;

	/// Overloaded operator for the multiplication with a vector
	Vector3<Type> operator*(const Vector3<Type>& point) const;

	/// Overloaded operator for equality condition
	bool operator==(const Quaternion<Type>& quaternion) const;

	/// Return the string representation
	std::string to_string() const;

private:

	/// Initialize the quaternion using Euler angles
	void initWithEulerAngles(Type angleX, Type angleY, Type angleZ);
};

// Constructor of the class
template <typename Type>
FORCEINLINE Quaternion<Type>::Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0) {

}

// Constructor with arguments
template <typename Type>
FORCEINLINE Quaternion<Type>::Quaternion(Type newX, Type newY, Type newZ, Type newW)
	:x(newX), y(newY), z(newZ), w(newW) {

}

// Constructor with the component w and the vector v=(x y z)
template <typename Type>
FORCEINLINE Quaternion<Type>::Quaternion(Type newW, const Vector3<Type>& v) : x(v.x), y(v.y), z(v.z), w(newW) {

}

// Constructor with the component w and the vector v=(x y z)
template <typename Type>
FORCEINLINE Quaternion<Type>::Quaternion(const Vector3<Type>& v, Type newW) : x(v.x), y(v.y), z(v.z), w(newW) {

}

template<typename Type>
Quaternion<Type>::Quaternion(const Matrix3x3<Type>& matrix)
{

	// Get the trace of the matrix
	Type trace = matrix.getTrace();

	Type r;
	Type s;

	if (trace < Type(0.0)) {
		if (matrix[1][1] > matrix[0][0]) {
			if (matrix[2][2] > matrix[1][1]) {
				r = std::sqrt(matrix[2][2] - matrix[0][0] - matrix[1][1] + Type(1.0));
				s = Type(0.5) / r;

				// Compute the quaternion
				x = (matrix[2][0] + matrix[0][2]) * s;
				y = (matrix[1][2] + matrix[2][1]) * s;
				z = Type(0.5) * r;
				w = (matrix[1][0] - matrix[0][1]) * s;
			}
			else {
				r = std::sqrt(matrix[1][1] - matrix[2][2] - matrix[0][0] + Type(1.0));
				s = Type(0.5) / r;

				// Compute the quaternion
				x = (matrix[0][1] + matrix[1][0]) * s;
				y = Type(0.5) * r;
				z = (matrix[1][2] + matrix[2][1]) * s;
				w = (matrix[0][2] - matrix[2][0]) * s;
			}
		}
		else if (matrix[2][2] > matrix[0][0]) {
			r = std::sqrt(matrix[2][2] - matrix[0][0] - matrix[1][1] + Type(1.0));
			s = Type(0.5) / r;

			// Compute the quaternion
			x = (matrix[2][0] + matrix[0][2]) * s;
			y = (matrix[1][2] + matrix[2][1]) * s;
			z = Type(0.5) * r;
			w = (matrix[1][0] - matrix[0][1]) * s;
		}
		else {
			r = std::sqrt(matrix[0][0] - matrix[1][1] - matrix[2][2] + Type(1.0));
			s = Type(0.5) / r;

			// Compute the quaternion
			x = Type(0.5) * r;
			y = (matrix[0][1] + matrix[1][0]) * s;
			z = (matrix[2][0] + matrix[0][2]) * s;
			w = (matrix[2][1] - matrix[1][2]) * s;
		}
	}
	else {
		r = std::sqrt(trace + Type(1.0));
		s = Type(0.5) / r;

		// Compute the quaternion
		x = (matrix[2][1] - matrix[1][2]) * s;
		y = (matrix[0][2] - matrix[2][0]) * s;
		z = (matrix[1][0] - matrix[0][1]) * s;
		w = Type(0.5) * r;
	}
}

// Set all the values
template <typename Type>
FORCEINLINE void Quaternion<Type>::setAllValues(Type newX, Type newY, Type newZ, Type newW) {
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

// Set the quaternion to zero
template <typename Type>
FORCEINLINE void Quaternion<Type>::setToZero() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

// Set to the identity quaternion
template <typename Type>
FORCEINLINE void Quaternion<Type>::setToIdentity() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

// Return the vector v=(x y z) of the quaternion
template <typename Type>
FORCEINLINE Vector3<Type> Quaternion<Type>::getVectorV() const {

	// Return the vector v
	return Vector3(x, y, z);
}

// Return the length of the quaternion (RP3D_FORCE_INLINE)
template <typename Type>
FORCEINLINE Type Quaternion<Type>::length() const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

// Return the square of the length of the quaternion
template <typename Type>
FORCEINLINE Type Quaternion<Type>::lengthSquare() const {
	return x * x + y * y + z * z + w * w;
}

// Normalize the quaternion
template <typename Type>
FORCEINLINE void Quaternion<Type>::normalize() {

	Type l = length();

	// Check if the length is not equal to zero
	assert(l > MACHINE_EPSILON);

	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

// Inverse the quaternion
template <typename Type>
FORCEINLINE void Quaternion<Type>::inverse() {

	// Use the conjugate of the current quaternion
	x = -x;
	y = -y;
	z = -z;
}

// Return the unit quaternion
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::getUnit() const {
	Type lengthQuaternion = length();

	// Check if the length is not equal to zero
	assert(lengthQuaternion > MACHINE_EPSILON);

	// Compute and return the unit quaternion
	return Quaternion<Type>(x / lengthQuaternion, y / lengthQuaternion,
		z / lengthQuaternion, w / lengthQuaternion);
}

// Return the identity quaternion
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::identity() {
	return Quaternion<Type>(0.0, 0.0, 0.0, 1.0);
}

template<typename Type>
 Quaternion<Type> Quaternion<Type>::fromEulerAngles(Type angleX, Type angleY, Type angleZ)
{

	Quaternion<Type> quaternion;
	quaternion.initWithEulerAngles(angleX, angleY, angleZ);

	return quaternion;
}

 template<typename Type>
 Quaternion<Type> Quaternion<Type>::fromEulerAngles(const Vector3<Type>& eulerAngles)
 {
	 Quaternion<Type> quaternion;
	 quaternion.initWithEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);

	 return quaternion;
 }
// Return the conjugate of the quaternion (RP3D_FORCE_INLINE)
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::getConjugate() const {
	return Quaternion<Type>(-x, -y, -z, w);
}

// Return the inverse of the quaternion (RP3D_FORCE_INLINE)
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::getInverse() const {

	// Return the conjugate quaternion
	return Quaternion<Type>(-x, -y, -z, w);
}

template<typename Type>
Matrix3x3<Type> Quaternion<Type>::getMatrix() const {

	Type nQ = x * x + y * y + z * z + w * w;
	Type s = 0.0;

	if (nQ > Type(0.0)) {
		s = Type(2.0) / nQ;
	}

	// Computations used for optimization (less multiplications)
	Type xs = x * s;
	Type ys = y * s;
	Type zs = z * s;
	Type wxs = w * xs;
	Type wys = w * ys;
	Type wzs = w * zs;
	Type xxs = x * xs;
	Type xys = x * ys;
	Type xzs = x * zs;
	Type yys = y * ys;
	Type yzs = y * zs;
	Type zzs = z * zs;

	// Create the matrix corresponding to the quaternion
	return Matrix3x3<Type>(Type(1.0) - yys - zzs, xys - wzs, xzs + wys,
		xys + wzs, Type(1.0) - xxs - zzs, yzs - wxs,
		xzs - wys, yzs + wxs, Type(1.0) - xxs - yys);
}

// Scalar product between two quaternions
template <typename Type>
FORCEINLINE Type Quaternion<Type>::dot(const Quaternion<Type>& quaternion) const {
	return (x * quaternion.x + y * quaternion.y + z * quaternion.z + w * quaternion.w);
}

template<typename Type>
void Quaternion<Type>::getRotationAngleAxis(Type& angle, Vector3<Type>& axis) const
{
	// Compute the roation angle
	angle = std::acos(w) * Type(2.0);

	// Compute the 3D rotation axis
	Vector3<Type> rotationAxis(x, y, z);

	// Normalize the rotation axis
	rotationAxis = rotationAxis.getUnit();

	// Set the rotation axis values
	axis.setAllValues(rotationAxis.x, rotationAxis.y, rotationAxis.z);
}

// Return true if the values are not NAN OR INF
template <typename Type>
FORCEINLINE bool Quaternion<Type>::isFinite() const {
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
}

// Return true if it is a unit quaternion
template <typename Type>
FORCEINLINE bool Quaternion<Type>::isUnit() const {
	const Type length = std::sqrt(x * x + y * y + z * z + w * w);
	const Type tolerance = 1e-5f;
	return std::abs(length - Type(1.0)) < tolerance;
}

// Return true if it is a valid quaternion
template <typename Type>
FORCEINLINE bool Quaternion<Type>::isValid() const {
	return isFinite() && isUnit();
}

// Compute the spherical linear interpolation between two quaternions.
/// The t argument has to be such that 0 <= t <= 1. This method is static.
template<typename Type>
Quaternion<Type> Quaternion<Type>::slerp(const Quaternion<Type>& quaternion1,
	const Quaternion<Type>& quaternion2, Type t) {
	assert(t >= Type(0.0) && t <= Type(1.0));

	Type invert = 1.0;

	// Compute cos(theta) using the quaternion scalar product
	Type cosineTheta = quaternion1.dot(quaternion2);

	// Take care of the sign of cosineTheta
	if (cosineTheta < Type(0.0)) {
		cosineTheta = -cosineTheta;
		invert = -1.0;
	}

	// Because of precision, if cos(theta) is nearly 1,
	// therefore theta is nearly 0 and we can write
	// sin((1-t)*theta) as (1-t) and sin(t*theta) as t
	const Type epsilon = Type(0.00001);
	if (1 - cosineTheta < epsilon) {
		return quaternion1 * (Type(1.0) - t) + quaternion2 * (t * invert);
	}

	// Compute the theta angle
	Type theta = std::acos(cosineTheta);

	// Compute sin(theta)
	Type sineTheta = std::sin(theta);

	// Compute the two coefficients that are in the spherical linear interpolation formula
	Type coeff1 = std::sin((Type(1.0) - t) * theta) / sineTheta;
	Type coeff2 = std::sin(t * theta) / sineTheta * invert;

	// Compute and return the interpolated quaternion
	return quaternion1 * coeff1 + quaternion2 * coeff2;
}

// Overloaded operator for the addition of two quaternions
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::operator+(const Quaternion<Type>& quaternion) const {

	// Return the result quaternion
	return Quaternion<Type>(x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
}

// Overloaded operator for the substraction of two quaternions
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::operator-(const Quaternion<Type>& quaternion) const {

	// Return the result of the substraction
	return Quaternion<Type>(x - quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
}

// Overloaded operator for addition with assignment
template <typename Type>
FORCEINLINE Quaternion<Type>& Quaternion<Type>::operator+=(const Quaternion<Type>& quaternion) {
	x += quaternion.x;
	y += quaternion.y;
	z += quaternion.z;
	w += quaternion.w;
	return *this;
}

// Overloaded operator for substraction with assignment
template <typename Type>
FORCEINLINE Quaternion<Type>& Quaternion<Type>::operator-=(const Quaternion<Type>& quaternion) {
	x -= quaternion.x;
	y -= quaternion.y;
	z -= quaternion.z;
	w -= quaternion.w;
	return *this;
}

// Overloaded operator for the multiplication with a constant
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::operator*(Type nb) const {
	return Quaternion<Type>(nb * x, nb * y, nb * z, nb * w);
}

// Overloaded operator for the multiplication of two quaternions
template <typename Type>
FORCEINLINE Quaternion<Type> Quaternion<Type>::operator*(const Quaternion<Type>& quaternion) const {

	/* The followin code is equivalent to this
	return Quaternion(w * quaternion.w - getVectorV().dot(quaternion.getVectorV()),
						  w * quaternion.getVectorV() + quaternion.w * getVectorV() +
						  getVectorV().cross(quaternion.getVectorV()));
	*/

	return Quaternion<Type>(w * quaternion.x + quaternion.w * x + y * quaternion.z - z * quaternion.y,
		w * quaternion.y + quaternion.w * y + z * quaternion.x - x * quaternion.z,
		w * quaternion.z + quaternion.w * z + x * quaternion.y - y * quaternion.x,
		w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z);
}

// Overloaded operator for the multiplication with a vector.
/// This methods rotates a point given the rotation of a quaternion.
template <typename Type>
FORCEINLINE Vector3<Type> Quaternion<Type>::operator*(const Vector3<Type>& point) const {

	/* The following code is equivalent to this
	 * Quaternion p(point.x, point.y, point.z, 0.0);
	 * return (((*this) * p) * getConjugate()).getVectorV();
	*/

	const Type prodX = w * point.x + y * point.z - z * point.y;
	const Type prodY = w * point.y + z * point.x - x * point.z;
	const Type prodZ = w * point.z + x * point.y - y * point.x;
	const Type prodW = -x * point.x - y * point.y - z * point.z;
	return Vector3<Type>(w * prodX - prodY * z + prodZ * y - prodW * x,
		w * prodY - prodZ * x + prodX * z - prodW * y,
		w * prodZ - prodX * y + prodY * x - prodW * z);
}

// Overloaded operator for equality condition
template <typename Type>
FORCEINLINE bool Quaternion<Type>::operator==(const Quaternion<Type>& quaternion) const {
	return (x == quaternion.x && y == quaternion.y &&
		z == quaternion.z && w == quaternion.w);
}

// Get the string representation
template <typename Type>
FORCEINLINE std::string Quaternion<Type>::to_string() const {
	return "Quaternion(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," +
		std::to_string(w) + ")";
}

// Initialize the quaternion using Euler angles
template<typename Type>
void Quaternion<Type>::initWithEulerAngles(Type angleX, Type angleY, Type angleZ) {

	Type angle = angleX * Type(0.5);
	const Type sinX = std::sin(angle);
	const Type cosX = std::cos(angle);

	angle = angleY * Type(0.5);
	const Type sinY = std::sin(angle);
	const Type cosY = std::cos(angle);

	angle = angleZ * Type(0.5);
	const Type sinZ = std::sin(angle);
	const Type cosZ = std::cos(angle);

	const Type cosYcosZ = cosY * cosZ;
	const Type sinYcosZ = sinY * cosZ;
	const Type cosYsinZ = cosY * sinZ;
	const Type sinYsinZ = sinY * sinZ;

	x = sinX * cosYcosZ - cosX * sinYsinZ;
	y = cosX * sinYcosZ + sinX * cosYsinZ;
	z = cosX * cosYsinZ - sinX * sinYcosZ;
	w = cosX * cosYcosZ + sinX * sinYsinZ;

	// Normalize the quaternion
	normalize();
}


using QuaternionC = Quaternion<char>;
using QuaternionUs = Quaternion<unsigned short>;
using QuaternionS = Quaternion<short>;
using QuaternionUi = Quaternion<unsigned int>;
using QuaternionI = Quaternion<int>;
using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;


#endif
