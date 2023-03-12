//
//  Tank.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "../include/Tank.h"
#include "../include/PhongShader.h"


Tank::Tank() {
    // TODO: Add your code

    // pBottom = nullptr;
    // pTop = nullptr;


    // Zeiger Instanziieruen
    pTop = new Model;
    pBottom = new Model;

}

Tank::~Tank() {
    // TODO: Add your code
    delete pTop;
    delete pBottom;
}

bool Tank::loadModels(const char *ChassisFile, const char *CannonFile) {
    // TODO: Add your code

    /*
    pBottom = new Model(ChassisFile, false);
    pBottom->shader(new PhongShader(), true);

    pTop = new Model(CannonFile, false);
    pTop->shader(new PhongShader(), true);

    return true;
     */

    pTop->load(CannonFile, false);
    pTop->shader(pShader, true);


    pBottom->load(ChassisFile, false);
    pBottom->shader(pShader, true);

    return true;


}

void Tank::steer(float ForwardBackward, float LeftRight) {
    // TODO: Add your code
    speed = ForwardBackward;
    rotation = LeftRight;


}

void Tank::aim(const Vector &Target) {
    // TODO: Add your code
    this->target = Target;
}

void Tank::update(float dtime) {
    // TODO: Add your code
    Matrix bottom;
    Matrix top;
    Matrix rotM;

    TM.translation(speed * dtime, 0, 0);
    RM.rotationY(rotation * dtime);

    bottom = pBottom->transform() * RM * TM;

    pBottom->transform(bottom);
    //pTop->transform(bottom);

    // Zur ausrichung an MausCoords
    top.lookAt(this->target, bottom.up(), bottom.translation());
    // Brauchen wir sonst ist Kanone und Mauspos verdreht
    top.invert();

    rotM.rotationY(AI_DEG_TO_RAD(90));
    pTop->transform(top * rotM);

}

void Tank::draw(const BaseCamera &Cam) {
    // TODO: Add your code
    // KP ob das passt
    pTop->draw(Cam);
    pBottom->draw(Cam);
}

