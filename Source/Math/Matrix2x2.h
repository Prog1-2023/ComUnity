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

#ifndef MATRIX2X2_H
#define MATRIX2X2_H

// Libraries
#include <cassert>
//#include <reactphysics3d/mathematics/Vector2.h>
#include "../Utils/CoreMinimal.h"
#include "Vector2.h"


template <typename Type>
class Matrix2x2 {

    private :

        // -------------------- Attributes -------------------- //

        /// Rows of the matrix;
        Vector2<Type> mRows[2];

    public :

        // -------------------- Methods -------------------- //

        /// Constructor
        Matrix2x2();

        /// Constructor
        Matrix2x2(Type value);

        /// Constructor
        Matrix2x2(Type a1, Type a2, Type b1, Type b2);

        /// Set all the values in the matrix
        void setAllValues(Type a1, Type a2, Type b1, Type b2);

        /// Set the matrix to zero
        void setToZero();

        /// Return a column
        Vector2<Type> getColumn(int i) const;

        /// Return a row
        Vector2<Type> getRow(int i) const;

        /// Return the transpose matrix
        Matrix2x2 getTranspose() const;

        /// Return the determinant of the matrix
        Type getDeterminant() const;

        /// Return the trace of the matrix
        Type getTrace() const;

        /// Return the inverse matrix
        Matrix2x2<Type> getInverse() const;

        /// Return the inverse matrix
        Matrix2x2<Type> getInverse(Type determinant) const;

        /// Return the matrix with absolute values
        Matrix2x2<Type> getAbsoluteMatrix() const;

        /// Set the matrix to the identity matrix
        void setToIdentity();

        /// Return the 2x2 identity matrix
        static Matrix2x2<Type> identity();

        /// Return the 2x2 zero matrix
        static Matrix2x2<Type> zero();

        /// Overloaded operator for addition
        friend Matrix2x2<Type> operator+(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2);

        /// Overloaded operator for substraction
        friend Matrix2x2<Type> operator-(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2);

        /// Overloaded operator for the negative of the matrix
        friend Matrix2x2<Type> operator-(const Matrix2x2<Type>& matrix);

        /// Overloaded operator for multiplication with a number
        friend Matrix2x2<Type> operator*(Type nb, const Matrix2x2<Type>& matrix);

        /// Overloaded operator for multiplication with a matrix
        friend Matrix2x2<Type> operator*(const Matrix2x2<Type>& matrix, Type nb);

        /// Overloaded operator for matrix multiplication
        friend Matrix2x2<Type> operator*(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2);

        /// Overloaded operator for multiplication with a vector
        //friend Vector2<Type> operator*(const Matrix2x2<Type>& matrix, const Matrix2x2<Type>& vector);

        /// Overloaded operator for equality condition
        bool operator==(const Matrix2x2<Type>& matrix) const;

        /// Overloaded operator for the is different condition
        bool operator!= (const Matrix2x2<Type>& matrix) const;

        /// Overloaded operator for addition with assignment
        Matrix2x2<Type>& operator+=(const Matrix2x2<Type>& matrix);

        /// Overloaded operator for substraction with assignment
        Matrix2x2<Type>& operator-=(const Matrix2x2<Type>& matrix);

        /// Overloaded operator for multiplication with a number with assignment
        Matrix2x2<Type>& operator*=(Type nb);

        /// Overloaded operator to read element of the matrix.
        const Vector2<Type>& operator[](int row) const;

        /// Overloaded operator to read/write element of the matrix.
        Vector2<Type>& operator[](int row);

        /// Return the string representation
        std::string to_string() const;
};

// Constructor of the class Matrix2x2
template <typename Type>
FORCEINLINE Matrix2x2<Type>::Matrix2x2() {

    // Initialize all values in the matrix to zero
    setAllValues(0.0, 0.0, 0.0, 0.0);
}

// Constructor
template <typename Type>
FORCEINLINE Matrix2x2<Type>::Matrix2x2(Type value) {
    setAllValues(value, value, value, value);
}

// Constructor with arguments
template <typename Type>
FORCEINLINE Matrix2x2<Type>::Matrix2x2(Type a1, Type a2, Type b1, Type b2) {

    // Initialize the matrix with the values
    setAllValues(a1, a2, b1, b2);
}

