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


#ifndef MATRIX3X3_H
#define MATRIX3X3_H

// Libraries
#include <cassert>
//#include <reactphysics3d/mathematics/Vector3.h>
//#include "../Utils/CoreMinimal.h"
#include "Vector3.h"

template <typename Type>
class Matrix3x3 {

    private :

        // -------------------- Attributes -------------------- //

        /// Rows of the matrix;
        Vector3<Type> mRows[3];

    public :

        // -------------------- Methods -------------------- //

        /// Constructor
        Matrix3x3();

        /// Constructor
        Matrix3x3(Type value);

        /// Constructor
        Matrix3x3(Type a1, Type a2, Type a3, Type b1, Type b2, Type b3,
            Type c1, Type c2, Type c3);

        /// Set all the values in the matrix
        void setAllValues(Type a1, Type a2, Type a3, Type b1, Type b2, Type b3,
            Type c1, Type c2, Type c3);

        /// Set the matrix to zero
        void setToZero();

        /// Return a column
        Vector3<Type> getColumn(int i) const;

        /// Return a row
        Vector3<Type> getRow(int i) const;

        /// Return the transpose matrix
        Matrix3x3 getTranspose() const;

        /// Return the determinant of the matrix
        Type getDeterminant() const;

        /// Return the trace of the matrix
        Type getTrace() const;

        /// Return the inverse matrix
        Matrix3x3 getInverse() const;

        /// Return the inverse matrix
        Matrix3x3 getInverse(Type determinant) const;

        /// Return the matrix with absolute values
        Matrix3x3 getAbsoluteMatrix() const;

        /// Set the matrix to the identity matrix
        void setToIdentity();

        /// Return the 3x3 identity matrix
        static Matrix3x3 identity();

        /// Return the 3x3 zero matrix
        static Matrix3x3 zero();

        /// Return a skew-symmetric matrix using a given vector that can be used
        /// to compute cross product with another vector using matrix multiplication
        static Matrix3x3 computeSkewSymmetricMatrixForCrossProduct(const Vector3f& vector);

        /// Overloaded operator for addition
        friend Matrix3x3 operator+(const Matrix3x3& matrix1, const Matrix3x3& matrix2);

        /// Overloaded operator for substraction
        friend Matrix3x3 operator-(const Matrix3x3& matrix1, const Matrix3x3& matrix2);

        /// Overloaded operator for the negative of the matrix
        friend Matrix3x3 operator-(const Matrix3x3& matrix);

        /// Overloaded operator for multiplication with a number
        friend Matrix3x3 operator*(Type nb, const Matrix3x3& matrix);

        /// Overloaded operator for multiplication with a matrix
        friend Matrix3x3 operator*(const Matrix3x3& matrix, Type nb);

        /// Overloaded operator for matrix multiplication
        friend Matrix3x3 operator*(const Matrix3x3& matrix1, const Matrix3x3& matrix2);

        /// Overloaded operator for multiplication with a vector
        friend Vector3f operator*(const Matrix3x3& matrix, const Vector3f& vector);

        /// Overloaded operator for equality condition
        bool operator==(const Matrix3x3& matrix) const;

        /// Overloaded operator for the is different condition
        bool operator!= (const Matrix3x3& matrix) const;

        /// Overloaded operator for addition with assignment
        Matrix3x3& operator+=(const Matrix3x3& matrix);

        /// Overloaded operator for substraction with assignment
        Matrix3x3& operator-=(const Matrix3x3& matrix);

        /// Overloaded operator for multiplication with a number with assignment
        Matrix3x3& operator*=(Type nb);

        /// Overloaded operator to read element of the matrix.
        const Vector3<Type>& operator[](int row) const;

        /// Overloaded operator to read/write element of the matrix.
        Vector3<Type> operator[](int row);

        /// Return the string representation
        std::string to_string() const;
};

