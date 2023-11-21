#include "Vector3f.h"
#include <math.h>

// Constructors
Vector3f::Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

// Basic arithmetic operations
Vector3f Vector3f::operator+(const Vector3f& v) const {
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f Vector3f::operator-(const Vector3f& v) const {
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator*(float n) const {
    return Vector3f(x * n, y * n, z * n);
}

Vector3f Vector3f::operator/(float n) const {
    return Vector3f(x / n, y / n, z / n);
}

Vector3f Vector3f::unit() const {
    return *this / sqrt(x * x + y * y + z * z);
}

Vector3f Vector3f::cross(const Vector3f& v) const {
    return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
