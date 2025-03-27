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


#ifndef MATRIX4X4_H
#define MATRIX4X4_H

// Libraries
#include <cassert>
//#include <reactphysics3d/mathematics/Vector4.h>
//#include "../Utils/CoreMinimal.h"
#include "Vector4.h"

template <typename Type>
class Matrix4x4 {

private:

    // -------------------- Attributes -------------------- //

    /// Rows of the matrix;
    Vector4<Type> mRows[4];

public:

    // -------------------- Methods -------------------- //

    /// Constructor
    Matrix4x4();

    /// Constructor
    Matrix4x4(Type value);

    /// Constructor
    Matrix4x4(Type a1, Type a2, Type a3, Type a4, Type b1, Type b2, Type b3, Type b4,
        Type c1, Type c2, Type c3, Type c4, Type d1, Type d2, Type d3, Type d4);

    /// Set all the values in the matrix
    void setAllValues(Type a1, Type a2, Type a3, Type a4, Type b1, Type b2, Type b3, Type b4,
        Type c1, Type c2, Type c3, Type c4, Type d1, Type d2, Type d3, Type d4);

    /// Set the matrix to zero
    void setToZero();

    /// Return a column
    Vector4<Type> getColumn(int i) const;

    /// Return a row
    Vector4<Type> getRow(int i) const;

    /// Return the transpose matrix
    Matrix4x4 getTranspose() const;

    /// Return the determinant of the matrix
    Type getDeterminant() const;

    /// Return the trace of the matrix
    Type getTrace() const;

    /// Return the inverse matrix
    Matrix4x4 getInverse() const;

    /// Return the inverse matrix
    Matrix4x4 getInverse(Type determinant) const;

    /// Return the matrix with absolute values
    Matrix4x4 getAbsoluteMatrix() const;

    /// Set the matrix to the identity matrix
    void setToIdentity();

    /// Return the 3x3 identity matrix
    static Matrix4x4 identity();

    /// Return the 3x3 zero matrix
    static Matrix4x4 zero();

    /// Return a skew-symmetric matrix using a given vector that can be used
    /// to compute cross product with another vector using matrix multiplication
    static Matrix4x4 computeSkewSymmetricMatrixForCrossProduct(const Vector4f& vector);