// Method to set all the values in the matrix
template <typename Type>
FORCEINLINE void Matrix2x2<Type>::setAllValues(Type a1, Type a2, Type b1, Type b2) {
    mRows[0][0] = a1; mRows[0][1] = a2;
    mRows[1][0] = b1; mRows[1][1] = b2;
}

// Set the matrix to zero
template <typename Type>
FORCEINLINE void Matrix2x2<Type>::setToZero() {
    mRows[0].setToZero();
    mRows[1].setToZero();
}

// Return a column
template <typename Type>
FORCEINLINE Vector2<Type> Matrix2x2<Type>::getColumn(int i) const {
    assert(i>= 0 && i<2);
    return Vector2(mRows[0][i], mRows[1][i]);
}

// Return a row
template <typename Type>
FORCEINLINE Vector2<Type> Matrix2x2<Type>::getRow(int i) const {
    assert(i>= 0 && i<2);
    return mRows[i];
}

// Return the transpose matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> Matrix2x2<Type>::getTranspose() const {

    // Return the transpose matrix
    return Matrix2x2(mRows[0][0], mRows[1][0],
                     mRows[0][1], mRows[1][1]);
}

// Return the determinant of the matrix
template <typename Type>
FORCEINLINE Type Matrix2x2<Type>::getDeterminant() const {

    // Compute and return the determinant of the matrix
    return mRows[0][0] * mRows[1][1] - mRows[1][0] * mRows[0][1];
}

// Return the trace of the matrix
template <typename Type>
FORCEINLINE Type Matrix2x2<Type>::getTrace() const {

    // Compute and return the trace
    return (mRows[0][0] + mRows[1][1]);
}

// Set the matrix to the identity matrix
template <typename Type>
FORCEINLINE void Matrix2x2<Type>::setToIdentity() {
    mRows[0][0] = 1.0; mRows[0][1] = 0.0;
    mRows[1][0] = 0.0; mRows[1][1] = 1.0;
}

// Return the 2x2 identity matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> Matrix2x2<Type>::identity() {

    // Return the isdentity matrix
    return Matrix2x2(1.0, 0.0, 0.0, 1.0);
}

// Return the 2x2 zero matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> Matrix2x2<Type>::zero() {
    return Matrix2x2(0.0, 0.0, 0.0, 0.0);
}

// Return the inverse matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> Matrix2x2<Type>::getInverse() const {

    return getInverse(getDeterminant());
}

// Return the matrix with absolute values
template <typename Type>
FORCEINLINE Matrix2x2<Type> Matrix2x2<Type>::getAbsoluteMatrix() const {
    return Matrix2x2(std::abs(mRows[0][0]), std::abs(mRows[0][1]),
                     std::abs(mRows[1][0]), std::abs(mRows[1][1]));
}

// Overloaded operator for addition
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator+(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2) {
    return Matrix2x2<Type>(matrix1.mRows[0][0] + matrix2.mRows[0][0],
                     matrix1.mRows[0][1] + matrix2.mRows[0][1],
                     matrix1.mRows[1][0] + matrix2.mRows[1][0],
                     matrix1.mRows[1][1] + matrix2.mRows[1][1]);
}

// Overloaded operator for substraction
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator-(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2) {
    return Matrix2x2<Type>(matrix1.mRows[0][0] - matrix2.mRows[0][0],
                     matrix1.mRows[0][1] - matrix2.mRows[0][1],
                     matrix1.mRows[1][0] - matrix2.mRows[1][0],
                     matrix1.mRows[1][1] - matrix2.mRows[1][1]);
}

// Overloaded operator for the negative of the matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator-(const Matrix2x2<Type>& matrix) {
    return Matrix2x2<Type>(-matrix.mRows[0][0], -matrix.mRows[0][1],
                     -matrix.mRows[1][0], -matrix.mRows[1][1]);
}

// Overloaded operator for multiplication with a number
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator*(Type nb, const Matrix2x2<Type>& matrix) {
    return Matrix2x2<Type>(matrix.mRows[0][0] * nb, matrix.mRows[0][1] * nb,
                     matrix.mRows[1][0] * nb, matrix.mRows[1][1] * nb);
}

// Overloaded operator for multiplication with a matrix
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator*(const Matrix2x2<Type>& matrix, Type nb) {
    return nb * matrix;
}

