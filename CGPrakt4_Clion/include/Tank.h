//
//  Tank.hpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include "model.h"

class Tank : public BaseModel {
public:
    Tank();

    virtual ~Tank();

    bool loadModels(const char *ChassisFile, const char *CannonFile);

    void steer(float ForwardBackward, float LeftRight);

    void aim(const Vector &Target);

    void update(float dtime);

    virtual void draw(const BaseCamera &Cam);


    Model *pTop;
    Model *pBottom;

    float time = 0.f;

protected:


    float speed = 0.f;
    float rotation = 0.f;

    Vector target;


    Matrix TM;
    Matrix RM;
};

#endif /* Tank_hpp */
