//
//  Application.hpp
//  ogl4
//
//  Created by Philipp Lensing on 16.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <list>
#include "camera.h"
#include "phongshader.h"
#include "constantshader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "basemodel.h"
#include "tank.h"

class Application
{
public:
    typedef std::list<BaseModel*> ModelList;
    Application(GLFWwindow* pWin);
    void start();
    void update();
    void update(float frametime);
    void draw();
    void end();
    void getInputForTank(GLFWwindow *pWindow, Tank * pTank);
protected:
    Vector calc3DRay(float xNormal, float yNormal, Vector& Pos);
    Camera Cam;
    ModelList Models;
    GLFWwindow* pWindow;
    Tank* pTank;
    Model* pTankTop;
    Model* pTankBot;

    float frameTime = 0;

};

#endif /* Application_hpp */
