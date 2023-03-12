//
// Created by boery on 01.04.2022.
//

//
//  SimpleRayTracer.cpp
//  SimpleRayTracer
//
//  Created by Philipp Lensing on 03.09.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#define EPSILON 1e-6
#define GAMMA 1e-4

#include "../include/SimpleRayTracer.h"
#include "../include/rgbimage.h"
#include "../include/vector.h"
#include <math.h>


using namespace std;


Camera::Camera(float zvalue, float planedist, float width, float height, unsigned int widthInPixel,
               unsigned int heightInPixel) {
    this->m_zvalue = zvalue;
    this->m_planedist = planedist;
    this->m_width = width;
    this->m_heigth = height;
    this->m_heightInPixel = heightInPixel;
    this->m_widthInPixel = widthInPixel;
    // this->m_aspectRatio = (float) widthInPixel / heightInPixel;

}

// Konstruktor
SimpleRayTracer::SimpleRayTracer(unsigned int MaxDepth) : m_maxDepth(MaxDepth) {
}


void SimpleRayTracer::traceScene(const Scene &SceneModel, RGBImage &Image) {
    // Noch scuffed aber funktioniert
    Camera camera(-8.0f, 1, 1, Image.height(), 640, 480);
    Vector o(camera.Position()); // Augpunkt

    unsigned int kx = 0;
    unsigned int ky = 0;

    int xMinusRange = camera.m_widthInPixel / 2 * -1;
    int xPlusRange = camera.m_widthInPixel / 2;

    int yMinusRange = camera.m_heightInPixel / 2 * -1;
    int yPlusRange = camera.m_heightInPixel / 2;

    for (int x = xMinusRange; x < xPlusRange; x++) {
        for (int y = yPlusRange; y > yMinusRange; y--) {

            float uebergabeX = x / 640.00f;
            float uebergabeY = y / 640.00f;
            Vector d = camera.generateRay(uebergabeX, uebergabeY);

            Image.setPixelColor(kx, ky, trace(SceneModel, o, d, m_maxDepth));
            ky++;
        }
        ky = 0;
        kx++;
    }
}

Vector Camera::generateRay(float x, float y) const {

    Vector augeVec = Position();
    // Oben Rechts : Default

    //Vector eckeVec((m_widthInPixel / 2), (m_heightInPixel / 2), (m_zvalue + m_planedist));
    Vector eckeVec(x, y, (m_zvalue + m_planedist));

    Vector finalVec = eckeVec - augeVec;
    finalVec.normalize();
    return finalVec;
}

Vector Camera::Position() const {
    return {0, 0, m_zvalue};
}


Color SimpleRayTracer::trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth) {
    Color color;

    // Berechne ersten Auftreffpunkt p des Strahls s auf der Objektoberflaeche
    float smallestDist = INFINITY;
    int triangleIndex = -1; //wird später auf i gesetzt
    float s = 0;

    // wir suchen das nächste dreieck, auf welches der Strahl trifft
    // jedes triangle durchprobieren
    for (int i = 0; i < SceneModel.getTriangleCount(); i++) {
        Triangle t = SceneModel.getTriangle(i);

        //wir schauen, ob von dem augpunkt(oder später reflektionspunkt) eine sichtverbindung zu dem dreieck besteht
        if (o.triangleIntersection(d, t.A, t.B, t.C, s)) {

            //wenn der abstand weniger ist als ein vorheriges dreieck
            if (s > EPSILON && s < smallestDist) { //EPSILON == 1e-6 == 0.00000001
                smallestDist = s;
                triangleIndex = i; //wird auf i gesetzt um zu speichern
            }
        }
    }
    if (triangleIndex < 0) {
        return Color();
    } // falls der Strahl auf kein Dreieck getroffen ist

    // Auftreffpunkt auf dem dreieck
    Vector p = o + d * smallestDist;
    Triangle t = SceneModel.getTriangle(triangleIndex);
    Vector n = t.calcNormal(p); //normale des Dreiecks berechnen

    color += t.pMtrl->getAmbientCoeff(p);
    // Pruefe, ob von Punkt p Sichtverbindung zur Lichtquelle besteht
    for (int i = 0; i < SceneModel.getLightCount(); i++) { //wir gehen durch alle lichter
        PointLight light = SceneModel.getLight(i);

        float s;
        Vector lp = light.Position - p;	//vektor zwischen punkt p und lichtquelle
        float length = lp.length();	//length zwischenspeichern, da wir normalisieren
        lp.normalize();
        bool visualContact = true;

        // wieder durch alle dreiecke
        for (int j = 0; j < SceneModel.getTriangleCount(); j++) {
            Triangle t = SceneModel.getTriangle(j);
            if (p.triangleIntersection(lp, t.A, t.B, t.C, s)) {	//wir überprüfen, ob das dreieck von der Lichtquelle bestrahlt wird
                //1e-4 ist margin of error, s muss positiv sein
                if (length > s && s > GAMMA) {
                    visualContact = false;
                    break;
                }
            }
        }

        // Wenn JA: F += Berechne_Lokales_Beleuchtungsmodell(...)
        if (visualContact) color += this->localIllumination(p, o, n, light, *(t.pMtrl));
    }

    // wenn noch reflektionen zu bearbeiten sind
    if (depth > 0) {
        // Berechne Reflexionsstrahl r von s im Punkt p
        Vector r = d.reflection(n);

        //  F = F + Raytracing(r) * Reflexionskoeffizient;
        color += trace(SceneModel, p, r, --depth) * t.pMtrl->getReflectivity(p);
    }

    return color;
}

Color
SimpleRayTracer::localIllumination(const Vector &Surface, const Vector &Eye, const Vector &N, const PointLight &Light,
                                   const Material &Mtrl) {

    // Formeln aus Vorlesung
    // Phong Shading

    Vector L = (Light.Position - Surface).normalize();
    Vector E = (Eye - Surface).normalize();
    //Vector R = (N * 2 * L.dot(N) - L).normalize();

    Vector R = L.reflection(N).normalize();

    Color D = Light.Intensity * Mtrl.getDiffuseCoeff(Surface) * L.dot(N);
    Color S = Light.Intensity * Mtrl.getSpecularCoeff(Surface) * pow(E.dot(R), Mtrl.getSpecularExp(Surface));

    // Ambient = indirektes licht

    return D + S;
}


// RGB in die Konsole printen
std::ostream &operator<<(std::ostream &s, const Camera &out) {
    s << "zvalue: " << out.m_zvalue << std::endl
      << "plandedist: " << out.m_planedist << std::endl
      << "width: " << out.m_width << std::endl
      << "height: " << out.m_heigth << std::endl
      << "widthInPixel: " << out.m_widthInPixel << std::endl
      << "heightInPixel: " << out.m_heightInPixel << std::endl;

    return s;
}

// unused shit
float SimpleRayTracer::dotPositive(const Vector &a, const Vector &b) {
    float dotOfAB = a.dot(b);
    if (dotOfAB < 0.0f)
        dotOfAB *= -1;
    return dotOfAB;
}