    /// Overloaded operator for addition
    friend Matrix4x4 operator+(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

    /// Overloaded operator for substraction
    friend Matrix4x4 operator-(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

    /// Overloaded operator for the negative of the matrix
    friend Matrix4x4 operator-(const Matrix4x4& matrix);

    /// Overloaded operator for multiplication with a number
    friend Matrix4x4 operator*(Type nb, const Matrix4x4& matrix);

    /// Overloaded operator for multiplication with a matrix
    friend Matrix4x4 operator*(const Matrix4x4& matrix, Type nb);

    /// Overloaded operator for matrix multiplication
    friend Matrix4x4 operator*(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

    /// Overloaded operator for multiplication with a vector
    friend Vector4f operator*(const Matrix4x4& matrix, const Vector4f& vector);

    /// Overloaded operator for equality condition
    bool operator==(const Matrix4x4& matrix) const;

    /// Overloaded operator for the is different condition
    bool operator!= (const Matrix4x4& matrix) const;

    /// Overloaded operator for addition with assignment
    Matrix4x4& operator+=(const Matrix4x4& matrix);

    /// Overloaded operator for substraction with assignment
    Matrix4x4& operator-=(const Matrix4x4& matrix);

    /// Overloaded operator for multiplication with a number with assignment
    Matrix4x4& operator*=(Type nb);

    /// Overloaded operator to read element of the matrix.
    const Vector4<Type>& operator[](int row) const;

    /// Overloaded operator to read/write element of the matrix.
    Vector4<Type> operator[](int row);

    /// Return the string representation
    std::string to_string() const;
};

// Constructor of the class Matrix4x4
template <typename Type>
FORCEINLINE Matrix4x4<Type>::Matrix4x4() {
    // Initialize all values in the matrix to zero
    setAllValues(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

// Constructor
template <typename Type>
FORCEINLINE Matrix4x4<Type>::Matrix4x4(Type value) {
    setAllValues(value, value, value, value, value, value, value, value, value, value, value, value, value, value, value, value);
}

// Constructor with arguments
template <typename Type>
FORCEINLINE Matrix4x4<Type>::Matrix4x4(Type a1, Type a2, Type a3, Type a4, Type b1, Type b2, Type b3, Type b4,
    Type c1, Type c2, Type c3, Type c4, Type d1, Type d2, Type d3, Type d4) {
    // Initialize the matrix with the values
    setAllValues(a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4);
}

// Method to set all the values in the matrix
template <typename Type>
FORCEINLINE void Matrix4x4<Type>::setAllValues(Type a1, Type a2, Type a3, Type a4, Type b1, Type b2, Type b3, Type b4,
    Type c1, Type c2, Type c3, Type c4, Type d1, Type d2, Type d3, Type d4) {
    mRows[0][0] = a1; mRows[0][1] = a2; mRows[0][2] = a3; mRows[0][3] = a4;
    mRows[1][0] = b1; mRows[1][1] = b2; mRows[1][2] = b3; mRows[1][3] = b4;
    mRows[2][0] = c1; mRows[2][1] = c2; mRows[2][2] = c3; mRows[2][3] = c4;
    mRows[3][0] = d1; mRows[3][1] = d2; mRows[3][2] = d3; mRows[3][3] = d4;
}

// Set the matrix to zero
template <typename Type>
FORCEINLINE void Matrix4x4<Type>::setToZero() {
    mRows[0].setToZero();
    mRows[1].setToZero();
    mRows[2].setToZero();
    mRows[4].setToZero();
}

// Return a column
template <typename Type>
FORCEINLINE Vector4<Type> Matrix4x4<Type>::getColumn(int i) const {
    assert(i >= 0 && i < 4);
    return Vector4<Type>(mRows[0][i], mRows[1][i], mRows[2][i], mRows[3][i]);
}

// Return a row
template <typename Type>
FORCEINLINE Vector4<Type> Matrix4x4<Type>::getRow(int i) const {
    assert(i >= 0 && i < 4);
    return mRows[i];
}

// Return the transpose matrix
template <typename Type>
FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::getTranspose() const {

    // Return the transpose matrix
    return Matrix4x4(mRows[0][0], mRows[1][0], mRows[2][0], mRows[3][0],
        mRows[0][1], mRows[1][1], mRows[2][1], mRows[3][1],
        mRows[0][2], mRows[1][2], mRows[2][2], mRows[3][2],
        mRows[0][3], mRows[1][3], mRows[2][3], mRows[3][3]
    );
}

// Return the determinant of the matrix
template <typename Type>
FORCEINLINE Type Matrix4x4<Type>::getDeterminant() const {

    // Compute and return the determinant of the matrix
    return (mRows[0][0] * (mRows[1][1] * mRows[2][2] - mRows[2][1] * mRows[1][2]) -
        mRows[0][1] * (mRows[1][0] * mRows[2][2] - mRows[2][0] * mRows[1][2]) +
        mRows[0][2] * (mRows[1][0] * mRows[2][1] - mRows[2][0] * mRows[1][1]));
}

// Return the trace of the matrix
template <typename Type>
FORCEINLINE Type Matrix4x4<Type>::getTrace() const {

    // Compute and return the trace
    return (mRows[0][0] + mRows[1][1] + mRows[2][2], mRows[3][3]);
}

// Set the matrix to the identity matrix
template <typename Type>
FORCEINLINE void Matrix4x4<Type>::setToIdentity() {
    mRows[0][0] = 1.0; mRows[0][1] = 0.0; mRows[0][2] = 0.0; mRows[0][3] = 0.0;
    mRows[1][0] = 0.0; mRows[1][1] = 1.0; mRows[1][2] = 0.0; mRows[1][3] = 0.0;
    mRows[2][0] = 0.0; mRows[2][1] = 0.0; mRows[2][2] = 1.0; mRows[2][3] = 0.0;
    mRows[2][0] = 0.0; mRows[2][1] = 0.0; mRows[2][2] = 0.0; mRows[3][3] = 1.0;
}

// Return the 3x3 identity matrix
template <typename Type>
FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::identity() {
    return Matrix4x4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

// Return the 3x3 zero matrix.
template <typename Type>
FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::zero() {
    return Matrix4x4(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

// Return the inverse matrix
template <typename Type>
FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::getInverse() const {

    return getInverse(getDeterminant());
}

//template<typename Type>
//Matrix4x4<Type> Matrix4x4<Type>::getInverse(Type determinant) const {
//
//    // Check if the determinant is equal to zero
//    assert(determinant != Type(0.0));
//
//    float invDeterminant = Type(1.0) / determinant;
//
//    Matrix4x4 tempMatrix((mRows[1][1] * mRows[2][2] - mRows[2][1] * mRows[1][2]),
//        -(mRows[0][1] * mRows[2][2] - mRows[2][1] * mRows[0][2]),
//        (mRows[0][1] * mRows[1][2] - mRows[0][2] * mRows[1][1]),
//        -(mRows[1][0] * mRows[2][2] - mRows[2][0] * mRows[1][2]),
//        (mRows[0][0] * mRows[2][2] - mRows[2][0] * mRows[0][2]),
//        -(mRows[0][0] * mRows[1][2] - mRows[1][0] * mRows[0][2]),
//        (mRows[1][0] * mRows[2][1] - mRows[2][0] * mRows[1][1]),
//        -(mRows[0][0] * mRows[2][1] - mRows[2][0] * mRows[0][1]),
//        (mRows[0][0] * mRows[1][1] - mRows[0][1] * mRows[1][0]));
//
//    // Return the inverse matrix
//    return (invDeterminant * tempMatrix);
//}

// Return a skew-symmetric matrix using a given vector that can be used
// to compute cross product with another vector using matrix multiplication
//template <typename Type>
//FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::computeSkewSymmetricMatrixForCrossProduct(const Vector4f& vector) {
//    return Matrix4x4(0, -vector.z, vector.y, vector.z, 0, -vector.x, -vector.y, vector.x, 0);
//}

// Return the matrix with absolute values
template <typename Type>
FORCEINLINE Matrix4x4<Type> Matrix4x4<Type>::getAbsoluteMatrix() const {
    return Matrix4x4(std::abs(mRows[0][0]), std::abs(mRows[0][1]), std::abs(mRows[0][2]), std::abs(mRows[0][3]),
        std::abs(mRows[1][0]), std::abs(mRows[1][1]), std::abs(mRows[1][2]), std::abs(mRows[1][3]),
        std::abs(mRows[2][0]), std::abs(mRows[2][1]), std::abs(mRows[2][2]), std::abs(mRows[2][3]),
        std::abs(mRows[3][0]), std::abs(mRows[3][1]), std::abs(mRows[3][2]), std::abs(mRows[3][3])
    );
}

// Overloaded operator for addition
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator+(const Matrix4x4<Type>& matrix1, const Matrix4x4<Type>& matrix2) {
    return Matrix4x4(matrix1.mRows[0][0] + matrix2.mRows[0][0],
        matrix1.mRows[0][1] + matrix2.mRows[0][1],
        matrix1.mRows[0][2] + matrix2.mRows[0][2],
        matrix1.mRows[0][3] + matrix2.mRows[0][3],
        matrix1.mRows[1][0] + matrix2.mRows[1][0],
        matrix1.mRows[1][1] + matrix2.mRows[1][1],
        matrix1.mRows[1][2] + matrix2.mRows[1][2],
        matrix1.mRows[1][3] + matrix2.mRows[1][3],
        matrix1.mRows[2][0] + matrix2.mRows[2][0],
        matrix1.mRows[2][1] + matrix2.mRows[2][1],
        matrix1.mRows[2][2] + matrix2.mRows[2][2],
        matrix1.mRows[2][3] + matrix2.mRows[2][3],
        matrix1.mRows[3][0] + matrix2.mRows[3][0],
        matrix1.mRows[3][1] + matrix2.mRows[3][1],
        matrix1.mRows[3][2] + matrix2.mRows[3][2],
        matrix1.mRows[3][3] + matrix2.mRows[3][3]

    );
}

// Overloaded operator for substraction
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator-(const Matrix4x4<Type>& matrix1, const Matrix4x4<Type>& matrix2) {
    return Matrix4x4(matrix1.mRows[0][0] - matrix2.mRows[0][0],
        matrix1.mRows[0][1] - matrix2.mRows[0][1],
        matrix1.mRows[0][2] - matrix2.mRows[0][2],
        matrix1.mRows[0][3] - matrix2.mRows[0][3],
        matrix1.mRows[1][0] - matrix2.mRows[1][0],
        matrix1.mRows[1][1] - matrix2.mRows[1][1],
        matrix1.mRows[1][2] - matrix2.mRows[1][2],
        matrix1.mRows[1][3] - matrix2.mRows[1][3],
        matrix1.mRows[2][0] - matrix2.mRows[2][0],
        matrix1.mRows[2][1] - matrix2.mRows[2][1],
        matrix1.mRows[2][2] - matrix2.mRows[2][2],
        matrix1.mRows[2][3] - matrix2.mRows[2][3],
        matrix1.mRows[3][0] - matrix2.mRows[3][0],
        matrix1.mRows[3][1] - matrix2.mRows[3][1],
        matrix1.mRows[3][2] - matrix2.mRows[3][2],
        matrix1.mRows[3][3] - matrix2.mRows[3][3]);
}

// Overloaded operator for the negative of the matrix
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator-(const Matrix4x4<Type>& matrix) {
    return Matrix4x4<Type>(-matrix.mRows[0][0],
        -matrix.mRows[0][1],
        -matrix.mRows[0][2],
        -matrix.mRows[0][3],
        -matrix.mRows[1][0],
        -matrix.mRows[1][1],
        -matrix.mRows[1][2],
        -matrix.mRows[1][3],
        -matrix.mRows[2][0],
        -matrix.mRows[2][1],
        -matrix.mRows[2][2],
        -matrix.mRows[2][3],
        -matrix.mRows[3][0],
        -matrix.mRows[3][1],
        -matrix.mRows[3][2],
        -matrix.mRows[3][3]);
}

// Overloaded operator for multiplication with a number
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator*(Type nb, const Matrix4x4<Type>& matrix) {
    return Matrix4x4<Type>(
        matrix.mRows[0][0] * nb,
        matrix.mRows[0][1] * nb,
        matrix.mRows[0][2] * nb,
        matrix.mRows[0][3] * nb,
        matrix.mRows[1][0] * nb,
        matrix.mRows[1][1] * nb,
        matrix.mRows[1][2] * nb,
        matrix.mRows[1][3] * nb,
        matrix.mRows[2][0] * nb,
        matrix.mRows[2][1] * nb,
        matrix.mRows[2][2] * nb,
        matrix.mRows[2][3] * nb,
        matrix.mRows[3][0] * nb,
        matrix.mRows[3][1] * nb,
        matrix.mRows[3][2] * nb,
        matrix.mRows[3][3] * nb);
}

// Overloaded operator for multiplication with a matrix
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator*(const Matrix4x4<Type>& matrix, Type nb) {
    return nb * matrix;
}

// Overloaded operator for matrix multiplication
template <typename Type>
FORCEINLINE Matrix4x4<Type> operator*(const Matrix4x4<Type>& matrix1, const Matrix4x4<Type>& matrix2)
{
    return Matrix4x4<Type>(

        matrix1.mRows[0][0] * matrix2.mRows[0][0] +
        matrix1.mRows[0][1] * matrix2.mRows[1][0] +
        matrix1.mRows[0][2] * matrix2.mRows[2][0] +
        matrix1.mRows[0][3] * matrix2.mRows[3][0],

        matrix1.mRows[0][0] * matrix2.mRows[0][1] +
        matrix1.mRows[0][1] * matrix2.mRows[1][1] +
        matrix1.mRows[0][2] * matrix2.mRows[2][1] +
        matrix1.mRows[0][3] * matrix2.mRows[3][1],

        matrix1.mRows[0][0] * matrix2.mRows[0][2] +
        matrix1.mRows[0][1] * matrix2.mRows[1][2] +
        matrix1.mRows[0][2] * matrix2.mRows[2][2] +
        matrix1.mRows[0][3] * matrix2.mRows[3][2],

        matrix1.mRows[0][0] * matrix2.mRows[0][3] +
        matrix1.mRows[0][1] * matrix2.mRows[1][3] +
        matrix1.mRows[0][2] * matrix2.mRows[2][3] +
        matrix1.mRows[0][3] * matrix2.mRows[3][3],


        matrix1.mRows[1][0] * matrix2.mRows[0][0] +
        matrix1.mRows[1][1] * matrix2.mRows[1][0] +
        matrix1.mRows[1][2] * matrix2.mRows[2][0] +
        matrix1.mRows[1][3] * matrix2.mRows[3][0],

        matrix1.mRows[1][0] * matrix2.mRows[0][1] +
        matrix1.mRows[1][1] * matrix2.mRows[1][1] +
        matrix1.mRows[1][2] * matrix2.mRows[2][1] +
        matrix1.mRows[1][3] * matrix2.mRows[3][1],


        matrix1.mRows[1][0] * matrix2.mRows[0][2] +
        matrix1.mRows[1][1] * matrix2.mRows[1][2] +
        matrix1.mRows[1][2] * matrix2.mRows[2][2] +
        matrix1.mRows[1][3] * matrix2.mRows[3][2],

        matrix1.mRows[1][0] * matrix2.mRows[0][3] +
        matrix1.mRows[1][1] * matrix2.mRows[1][3] +
        matrix1.mRows[1][2] * matrix2.mRows[2][3] +
        matrix1.mRows[1][3] * matrix2.mRows[3][3],


        matrix1.mRows[2][0] * matrix2.mRows[0][0] +
        matrix1.mRows[2][1] * matrix2.mRows[1][0] +
        matrix1.mRows[2][2] * matrix2.mRows[2][0] +
        matrix1.mRows[2][3] * matrix2.mRows[3][0],

        matrix1.mRows[2][0] * matrix2.mRows[0][1] +
        matrix1.mRows[2][1] * matrix2.mRows[1][1] +
        matrix1.mRows[2][2] * matrix2.mRows[2][1] +
        matrix1.mRows[2][3] * matrix2.mRows[3][1],


        matrix1.mRows[2][0] * matrix2.mRows[0][2] +
        matrix1.mRows[2][1] * matrix2.mRows[1][2] +
        matrix1.mRows[2][2] * matrix2.mRows[2][2] +
        matrix1.mRows[2][3] * matrix2.mRows[3][2],

        matrix1.mRows[2][0] * matrix2.mRows[0][3] +
        matrix1.mRows[2][1] * matrix2.mRows[1][3] +
        matrix1.mRows[2][2] * matrix2.mRows[2][3] +
        matrix1.mRows[2][3] * matrix2.mRows[3][3],

        matrix1.mRows[3][0] * matrix2.mRows[0][0] +
        matrix1.mRows[3][1] * matrix2.mRows[1][0] +
        matrix1.mRows[3][2] * matrix2.mRows[2][0] +
        matrix1.mRows[3][3] * matrix2.mRows[3][0],

        matrix1.mRows[3][0] * matrix2.mRows[0][1] +
        matrix1.mRows[3][1] * matrix2.mRows[1][1] +
        matrix1.mRows[3][2] * matrix2.mRows[2][1] +
        matrix1.mRows[3][3] * matrix2.mRows[3][1],

        matrix1.mRows[3][0] * matrix2.mRows[0][2] +
        matrix1.mRows[3][1] * matrix2.mRows[1][2] +
        matrix1.mRows[3][2] * matrix2.mRows[2][2] +
        matrix1.mRows[3][3] * matrix2.mRows[3][2],

        matrix1.mRows[3][0] * matrix2.mRows[0][3] +
        matrix1.mRows[3][1] * matrix2.mRows[1][3] +
        matrix1.mRows[3][2] * matrix2.mRows[2][3] +
        matrix1.mRows[3][3] * matrix2.mRows[3][3]);


}

// Overloaded operator for multiplication with a vector
template <typename Type>
FORCEINLINE Vector4<Type> operator*(const Matrix4x4<Type>& matrix, const Vector4<Type>& vector) {
    return Vector4<Type>(
        matrix.mRows[0][0] * vector.x +
        matrix.mRows[0][1] * vector.y +
        matrix.mRows[0][2] * vector.z +
        matrix.mRows[0][3] * vector.w,

        matrix.mRows[1][0] * vector.x +
        matrix.mRows[1][1] * vector.y +
        matrix.mRows[1][2] * vector.z +
        matrix.mRows[1][3] * vector.w,

        matrix.mRows[2][0] * vector.x +
        matrix.mRows[2][1] * vector.y +
        matrix.mRows[2][2] * vector.z +
        matrix.mRows[2][3] * vector.w,

        matrix.mRows[3][0] * vector.x +
        matrix.mRows[3][1] * vector.y +
        matrix.mRows[3][2] * vector.z +
        matrix.mRows[3][3] * vector.w);


}

// Overloaded operator for equality condition
template <typename Type>
FORCEINLINE bool Matrix4x4<Type>::operator==(const Matrix4x4<Type>& matrix) const {
    return (
        mRows[0][0] == matrix.mRows[0][0] &&
        mRows[0][1] == matrix.mRows[0][1] &&
        mRows[0][2] == matrix.mRows[0][2] &&
        mRows[0][3] == matrix.mRows[0][3] &&
        mRows[1][0] == matrix.mRows[1][0] &&
        mRows[1][1] == matrix.mRows[1][1] &&
        mRows[1][2] == matrix.mRows[1][2] &&
        mRows[1][3] == matrix.mRows[1][3] &&
        mRows[2][0] == matrix.mRows[2][0] &&
        mRows[2][1] == matrix.mRows[2][1] &&
        mRows[2][2] == matrix.mRows[2][2] &&
        mRows[2][3] == matrix.mRows[2][3]
        );
}

// Overloaded operator for the is different condition
template <typename Type>
FORCEINLINE bool Matrix4x4<Type>::operator!= (const Matrix4x4<Type>& matrix) const {
    return !(*this == matrix);
}

// Overloaded operator for addition with assignment
template <typename Type>
FORCEINLINE Matrix4x4<Type>& Matrix4x4<Type>::operator+=(const Matrix4x4<Type>& matrix) {
    mRows[0][0] += matrix.mRows[0][0];
    mRows[0][1] += matrix.mRows[0][1];
    mRows[0][2] += matrix.mRows[0][2];
    mRows[0][3] += matrix.mRows[0][3];
    mRows[1][0] += matrix.mRows[1][0];
    mRows[1][1] += matrix.mRows[1][1];
    mRows[1][2] += matrix.mRows[1][2];
    mRows[1][3] += matrix.mRows[1][3];
    mRows[2][0] += matrix.mRows[2][0];
    mRows[2][1] += matrix.mRows[2][1];
    mRows[2][2] += matrix.mRows[2][2];
    mRows[2][3] += matrix.mRows[2][3];
    return *this;
}

// Overloaded operator for substraction with assignment
template <typename Type>
FORCEINLINE Matrix4x4<Type>& Matrix4x4<Type>::operator-=(const Matrix4x4<Type>& matrix) {
    mRows[0][0] -= matrix.mRows[0][0];
    mRows[0][1] -= matrix.mRows[0][1];
    mRows[0][2] -= matrix.mRows[0][2];
    mRows[0][3] -= matrix.mRows[0][3];
    mRows[1][0] -= matrix.mRows[1][0];
    mRows[1][1] -= matrix.mRows[1][1];
    mRows[1][3] -= matrix.mRows[1][3];
    mRows[2][0] -= matrix.mRows[2][0];
    mRows[2][1] -= matrix.mRows[2][1];
    mRows[2][2] -= matrix.mRows[2][2];
    mRows[2][3] -= matrix.mRows[2][3];
    return *this;
}

// Overloaded operator for multiplication with a number with assignment
template <typename Type>
FORCEINLINE Matrix4x4<Type>& Matrix4x4<Type>::operator*=(Type nb) {
    mRows[0][0] *= nb;
    mRows[0][1] *= nb;
    mRows[0][2] *= nb;
    mRows[0][3] *= nb;
    mRows[1][0] *= nb;
    mRows[1][1] *= nb;
    mRows[1][2] *= nb;
    mRows[1][3] *= nb;
    mRows[2][0] *= nb;
    mRows[2][1] *= nb;
    mRows[2][2] *= nb;
    mRows[2][3] *= nb;
    return *this;
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE const Vector4<Type>& Matrix4x4<Type>::operator[](int row) const {
    return mRows[row];
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE Vector4<Type> Matrix4x4<Type>::operator[](int row) {
    return mRows[row];
}

// Get the string representation
template <typename Type>
FORCEINLINE std::string Matrix4x4<Type>::to_string() const {
    return "Matrix4x4(" + std::to_string(mRows[0][0]) + "," + std::to_string(mRows[0][1]) + "," + std::to_string(mRows[0][2]) + "," + std::to_string(mRows[0][3]) + "," +
        std::to_string(mRows[1][0]) + "," + std::to_string(mRows[1][1]) + "," + std::to_string(mRows[1][2]) + "," + std::to_string(mRows[1][3]) + "," +
        std::to_string(mRows[2][0]) + "," + std::to_string(mRows[2][1]) + "," + std::to_string(mRows[2][2]) + std::to_string(mRows[2][3]) + "," +
        std::to_string(mRows[3][0]) + "," + std::to_string(mRows[3][1]) + "," + std::to_string(mRows[3][2]) + std::to_string(mRows[3][3]) + ")";
}

using Matrix4x4c = Matrix4x4<char>;
using Matrix4x4us = Matrix4x4<unsigned short>;
using Matrix4x4s = Matrix4x4<short>;
using Matrix4x4ui = Matrix4x4<unsigned int>;
using Matrix4x4i = Matrix4x4<int>;
using Matrix4x4f = Matrix4x4<float>;
using Matrix4x4d = Matrix4x4<double>;

#endif
