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
#include <GLFW/glfw3.h>
#include <math.h>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif

#include "../include/LinePlaneModel.h"
#include "../include/TrianglePlaneModel.h"
#include "../include/TriangleSphereModel.h"
#include "../include/LineBoxModel.h"
#include "../include/TriangleBoxModel.h"
#include "../include/Model.h"
#include "../include/Scene.h"


#ifdef WIN32
//#define ASSET_DIRECTORY "../../assets/"
#define ASSET_DIRECTORY "../assets/"
#else
#define ASSET_DIRECTORY "../assets/"
#endif


Application::Application(GLFWwindow *pWin) : pWindow(pWin), Cam(pWin) {
    BaseModel *pModel;
    ConstantShader *pConstShader;
    PhongShader *pPhongShader;

    // Shader laden
    pPhongShader = new PhongShader();

    // create LineGrid model with constant color shader
    pModel = new LinePlaneModel(10, 10, 10, 10);
    pConstShader = new ConstantShader();
    pConstShader->color(Color(1, 1, 1));
    pModel->shader(pConstShader, true);
    Models.push_back(pModel);

    // Exercise 1
    /*
    // TODO Load pTankTop & pTankBot
    pTank = new Tank();
    pTank->shader(pPhongShader, true);
    pTank->loadModels(ASSET_DIRECTORY "tank_bottom.dae", ASSET_DIRECTORY "tank_top.dae");
    Models.push_back(pTank->pTop);
    Models.push_back(pTank->pBottom);
    //Models.push_back(pTank);
*/

    // Exercise 2


    pPhongShader = new PhongShader();
    pTank = new Tank();
    pTank->shader(pPhongShader, true);
    pTank->loadModels(ASSET_DIRECTORY "tank_bottom.dae", ASSET_DIRECTORY "tank_top.dae");
    Models.push_back(pTank->pTop);
    Models.push_back(pTank->pBottom);
    //Models.push_back(pTank);



    // Exercise 3
    /*
    Scene* pScene = new Scene();
    pScene->shader(new PhongShader(), true);
    pScene->addSceneFile(ASSET_DIRECTORY "scene.osh");
    Models.push_back(pScene);
    */

}

