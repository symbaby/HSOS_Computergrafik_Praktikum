//
// Created by boery on 21.03.2022.
//

#ifndef CGPRAKT1_VECTOR_H
#define CGPRAKT1_VECTOR_H

#include <iostream>

class Vector {
public:
    float X;
    float Y;
    float Z;

    Vector(float x, float y, float z);

    Vector();

    float dot(const Vector &v) const;

    Vector cross(const Vector &v) const;

    Vector operator+(const Vector &v) const;

    Vector operator-(const Vector &v) const;

    Vector &operator+=(const Vector &v);

    Vector operator*(float c) const;

    Vector operator-() const;

    Vector &normalize();

    float length() const;

    float lengthSquared() const;

    Vector reflection(const Vector &normal) const;

    bool triangleIntersection(const Vector &d, const Vector &a, const Vector &b,
                              const Vector &c, float &s) const;

    // Fuer einfache Tests
    friend std::ostream& operator<<(std::ostream &s, const Vector &out);
};



#endif //CGPRAKT1_VECTOR_H
