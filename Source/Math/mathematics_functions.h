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

#ifndef REACTPHYSICS3D_MATHEMATICS_FUNCTIONS_H
#define REACTPHYSICS3D_MATHEMATICS_FUNCTIONS_H

// Libraries
#include <reactphysics3d/configuration.h>
#include <reactphysics3d/decimal.h>
//#include <reactphysics3d/mathematics/Vector3.h>
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "Vector3.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <reactphysics3d/containers/Array.h>

/// ReactPhysics3D namespace
namespace reactphysics3d {

//class Vector3;
//class Vector2;

// ---------- Mathematics functions ---------- //

/// Function that returns the result of the "value" clamped by
/// two others values "lowerLimit" and "upperLimit"
RP3D_FORCE_INLINE int clamp(int value, int lowerLimit, int upperLimit) {
    assert(lowerLimit <= upperLimit);
    return std::min(std::max(value, lowerLimit), upperLimit);
}

/// Function that returns the result of the "value" clamped by
/// two others values "lowerLimit" and "upperLimit"
RP3D_FORCE_INLINE float clamp(float value, float lowerLimit, float upperLimit) {
    assert(lowerLimit <= upperLimit);
    return std::min(std::max(value, lowerLimit), upperLimit);
}

/// Return the minimum value among three values
RP3D_FORCE_INLINE float min3(float a, float b, float c) {
    return std::min(std::min(a, b), c);
}

/// Return the maximum value among three values
RP3D_FORCE_INLINE float max3(float a, float b, float c) {
    return std::max(std::max(a, b), c);
}

/// Return true if two values have the same sign
RP3D_FORCE_INLINE bool sameSign(float a, float b) {
    return a * b >= float(0.0);
}

// Return true if two vectors are parallel
RP3D_FORCE_INLINE bool areParallelVectors(Vector3f vector1, const Vector3f& vector2) {
    return vector1.Cross(vector2).LengthSquared() < float(0.00001);
}


// Return true if two vectors are orthogonal
RP3D_FORCE_INLINE bool areOrthogonalVectors(Vector3f vector1, const Vector3f& vector2) {
    return std::abs(vector1.Dot(vector2)) < float(0.001);
}


// Clamp a vector such that it is no longer than a given maximum length
RP3D_FORCE_INLINE Vector3f clamp(Vector3f vector, float maxLength) {
    if (vector.LengthSquared() > maxLength * maxLength) {
        return vector.GetUnit() * maxLength;
    }
    return vector;
}

// Compute and return a point on segment from "segPointA" and "segPointB" that is closest to point "pointC"
RP3D_FORCE_INLINE Vector3f computeClosestPointOnSegment(const Vector3f& segPointA, const Vector3f& segPointB, const Vector3f& pointC) {

    Vector3f ab = segPointB - segPointA;

    float abLengthSquare = ab.LengthSquared();

    // If the segment has almost zero length
    if (abLengthSquare < MACHINE_EPSILON) {

        // Return one end-point of the segment as the closest point
        return segPointA;
    }

    // Project point C onto "AB" line
    float t = (pointC - segPointA).Dot(ab) / abLengthSquare;

    // If projected point onto the line is outside the segment, clamp it to the segment
    if (t < float(0.0)) t = float(0.0);
    if (t > float(1.0)) t = float(1.0);

    // Return the closest point on the segment
    return segPointA + ab * t;
}

// Compute the closest points between two segments
// This method uses the technique described in the book Real-Time
// collision detection by Christer Ericson.
RP3D_FORCE_INLINE void computeClosestPointBetweenTwoSegments(const Vector3f& seg1PointA, const Vector3f& seg1PointB,
                                                             const Vector3f& seg2PointA, const Vector3f& seg2PointB,
                                                             Vector3f& closestPointSeg1, Vector3f& closestPointSeg2) {

    Vector3f d1 = seg1PointB - seg1PointA;
    Vector3f d2 = seg2PointB - seg2PointA;
    Vector3f r = seg1PointA - seg2PointA;
    float a = d1.LengthSquared();
    float e = d2.LengthSquared();
    float f = d2.Dot(r);
    float s, t;

    // If both segments degenerate into points
    if (a <= MACHINE_EPSILON && e <= MACHINE_EPSILON) {

        closestPointSeg1 = seg1PointA;
        closestPointSeg2 = seg2PointA;
        return;
    }
    if (a <= MACHINE_EPSILON) {   // If first segment degenerates into a point

        s = float(0.0);

        // Compute the closest point on second segment
        t = clamp(f / e, float(0.0), decimal(1.0));
    }
    else {

        float c = d1.Dot(r);

        // If the second segment degenerates into a point
        if (e <= MACHINE_EPSILON) {

            t = float(0.0);
            s = clamp(-c / a, float(0.0), float(1.0));
        }
        else {

            float b = d1.Dot(d2);
            float denom = a * e - b * b;

            // If the segments are not parallel
            if (denom != float(0.0)) {

                // Compute the closest point on line 1 to line 2 and
                // clamp to first segment.
                s = clamp((b * f - c * e) / denom, float(0.0), float(1.0));
            }
            else {

                // Pick an arbitrary point on first segment
                s = float(0.0);
            }

            // Compute the point on line 2 closest to the closest point
            // we have just found
            t = (b * s + f) / e;

            // If this closest point is inside second segment (t in [0, 1]), we are done.
            // Otherwise, we clamp the point to the second segment and compute again the
            // closest point on segment 1
            if (t < float(0.0)) {
                t = float(0.0);
                s = clamp(-c / a, float(0.0), float(1.0));
            }
            else if (t > float(1.0)) {
                t = float(1.0);
                s = clamp((b - c) / a, float(0.0), float(1.0));
            }
        }
    }

    // Compute the closest points on both segments
    closestPointSeg1 = seg1PointA + d1 * s;
    closestPointSeg2 = seg2PointA + d2 * t;
}

// Compute the barycentric coordinates u, v, w of a point p inside the triangle (a, b, c)
// This method uses the technique described in the book Real-Time collision detection by
// Christer Ericson.
RP3D_FORCE_INLINE void computeBarycentricCoordinatesInTriangle(const Vector3f& a, const Vector3f& b, const Vector3f& c,
                                             const Vector3f& p, float& u, float& v, float& w) {
    Vector3f v0 = b - a;
    Vector3f v1 = c - a;
    Vector3f v2 = p - a;

    const float d00 = v0.Dot(v0);
    const float d01 = v0.Dot(v1);
    const float d11 = v1.Dot(v1);
    const float d20 = v2.Dot(v0);
    const float d21 = v2.Dot(v1);

    const float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = float(1.0) - v - w;
}

// Compute the intersection between a plane and a segment
// Let the plane define by the equation planeNormal.dot(X) = planeD with X a point on the plane and "planeNormal" the plane normal. This method
// computes the intersection P between the plane and the segment (segA, segB). The method returns the value "t" such
// that P = segA + t * (segB - segA). Note that it only returns a value in [0, 1] if there is an intersection. Otherwise,
// there is no intersection between the plane and the segment.
RP3D_FORCE_INLINE float computePlaneSegmentIntersection(const Vector3f& segA, const Vector3f& segB, const float planeD, Vector3f planeNormal) {

    const float parallelEpsilon = float(0.0001);
    float t = float(-1);

    const float nDotAB = planeNormal.Dot(segB - segA);

    // If the segment is not parallel to the plane
    if (std::abs(nDotAB) > parallelEpsilon) {
        t = (planeD - planeNormal.Dot(segA)) / nDotAB;
    }

    return t;
}

// Compute the distance between a point "point" and a line given by the points "linePointA" and "linePointB"
RP3D_FORCE_INLINE float computePointToLineDistance(const Vector3f& linePointA, const Vector3f& linePointB, const Vector3f& point) {

    float distAB = (linePointB - linePointA).Length();

    if (distAB < MACHINE_EPSILON) {
        return (point - linePointA).Length();
    }

    return ((point - linePointA).Cross(point - linePointB)).Length() / distAB;
}


// Clip a segment against multiple planes and return the clipped segment vertices
// This method implements the Sutherland–Hodgman clipping algorithm
RP3D_FORCE_INLINE Array<Vector3f> clipSegmentWithPlanes(const Vector3f& segA, const Vector3f& segB,
                                                           const Array<Vector3f>& planesPoints,
                                                           Array<Vector3f>& planesNormals,
                                                           MemoryAllocator& allocator) {
    assert(planesPoints.size() == planesNormals.size());

    Array<Vector3f> inputVertices(allocator, 2);
    Array<Vector3f> outputVertices(allocator, 2);

    inputVertices.add(segA);
    inputVertices.add(segB);

    // For each clipping plane
    const uint32 nbPlanesPoints = static_cast<uint32>(planesPoints.size());
    for (uint32 p=0; p < nbPlanesPoints; p++) {

        // If there is no more vertices, stop
        if (inputVertices.size() == 0) return inputVertices;

        assert(inputVertices.size() == 2);

        outputVertices.clear();

        Vector3f& v1 = inputVertices[0];
        Vector3f& v2 = inputVertices[1];

        float v1DotN = (v1 - planesPoints[p]).Dot(planesNormals[p]);
        float v2DotN = (v2 - planesPoints[p]).Dot(planesNormals[p]);

        // If the second vertex is in front of the clippling plane
        if (v2DotN >= float(0.0)) {

            // If the first vertex is not in front of the clippling plane
            if (v1DotN < float(0.0)) {

                // The second point we keep is the intersection between the segment v1, v2 and the clipping plane
                float t = computePlaneSegmentIntersection(v1, v2, planesNormals[p].Dot(planesPoints[p]), planesNormals[p]);

                if (t >= float(0) && t <= float(1.0)) {
                    outputVertices.add(v1 + (v2 - v1) * t);
                }
                else {
                    outputVertices.add(v2);
                }
            }
            else {
                outputVertices.add(v1);
            }

            // Add the second vertex
            outputVertices.add(v2);
        }
        else {  // If the second vertex is behind the clipping plane

            // If the first vertex is in front of the clippling plane
            if (v1DotN >= float(0.0)) {

                outputVertices.add(v1);

                // The first point we keep is the intersection between the segment v1, v2 and the clipping plane
                float t = computePlaneSegmentIntersection(v1, v2, -planesNormals[p].Dot(planesPoints[p]), -planesNormals[p]);

                if (t >= float(0.0) && t <= float(1.0)) {
                    outputVertices.add(v1 + (v2 - v1) * t);
                }
            }
        }

        inputVertices = outputVertices;
    }

    return outputVertices;
}

// Clip a polygon against a single plane and return the clipped polygon vertices
// This method implements the Sutherland–Hodgman polygon clipping algorithm
RP3D_FORCE_INLINE void clipPolygonWithPlane(const Array<Vector3f>& polygonVertices, const Vector3f& planePoint,
                                            Vector3f planeNormal, Array<Vector3f>& outClippedPolygonVertices) {

    uint32 nbInputVertices = static_cast<uint32>(polygonVertices.size());

    assert(outClippedPolygonVertices.size() == 0);

    uint32 vStartIndex = nbInputVertices - 1;

    const float planeNormalDotPlanePoint = planeNormal.Dot(planePoint);

    float vStartDotN = (polygonVertices[vStartIndex] - planePoint).Dot(planeNormal);

    // For each edge of the polygon
    for (uint vEndIndex = 0; vEndIndex < nbInputVertices; vEndIndex++) {

        const Vector3f& vStart = polygonVertices[vStartIndex];
        const Vector3f& vEnd = polygonVertices[vEndIndex];

        const float vEndDotN = (vEnd - planePoint).Dot(planeNormal);

        // If the second vertex is in front of the clippling plane
        if (vEndDotN >= float(0.0)) {

            // If the first vertex is not in front of the clippling plane
            if (vStartDotN < float(0.0)) {

                // The second point we keep is the intersection between the segment v1, v2 and the clipping plane
                const float t = computePlaneSegmentIntersection(vStart, vEnd, planeNormalDotPlanePoint, planeNormal);

                if (t >= float(0) && t <= float(1.0)) {
                    outClippedPolygonVertices.add(vStart + (vEnd - vStart) * t);
                }
                else {
                    outClippedPolygonVertices.add(vEnd);
                }
            }

            // Add the second vertex
            outClippedPolygonVertices.add(vEnd);
        }
        else {  // If the second vertex is behind the clipping plane

            // If the first vertex is in front of the clippling plane
            if (vStartDotN >= float(0.0)) {

                // The first point we keep is the intersection between the segment v1, v2 and the clipping plane
                const float t = computePlaneSegmentIntersection(vStart, vEnd, -planeNormalDotPlanePoint, -planeNormal);

                if (t >= float(0.0) && t <= float(1.0)) {
                    outClippedPolygonVertices.add(vStart + (vEnd - vStart) * t);
                }
                else {
                    outClippedPolygonVertices.add(vStart);
                }
            }
        }

        vStartIndex = vEndIndex;
        vStartDotN = vEndDotN;
    }
}

// Project a point onto a plane that is given by a point and its unit length normal
RP3D_FORCE_INLINE Vector3f projectPointOntoPlane(const Vector3f& point, Vector3f unitPlaneNormal, const Vector3f& planePoint) {
    return point - unitPlaneNormal * unitPlaneNormal.Dot(point - planePoint) ;
}

// Return the distance between a point and a plane (the plane normal must be normalized)
RP3D_FORCE_INLINE float computePointToPlaneDistance(const Vector3f& point, Vector3f planeNormal, const Vector3f& planePoint) {
    return planeNormal.Dot(point - planePoint);
}

/// Return true if a number is a power of two
RP3D_FORCE_INLINE bool isPowerOfTwo(uint64 number) {
   return number != 0 && !(number & (number -1));
}

/// Return the next power of two larger than the number in parameter
RP3D_FORCE_INLINE uint64 nextPowerOfTwo64Bits(uint64 number) {
    number--;
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
    number |= number >> 32;
    number++;
    number += (number == 0);
    return number;
}

/// Return an unique integer from two integer numbers (pairing function)
/// Here we assume that the two parameter numbers are sorted such that
/// number1 = max(number1, number2)
/// http://szudzik.com/ElegantPairing.pdf
RP3D_FORCE_INLINE uint64 pairNumbers(uint32 number1, uint32 number2) {
    assert(number1 == std::max(number1, number2));
    uint64 nb1 = number1;
    uint64 nb2 = number2;
    return nb1 * nb1 + nb1 + nb2;
}


}


#endif