void Application::start() {
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Application::update(float frameTime) {
    // Exercise 1
    // TODO: old Version mit FPS abhängigkeit
/* Alt, Abhängig von Fps
    float deltatime = ((-glfwGetTime()) / 3);
    Matrix RM, RMn, FlipM, TM, CanonZ;
    TM.translation(0, 0, 4);
    CanonZ.rotationY(-0.5 * AI_MATH_PI);
    FlipM.rotationY(AI_MATH_PI);

    RM.rotationY(deltatime * AI_MATH_PI);
    RMn.rotationY(-deltatime * AI_MATH_PI);

    pTank->pBottom->transform(RM * TM * FlipM);
    pTank->pTop->transform(RM * TM * RMn * CanonZ);
*/

/*
    // ToDo: Zeit unabhängig, der ist besser
    // eine Umdrehung in timeInSec Sekunden
    float timeInSec = 6;
    pTank->time += frameTime;

    // Straight Matrix, // Translation Matrix, // Rotation Matrix
    Matrix SM;
    Matrix TM;
    Matrix RM;

    // Panzer Haubitze nach unten gucken UND Panzer am anfang drehen
    SM.rotationY(AI_DEG_TO_RAD(270));


    //4 Einheiten um cursorX verschieben
    TM.translation(4, 0, 0);

    //clockwise rotation comes full circle after rimeInSec
    RM.rotationY(-1 * pTank->time * AI_MATH_PI * 2 / timeInSec);


    // SM richtig ausrichte, TM verschieben und mit RM schliesslich Rotaten
    pTank->pBottom->transform( RM * TM * SM);

    // RM Invertieren fuer die Haubitze damit die gerade nach unten zeigt
    RM.invert();

    // RM auf bottom Matrix multiplizieren und "verheiraten" und mit RM die drehen mit dem invertierten RM ausloeschen
    pTank->pTop->transform(pTank->pBottom->transform() * RM);
*/


    // Exercise 2
    // TODO: add your code here

    // Parameter die fuer die Steer Methode vorbereiten
    float BackwardForward = 0;
    float LeftRight = 0;

    // Bemerkung von Berkan und Johannes:
    // "Ich hab keine Pfeiltasten auf mein 60% Keyboard, deshalb mit WASD
    // DuckyOne2 Mini, Polaris"

    // W
    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS) {
        BackwardForward += 1.0f;
    }

    // A
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS) {
        BackwardForward -= 1.0f;
    }

    // S
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS) {
        LeftRight += 1.0f;
    }

    // D
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS) {
        LeftRight -= 1.0f;
    }

    // cursorX,cursorY ,windowX, windowY Workaround fuer ein Fehler.
    // GLFW will Pointer haben
    double *cursorX = new double;
    double *cursorY = new double;
    int *windowX = new int;
    int *windowY = new int;

    // Window Size in windowX und windowY speichern.
    glfwGetWindowSize(pWindow, windowX, windowY);

    // Window Size in windowX und windowY speichern.
    // WILL POINTER HABEN
    glfwGetCursorPos(pWindow, cursorX, cursorY);

    // Windowsize zwischenspeichern
    double xNormal = *windowX;
    double yNormal = *windowY;

    // Cursorposition in normalisierten Bildraum bringen. -1 bis 1
    xNormal = ((*cursorX / xNormal) - 0.5) * 2;
    yNormal = -((*cursorY / yNormal) - 0.5) * 2;

    // Dieser Vektor wird in cacl3DRay ueberschrieben
    Vector c(0, 0, 0);

    // Werte von -1 bis 1 werden uebergeben
    pTank->aim(calc3DRay(xNormal, yNormal, c));
    pTank->steer(BackwardForward, LeftRight);
    pTank->update(frameTime);

    // Alles mit new muss auch deleted werden
    delete (cursorX);
    delete (cursorY);
    delete (windowX);
    delete (windowY);

    Cam.update();
}


Vector Application::calc3DRay(float xNormal, float yNormal, Vector &Pos) {
    // Richtungsvektor zu erzeugen,
    // indem Sie die Projektionsmatrix (diese erhalten Sie von dem Kamera-Objekt,
    // welches in Application::Cam gespeichert ist) invers auf die neuen
    // Mauszeigerkoordinaten anwenden

    Matrix project = Cam.getProjectionMatrix();
    project.invert();

    // Die fehlende Z-Koordinate können Sie mit 0
    // annehmen.
    Vector erg(xNormal, yNormal, 0);

    // Das Ergebnis der Transformation ist ein Richtungsvektor im
    // Kameraraum (View-Coordinates).

    // WICHTIG: Projekt ist nun invers!
    erg = project * erg;

    // Kamera Matrix
    Matrix kameraMatrix = Cam.getViewMatrix();
    kameraMatrix.invert();

    // Siggi Kreuz mit KameraMatrix und erg, ergibt einen neuen Vektor
    // Fuer die Umrechnung solllte man bedenken, dass Sie nur die Richtung des Vektors
    // anpassen muessen und nicht dessen Ursprung (Matrix::transformVec3x3(...))
    erg = kameraMatrix.transformVec3x3(erg);

    // Ursprung ist jetzt Kameraposition
    Pos = Cam.position(); //Kameramatrix als Vektor

    // Normalvektor von der Y-Ebene
    Vector n(0, 1, 0);

    // Kollision berechnen nach Prakt 1 (Vektor Kollisionstest ) geklaut
    float s = n.dot(erg);
    s = s - (n.dot(Pos) / s);

    // Strahlgleichung
    erg = Pos + (erg * s);

    return erg;
}

void Application::draw() {
    // 1. clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for (ModelList::iterator it = Models.begin(); it != Models.end(); ++it) {
        (*it)->draw(Cam);
    }

    // 3. check once per frame for opengl errors
    GLenum Error = glGetError();
    assert(Error == 0);
}

void Application::end() {
    for (ModelList::iterator it = Models.begin(); it != Models.end(); ++it)
        delete *it;

    Models.clear();
}


