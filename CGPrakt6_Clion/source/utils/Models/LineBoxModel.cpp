//
//  LineBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "utils/Models/LineBoxModel.h"

LineBoxModel::LineBoxModel(float Width, float Height, float Depth) {
    float base = 0.1f;

    VB.begin();

    // 1
    VB.addVertex(base, 0, base);
    VB.addVertex(base + Width, 0, base);

    // 2
    VB.addVertex(base, 0, base);
    VB.addVertex(base, 0, base + Depth);

    // 3
    VB.addVertex(base, 0, base);
    VB.addVertex(base, 0 + Height, base);

    // 4
    VB.addVertex(base + Width, 0, base);
    VB.addVertex(base + Width, 0 + Height, base);

    // 5
    VB.addVertex(base + Width, 0, base);
    VB.addVertex(base + Width, 0, base + Depth);

    //6
    VB.addVertex(base + Width, 0 + Height, base);
    VB.addVertex(base, 0 + Height, base);

    //7
    VB.addVertex(base, 0, base + Depth);
    VB.addVertex(base + Width, 0, base + Depth);

    //8
    VB.addVertex(base, 0, base + Depth);
    VB.addVertex(base, 0 + Height, base + Depth);

    //9
    VB.addVertex(base + Width, 0, base + Depth);
    VB.addVertex(base + Width, 0 + Height, base + Depth);

    // 10
    VB.addVertex(base, 0 + Height, base + Depth);
    VB.addVertex(base + Width, 0 + Height, base + Depth);

    // 11
    VB.addVertex(base + Width, 0 + Height, base + Depth);
    VB.addVertex(base + Width, 0 + Height, base);


    // 12
    VB.addVertex(base, 0 + Height, base);
    VB.addVertex(base, 0 + Height, base + Depth);

    VB.end();
}

void LineBoxModel::draw(const BaseCamera &Cam) {
    // TODO: Add your code (Exercise 1) DONE
    BaseModel::draw(Cam);

    VB.activate();


    glDrawArrays(GL_LINES, 0, VB.vertexCount());

    VB.deactivate();
}