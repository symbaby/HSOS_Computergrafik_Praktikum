//
// Created by boery on 21.03.2022.
//

#include "../include/vector.h"

#include <assert.h>
#include <math.h>
#include "sstream"

#define EPSILON 1e-6

Vector::Vector(float x, float y, float z) : X(x), Y(y), Z(z) {
}

Vector::Vector() {
    // Sollen unitialisiert bleiben
}

float Vector::dot(const Vector &v) const {
    float erg = (this->X * v.X) +
                (this->Y * v.Y) +
                (this->Z * v.Z);

    return erg;
}

Vector Vector::cross(const Vector &v) const {
    // Kreuzprodukt Zellen ausrechnen

    float ergX = (this->Y * v.Z) - (this->Z * v.Y);
    float ergY = (this->Z * v.X) - (this->X * v.Z);
    float ergZ = (this->X * v.Y) - (this->Y * v.X);

    // Zellen zuweisen
    Vector erg(ergX, ergY, ergZ);

    return erg;
}


Vector Vector::operator+(const Vector &v) const {
    Vector erg;
    erg.X = this->X + v.X;
    erg.Y = this->Y + v.Y;
    erg.Z = this->Z + v.Z;

    return erg;
}

Vector Vector::operator-(const Vector &v) const {
    Vector erg;
    erg.X = this->X - v.X;
    erg.Y = this->Y - v.Y;
    erg.Z = this->Z - v.Z;

    return erg;
}

Vector Vector::operator*(float c) const {
    Vector erg;
    erg.X = this->X * c;
    erg.Y = this->Y * c;
    erg.Z = this->Z * c;

    return erg;
}

Vector Vector::operator-() const {
    Vector erg;
    erg.X = this->X * -1;
    erg.Y = this->Y * -1;
    erg.Z = this->Z * -1;

    return erg;
}

Vector &Vector::operator+=(const Vector &v) {
    this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;

    return *this;
}


Vector &Vector::normalize() {
    float m = 1 / (sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z));

    this->X *= m;
    this->Y *= m;
    this->Z *= m;

    return *this;
}

float Vector::length() const {
    float num = sqrt(lengthSquared());
    return num;
}

float Vector::lengthSquared() const {
    float num = this->X * this->X + this->Y * this->Y + this->Z * this->Z;
    return num;
}

/* Man musste die Formel:
 * V -2*(N*V)*N
 *
 * so umbasteln, sodass wir die zuvor programmierten Operatorueberladungen nutzen konnten.
 * */
Vector Vector::reflection(const Vector &normal) const {
    Vector R = *this + (normal * (this->dot(normal))) * -2;
    return R;
}

bool Vector::triangleIntersection(const Vector &d, const Vector &a, const Vector &b, const Vector &c, float &s) const {

    /** Kernschrott
    // n berechnen
    Vector zaehler = (b - a).cross(c - a);
    // Wir haben die .normalize() Methode...
    float nenner = ((b - a).cross(c - a)).length();
    Vector n = zaehler * (1 / nenner);
    */

    /* n ausrechen, laenge eines normalisierten Vektors = 1
     * Kreuzprodukt liefert uns: Flaeche des Parallelogramm,  Flaeche des Dreiecks ((AxB) / 2)
     */

    Vector n = (b - a).cross(c - a).normalize();

    // d ausrechnen
    float distanz = n.dot(a); // man kann aiuch n.dot(b) oder n.dot(c) nehmen!

    // s ausrechnen aus VL
    s = (distanz - (n.dot(*this))) / (n.dot(d));
    if (s < 0) {
        s = -1 * s; // Wenn skalarprodukt negativ ist, ist es hinter uns.
    }

    // Strahlgleichung aus VL
    Vector p = *this + (d * s);

    // Grosses Dreieck Flaeche
    float gF = (((b - a).cross(c - a)).length()) / 2;

    // Die "Teil-Dreiecke vom grossen Dreieck"
    float test1 = (((b - a).cross(p - a)).length()) / 2;
    float test2 = (((c - b).cross(p - b)).length()) / 2;
    float test3 = (((a - c).cross(p - c).length())) / 2;

    // Test
    // std::cout << "Test 1 " << test1 <<
    // std::endl << "Test 2 " << test2 <<
    // std::endl << "Test 3 " << test3 <<
    // std::endl;

    // Wenn die Flaeche + Korrekturfaktor >= die Flaeche addiert mit dreiecken, dann Kollsion
    if (gF + EPSILON >= (test1 + test2 + test3)) {
        return true;
    }

    return false;
}

// Ausgeben von Vektor in Konsole
std::ostream &operator<<(std::ostream &s, const Vector &out) {
    s << "X: " << out.X << std::endl
      << "Y: " << out.Y << std::endl
      << "Z: " << out.Z << std::endl;

    return s;
}