// Overloaded operator for matrix multiplication
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator*(const Matrix2x2<Type>& matrix1, const Matrix2x2<Type>& matrix2) {
    return Matrix2x2<Type>(matrix1.mRows[0][0] * matrix2.mRows[0][0] + matrix1.mRows[0][1] *
                     matrix2.mRows[1][0],
                     matrix1.mRows[0][0] * matrix2.mRows[0][1] + matrix1.mRows[0][1] *
                     matrix2.mRows[1][1],
                     matrix1.mRows[1][0] * matrix2.mRows[0][0] + matrix1.mRows[1][1] *
                     matrix2.mRows[1][0],
                     matrix1.mRows[1][0] * matrix2.mRows[0][1] + matrix1.mRows[1][1] *
                     matrix2.mRows[1][1]);
}

// Overloaded operator for multiplication with a vector
template <typename Type>
FORCEINLINE Matrix2x2<Type> operator*(const Matrix2x2<Type>& matrix, const Vector2<Type>& vector) {
    return Vector2(matrix.mRows[0][0]*vector.x + matrix.mRows[0][1]*vector.y,
                   matrix.mRows[1][0]*vector.x + matrix.mRows[1][1]*vector.y);
}

// Overloaded operator for equality condition
template <typename Type>
FORCEINLINE bool Matrix2x2<Type>::operator==(const Matrix2x2<Type>& matrix) const {
    return (mRows[0][0] == matrix.mRows[0][0] && mRows[0][1] == matrix.mRows[0][1] &&
            mRows[1][0] == matrix.mRows[1][0] && mRows[1][1] == matrix.mRows[1][1]);
}

// Overloaded operator for the is different condition
template <typename Type>
FORCEINLINE bool Matrix2x2<Type>::operator!= (const Matrix2x2<Type>& matrix) const {
    return !(*this == matrix);
}

// Overloaded operator for addition with assignment
template <typename Type>
FORCEINLINE Matrix2x2<Type>& Matrix2x2<Type>::operator+=(const Matrix2x2<Type>& matrix) {
   mRows[0][0] += matrix.mRows[0][0]; mRows[0][1] += matrix.mRows[0][1];
   mRows[1][0] += matrix.mRows[1][0]; mRows[1][1] += matrix.mRows[1][1];
   return *this;
}

// Overloaded operator for substraction with assignment
template <typename Type>
FORCEINLINE Matrix2x2<Type>& Matrix2x2<Type>::operator-=(const Matrix2x2<Type>& matrix) {
   mRows[0][0] -= matrix.mRows[0][0]; mRows[0][1] -= matrix.mRows[0][1];
   mRows[1][0] -= matrix.mRows[1][0]; mRows[1][1] -= matrix.mRows[1][1];
   return *this;
}

// Overloaded operator for multiplication with a number with assignment
template <typename Type>
FORCEINLINE Matrix2x2<Type>& Matrix2x2<Type>::operator*=(Type nb) {
   mRows[0][0] *= nb; mRows[0][1] *= nb;
   mRows[1][0] *= nb; mRows[1][1] *= nb;
   return *this;
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE const Vector2<Type>& Matrix2x2<Type>::operator[](int row) const {
    return mRows[row];
}

// Overloaded operator to return a row of the matrix.
/// This operator is also used to access a matrix value using the syntax
/// matrix[row][col].
template <typename Type>
FORCEINLINE Vector2<Type>& Matrix2x2<Type>::operator[](int row) {
    return mRows[row];
}

// Get the string representation
template <typename Type>
FORCEINLINE std::string Matrix2x2<Type>::to_string() const {
    return "Matrix2x2(" + std::to_string(mRows[0][0]) + "," + std::to_string(mRows[0][1]) + "," +
           std::to_string(mRows[1][0]) + "," + std::to_string(mRows[1][1]) + ")";
}

using Matrix2x2c = Matrix2x2<char>;
using Matrix2x2us = Matrix2x2<unsigned short>;
using Matrix2x2s = Matrix2x2<short>;
using Matrix2x2ui = Matrix2x2<unsigned int>;
using Matrix2x2i = Matrix2x2<int>;
using Matrix2x2f = Matrix2x2<float>;
using Matrix2x2d = Matrix2x2<double>;

#endif
