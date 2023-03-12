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
#include "Camera.h"
#include "PhongShader.h"
#include "ConstantShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BaseModel.h"

class Application
{
public:
    typedef std::list<BaseModel*> ModelList;
    Application(GLFWwindow* pWin);
    void start();
    void update();
    void draw();
    void end();
protected:
    Camera Cam;
    ModelList Models;
    GLFWwindow* pWindow;

};

#endif /* Application_hpp */