// Constructor of the class Matrix3x3
template <typename Type>
FORCEINLINE Matrix3x3<Type>::Matrix3x3() {
    // Initialize all values in the matrix to zero
    setAllValues(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

// Constructor
template <typename Type>
FORCEINLINE Matrix3x3<Type>::Matrix3x3(Type value) {
    setAllValues(value, value, value, value, value, value, value, value, value);
}

// Constructor with arguments
template <typename Type>
FORCEINLINE Matrix3x3<Type>::Matrix3x3(Type a1, Type a2, Type a3,
    Type b1, Type b2, Type b3,
    Type c1, Type c2, Type c3) {
    // Initialize the matrix with the values
    setAllValues(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

// Method to set all the values in the matrix
template <typename Type>
FORCEINLINE void Matrix3x3<Type>::setAllValues(Type a1, Type a2, Type a3,
    Type b1, Type b2, Type b3,
    Type c1, Type c2, Type c3) {
    mRows[0][0] = a1; mRows[0][1] = a2; mRows[0][2] = a3;
    mRows[1][0] = b1; mRows[1][1] = b2; mRows[1][2] = b3;
    mRows[2][0] = c1; mRows[2][1] = c2; mRows[2][2] = c3;
}

// Set the matrix to zero
template <typename Type>
FORCEINLINE void Matrix3x3<Type>::setToZero() {
    mRows[0].setToZero();
    mRows[1].setToZero();
    mRows[2].setToZero();
}

// Return a column
template <typename Type>
FORCEINLINE Vector3<Type> Matrix3x3<Type>::getColumn(int i) const {
    assert(i>= 0 && i<3);
    return Vector3<Type>(mRows[0][i], mRows[1][i], mRows[2][i]);
}

// Return a row
template <typename Type>
FORCEINLINE Vector3<Type> Matrix3x3<Type>::getRow(int i) const {
    assert(i>= 0 && i<3);
    return mRows[i];
}

// Return the transpose matrix
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::getTranspose() const {

    // Return the transpose matrix
    return Matrix3x3(mRows[0][0], mRows[1][0], mRows[2][0],
                     mRows[0][1], mRows[1][1], mRows[2][1],
                     mRows[0][2], mRows[1][2], mRows[2][2]);
}

// Return the determinant of the matrix
template <typename Type>
FORCEINLINE Type Matrix3x3<Type>::getDeterminant() const {

    // Compute and return the determinant of the matrix
    return (mRows[0][0]*(mRows[1][1]*mRows[2][2]-mRows[2][1]*mRows[1][2]) -
            mRows[0][1]*(mRows[1][0]*mRows[2][2]-mRows[2][0]*mRows[1][2]) +
            mRows[0][2]*(mRows[1][0]*mRows[2][1]-mRows[2][0]*mRows[1][1]));
}

// Return the trace of the matrix
template <typename Type>
FORCEINLINE Type Matrix3x3<Type>::getTrace() const {

    // Compute and return the trace
    return (mRows[0][0] + mRows[1][1] + mRows[2][2]);
}

// Set the matrix to the identity matrix
template <typename Type>
FORCEINLINE void Matrix3x3<Type>::setToIdentity() {
    mRows[0][0] = 1.0; mRows[0][1] = 0.0; mRows[0][2] = 0.0;
    mRows[1][0] = 0.0; mRows[1][1] = 1.0; mRows[1][2] = 0.0;
    mRows[2][0] = 0.0; mRows[2][1] = 0.0; mRows[2][2] = 1.0;
}

// Return the 3x3 identity matrix
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::identity() {
    return Matrix3x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

// Return the 3x3 zero matrix.
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::zero() {
    return Matrix3x3(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

// Return the inverse matrix
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::getInverse() const {

    return getInverse(getDeterminant());
}

template<typename Type>
Matrix3x3<Type> Matrix3x3<Type>::getInverse(Type determinant) const {

    // Check if the determinant is equal to zero
    assert(determinant != Type(0.0));

    float invDeterminant = Type(1.0) / determinant;

    Matrix3x3 tempMatrix((mRows[1][1] * mRows[2][2] - mRows[2][1] * mRows[1][2]),
        -(mRows[0][1] * mRows[2][2] - mRows[2][1] * mRows[0][2]),
        (mRows[0][1] * mRows[1][2] - mRows[0][2] * mRows[1][1]),
        -(mRows[1][0] * mRows[2][2] - mRows[2][0] * mRows[1][2]),
        (mRows[0][0] * mRows[2][2] - mRows[2][0] * mRows[0][2]),
        -(mRows[0][0] * mRows[1][2] - mRows[1][0] * mRows[0][2]),
        (mRows[1][0] * mRows[2][1] - mRows[2][0] * mRows[1][1]),
        -(mRows[0][0] * mRows[2][1] - mRows[2][0] * mRows[0][1]),
        (mRows[0][0] * mRows[1][1] - mRows[0][1] * mRows[1][0]));

    // Return the inverse matrix
    return (invDeterminant * tempMatrix);
}

// Return a skew-symmetric matrix using a given vector that can be used
// to compute cross product with another vector using matrix multiplication
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::computeSkewSymmetricMatrixForCrossProduct(const Vector3f& vector) {
    return Matrix3x3(0, -vector.z, vector.y, vector.z, 0, -vector.x, -vector.y, vector.x, 0);
}

// Return the matrix with absolute values
template <typename Type>
FORCEINLINE Matrix3x3<Type> Matrix3x3<Type>::getAbsoluteMatrix() const {
    return Matrix3x3(std::abs(mRows[0][0]), std::abs(mRows[0][1]), std::abs(mRows[0][2]),
                     std::abs(mRows[1][0]), std::abs(mRows[1][1]), std::abs(mRows[1][2]),
                     std::abs(mRows[2][0]), std::abs(mRows[2][1]), std::abs(mRows[2][2]));
}

// Overloaded operator for addition
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator+(const Matrix3x3<Type>& matrix1, const Matrix3x3<Type>& matrix2) {
    return Matrix3x3(matrix1.mRows[0][0] + matrix2.mRows[0][0], matrix1.mRows[0][1] +
                     matrix2.mRows[0][1], matrix1.mRows[0][2] + matrix2.mRows[0][2],
                     matrix1.mRows[1][0] + matrix2.mRows[1][0], matrix1.mRows[1][1] +
                     matrix2.mRows[1][1], matrix1.mRows[1][2] + matrix2.mRows[1][2],
                     matrix1.mRows[2][0] + matrix2.mRows[2][0], matrix1.mRows[2][1] +
                     matrix2.mRows[2][1], matrix1.mRows[2][2] + matrix2.mRows[2][2]);
}

// Overloaded operator for substraction
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator-(const Matrix3x3<Type>& matrix1, const Matrix3x3<Type>& matrix2) {
    return Matrix3x3(matrix1.mRows[0][0] - matrix2.mRows[0][0], matrix1.mRows[0][1] -
                     matrix2.mRows[0][1], matrix1.mRows[0][2] - matrix2.mRows[0][2],
                     matrix1.mRows[1][0] - matrix2.mRows[1][0], matrix1.mRows[1][1] -
                     matrix2.mRows[1][1], matrix1.mRows[1][2] - matrix2.mRows[1][2],
                     matrix1.mRows[2][0] - matrix2.mRows[2][0], matrix1.mRows[2][1] -
                     matrix2.mRows[2][1], matrix1.mRows[2][2] - matrix2.mRows[2][2]);
}

// Overloaded operator for the negative of the matrix
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator-(const Matrix3x3<Type>& matrix) {
    return Matrix3x3<Type>(-matrix.mRows[0][0], -matrix.mRows[0][1], -matrix.mRows[0][2],
                     -matrix.mRows[1][0], -matrix.mRows[1][1], -matrix.mRows[1][2],
                     -matrix.mRows[2][0], -matrix.mRows[2][1], -matrix.mRows[2][2]);
}

// Overloaded operator for multiplication with a number
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator*(Type nb, const Matrix3x3<Type>& matrix) {
    return Matrix3x3<Type>(matrix.mRows[0][0] * nb, matrix.mRows[0][1] * nb, matrix.mRows[0][2] * nb,
                     matrix.mRows[1][0] * nb, matrix.mRows[1][1] * nb, matrix.mRows[1][2] * nb,
                     matrix.mRows[2][0] * nb, matrix.mRows[2][1] * nb, matrix.mRows[2][2] * nb);
}

// Overloaded operator for multiplication with a matrix
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator*(const Matrix3x3<Type>& matrix, Type nb) {
    return nb * matrix;
}

// Overloaded operator for matrix multiplication
template <typename Type>
FORCEINLINE Matrix3x3<Type> operator*(const Matrix3x3<Type>& matrix1, const Matrix3x3<Type>& matrix2) {
    return Matrix3x3<Type>(matrix1.mRows[0][0]*matrix2.mRows[0][0] + matrix1.mRows[0][1] *
                     matrix2.mRows[1][0] + matrix1.mRows[0][2]*matrix2.mRows[2][0],
                     matrix1.mRows[0][0]*matrix2.mRows[0][1] + matrix1.mRows[0][1] *
                     matrix2.mRows[1][1] + matrix1.mRows[0][2]*matrix2.mRows[2][1],
                     matrix1.mRows[0][0]*matrix2.mRows[0][2] + matrix1.mRows[0][1] *
                     matrix2.mRows[1][2] + matrix1.mRows[0][2]*matrix2.mRows[2][2],
                     matrix1.mRows[1][0]*matrix2.mRows[0][0] + matrix1.mRows[1][1] *
                     matrix2.mRows[1][0] + matrix1.mRows[1][2]*matrix2.mRows[2][0],
                     matrix1.mRows[1][0]*matrix2.mRows[0][1] + matrix1.mRows[1][1] *
                     matrix2.mRows[1][1] + matrix1.mRows[1][2]*matrix2.mRows[2][1],
                     matrix1.mRows[1][0]*matrix2.mRows[0][2] + matrix1.mRows[1][1] *
                     matrix2.mRows[1][2] + matrix1.mRows[1][2]*matrix2.mRows[2][2],
                     matrix1.mRows[2][0]*matrix2.mRows[0][0] + matrix1.mRows[2][1] *
                     matrix2.mRows[1][0] + matrix1.mRows[2][2]*matrix2.mRows[2][0],
                     matrix1.mRows[2][0]*matrix2.mRows[0][1] + matrix1.mRows[2][1] *
                     matrix2.mRows[1][1] + matrix1.mRows[2][2]*matrix2.mRows[2][1],
                     matrix1.mRows[2][0]*matrix2.mRows[0][2] + matrix1.mRows[2][1] *
                     matrix2.mRows[1][2] + matrix1.mRows[2][2]*matrix2.mRows[2][2]);
}

// Overloaded operator for multiplication with a vector
template <typename Type>
FORCEINLINE Vector3<Type> operator*(const Matrix3x3<Type>& matrix, const Vector3<Type>& vector) {
    return Vector3<Type>(matrix.mRows[0][0]*vector.x + matrix.mRows[0][1]*vector.y +
                   matrix.mRows[0][2]*vector.z,
                   matrix.mRows[1][0]*vector.x + matrix.mRows[1][1]*vector.y +
                   matrix.mRows[1][2]*vector.z,
                   matrix.mRows[2][0]*vector.x + matrix.mRows[2][1]*vector.y +
                   matrix.mRows[2][2]*vector.z);
}

// Overloaded operator for equality condition
template <typename Type>
FORCEINLINE bool Matrix3x3<Type>::operator==(const Matrix3x3<Type>& matrix) const {
    return (mRows[0][0] == matrix.mRows[0][0] && mRows[0][1] == matrix.mRows[0][1] &&
            mRows[0][2] == matrix.mRows[0][2] &&
            mRows[1][0] == matrix.mRows[1][0] && mRows[1][1] == matrix.mRows[1][1] &&
            mRows[1][2] == matrix.mRows[1][2] &&
            mRows[2][0] == matrix.mRows[2][0] && mRows[2][1] == matrix.mRows[2][1] &&
            mRows[2][2] == matrix.mRows[2][2]);
}

// Overloaded operator for the is different condition
template <typename Type>
FORCEINLINE bool Matrix3x3<Type>::operator!= (const Matrix3x3<Type>& matrix) const {
    return !(*this == matrix);
}

// Overloaded operator for addition with assignment
template <typename Type>
FORCEINLINE Matrix3x3<Type>& Matrix3x3<Type>::operator+=(const Matrix3x3<Type>& matrix) {
   mRows[0][0] += matrix.mRows[0][0]; mRows[0][1] += matrix.mRows[0][1];
   mRows[0][2] += matrix.mRows[0][2]; mRows[1][0] += matrix.mRows[1][0];
   mRows[1][1] += matrix.mRows[1][1]; mRows[1][2] += matrix.mRows[1][2];
   mRows[2][0] += matrix.mRows[2][0]; mRows[2][1] += matrix.mRows[2][1];
   mRows[2][2] += matrix.mRows[2][2];
   return *this;
}

// Overloaded operator for substraction with assignment
template <typename Type>
FORCEINLINE Matrix3x3<Type>& Matrix3x3<Type>::operator-=(const Matrix3x3<Type>& matrix) {
   mRows[0][0] -= matrix.mRows[0][0]; mRows[0][1] -= matrix.mRows[0][1];
   mRows[0][2] -= matrix.mRows[0][2]; mRows[1][0] -= matrix.mRows[1][0];
   mRows[1][1] -= matrix.mRows[1][1]; mRows[1][2] -= matrix.mRows[1][2];
   mRows[2][0] -= matrix.mRows[2][0]; mRows[2][1] -= matrix.mRows[2][1];
   mRows[2][2] -= matrix.mRows[2][2];
   return *this;
}

// Overloaded operator for multiplication with a number with assignment
template <typename Type>
FORCEINLINE Matrix3x3<Type>& Matrix3x3<Type>::operator*=(Type nb) {
   mRows[0][0] *= nb; mRows[0][1] *= nb; mRows[0][2] *= nb;
   mRows[1][0] *= nb; mRows[1][1] *= nb; mRows[1][2] *= nb;
   mRows[2][0] *= nb; mRows[2][1] *= nb; mRows[2][2] *= nb;
   return *this;
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE const Vector3<Type>& Matrix3x3<Type>::operator[](int row) const {
    return mRows[row];
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE Vector3<Type> Matrix3x3<Type>::operator[](int row) {
    return mRows[row];
}

// Get the string representation
template <typename Type>
FORCEINLINE std::string Matrix3x3<Type>::to_string() const {
    return "Matrix3x3(" + std::to_string(mRows[0][0]) + "," + std::to_string(mRows[0][1]) + "," + std::to_string(mRows[0][2]) + "," +
           std::to_string(mRows[1][0]) + "," + std::to_string(mRows[1][1]) + "," + std::to_string(mRows[1][2]) + "," +
           std::to_string(mRows[2][0]) + "," + std::to_string(mRows[2][1]) + "," + std::to_string(mRows[2][2]) + ")";
}

using Matrix3x3c = Matrix3x3<char>;
using Matrix3x3us = Matrix3x3<unsigned short>;
using Matrix3x3s = Matrix3x3<short>;
using Matrix3x3ui = Matrix3x3<unsigned int>;
using Matrix3x3i = Matrix3x3<int>;
using Matrix3x3f = Matrix3x3<float>;
using Matrix3x3d = Matrix3x3<double>;

#endif
