#ifndef __SimpleRayTracer__vector__
#define __SimpleRayTracer__vector__

#include <iostream>

class Vector
{
public:
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;
    
    Vector( float x, float y, float z);
    Vector();
    
    float dot(const Vector& v) const;
    Vector cross(const Vector& v) const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector& operator+=(const Vector& v);
    Vector operator*(float c) const;
    Vector operator-() const;
    Vector& normalize();
    float length() const;
    float lengthSquared() const;
    Vector reflection( const Vector& normal) const;
    bool triangleIntersection( const Vector& d, const Vector& a, const Vector& b,
                              const Vector& c, float& s) const;
 };

#endif /* defined(__SimpleRayTracer__vector__) */
