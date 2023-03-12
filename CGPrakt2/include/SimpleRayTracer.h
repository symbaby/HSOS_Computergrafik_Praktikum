//
//  SimpleRayTracer.h
//  SimpleRayTracer
//
//  Created by Philipp Lensing on 03.09.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#ifndef SimpleRayTracer_SimpleRayTracer_h
#define SimpleRayTracer_SimpleRayTracer_h

#include "CGUtilities.h"

class RGBImage;

class Camera {
public:
    Camera(float zvalue, float planedist, float width, float height, unsigned int widthInPixel,
           unsigned int heightInPixel);

    Vector generateRay(unsigned int x, unsigned int y) const;

    Vector generateRay( float x,  float y) const ;

    Vector Position() const;

    float m_zvalue;
    float m_planedist;
    float m_width;
    float m_heigth;

    float m_aspectRatio;

    unsigned int m_widthInPixel;
    unsigned int m_heightInPixel;



    friend std::ostream& operator<<(std::ostream &s, const Camera &out);

};

class SimpleRayTracer {
private:
    float dotPositive(const Vector& a, const Vector& b);
public:

    int m_maxDepth = 0;

    SimpleRayTracer(unsigned int MaxDepth);

    void traceScene(const Scene &SceneModel, RGBImage &Image);

protected:
    Color trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth);

    Color
    localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal, const PointLight &Light,
                      const Material &Material);

    Color
    trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth, Color q);
};

#endif //CGPRAKT2_SIMPLERAYTRACER_H
