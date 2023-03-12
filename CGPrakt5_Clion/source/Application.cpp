//
//  Application.cpp
//  ogl4
//
//  Created by Philipp Lensing on 16.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "../include/Application.h"

#ifdef WIN32

#include <GL/glew.h>
#include <glfw/glfw3.h>

#define _USE_MATH_DEFINES

#include <cmath>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif

#include "../include/LinePlaneModel.h"
#include "../include/Model.h"
#include "../include/TerrainShader.h"


#ifdef WIN32
#define ASSET_DIRECTORY "../assets/"
#else
#define ASSET_DIRECTORY "../assets/"
#endif


Application::Application(GLFWwindow *pWin) : pWindow(pWin), Cam(pWin) {
    BaseModel *pModel;

    // create LineGrid model with constant color shader
    pModel = new LinePlaneModel(10, 10, 10, 10);
    auto *pConstShader = new ConstantShader();
    pConstShader->color(Color(1, 0, 0));
    pModel->shader(pConstShader, true);
    // add to render list
    Models.push_back(pModel);

    // Exercise 1
    // uncomment the following lines for testing
    pModel = new Model(ASSET_DIRECTORY "skybox.obj", false);
    pModel->shader(new PhongShader(), true);
    Models.push_back(pModel);

    pTerrain = new Terrain();
    auto *pTerrainShader = new TerrainShader(ASSET_DIRECTORY);
    pTerrain->shader(pTerrainShader, true);
    pTerrain->load(ASSET_DIRECTORY"heightmap.bmp", ASSET_DIRECTORY"grass2.bmp", ASSET_DIRECTORY"rock2.jpg");
    pTerrain->width(150);
    pTerrain->depth(150);
    pTerrain->height(15);
    Models.push_back(pTerrain);

}

void Application::start() {
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Application::update(float dtime) {
    // Exercise 1
    // TODO: Add keyboard & mouse input queries for terrain scaling ..

    inputScaleTerrain();
    static float Time = 0;
    Time+=dtime;
    ((TerrainShader*)pTerrain->BaseModel::shader())->time(Time*0.05f);

    Matrix Trans,Rot, Trans2;
    Rot.rotationY(-Time);
    Trans.translation(0.4f, 0, -0.15f);
    Trans2.translation(5.5f, 1.5, 2.8f);

    Cam.update();


}

void Application::inputScaleTerrain() {
    double mx, my;
    static bool Scaling = false;
    static Vector ScaleOrg;
    static Vector MouseOrg;
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS && !Scaling) {
        glfwGetCursorPos(pWindow, &mx, &my);
        MouseOrg = Vector(mx, my, 0);
        ScaleOrg = pTerrain->size();
        Scaling = true;

    }
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_RELEASE && Scaling)
        Scaling = false;

    if (Scaling) {
        Vector Scale = ScaleOrg;
        glfwGetCursorPos(pWindow, &mx, &my);
        Vector MouseDiff = Vector(mx, my, 0) - MouseOrg;
        MouseDiff.X = MouseDiff.X * 0.001f;
        MouseDiff.Y = MouseDiff.Y * 0.02f;

        float sx = 1, sy = 1;

        if (MouseDiff.X > 0)
            sx = 1.0f + MouseDiff.X;
        else if (MouseDiff.X < 0)
            sx = 1.0f / (1 - MouseDiff.X);
        if (MouseDiff.Y < 0)
            sy = 1.0f - MouseDiff.Y;
        else if (MouseDiff.Y > 0)
            sy = 1.0f / (1 + MouseDiff.Y);

        Scale.X *= sx;
        Scale.Y *= sy;
        Scale.Z *= sx;

        pTerrain->size(Scale);
    }
}

void Application::draw() {
    // 1. clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for (auto it = Models.begin(); it != Models.end(); ++it) {
        (*it)->draw(Cam);
    }

    // 3. check once per frame for opengl errors
    GLenum Error = glGetError();
    assert(Error == 0);
}

void Application::end() {
    for (auto it = Models.begin(); it != Models.end(); ++it)
        delete *it;

    Models.clear();
}

