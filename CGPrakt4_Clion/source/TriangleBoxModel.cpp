//
//  TriangleBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "../include/TriangleBoxModel.h"

TriangleBoxModel::TriangleBoxModel(float Width, float Height, float Depth) {

    // TODO: Add your code (Exercise 2)
    /// TODO Hardcode shit aufraeumen + normale fixen
    VB.begin();

    //Die Werte im Koordinatensystem
    float CoordWidth = Width / 2;
    float CoordHeight = Height / 2;
    float CoordDepth = Depth / 2;

    //Die Punkte
    Vector vorne_unten_links(-CoordWidth, -CoordHeight, -CoordDepth); // 0
    Vector vorne_oben_links(-CoordWidth, CoordHeight, -CoordDepth); // 1
    Vector vorne_unten_rechts(-CoordWidth, -CoordHeight, CoordDepth); // 2
    Vector vorne_oben_rechts(-CoordWidth, CoordHeight, CoordDepth); // 3
    Vector hinten_unten_links(CoordWidth, -CoordHeight, -CoordDepth); // 4
    Vector hinten_unten_rechts(CoordWidth, -CoordHeight, CoordDepth); // 5
    Vector hinten_oben_links(CoordWidth, CoordHeight, -CoordDepth); // 6
    Vector hinten_oben_rechts(CoordWidth, CoordHeight, CoordDepth); // 7


    //Die Normalen fuer Beleuchtung berechnen
    Vector boden_normal = -hinten_unten_rechts.normal(hinten_unten_rechts, hinten_unten_links,
                                                      vorne_unten_links); /*BODEN*/

    Vector rechts_normal = hinten_unten_rechts.normal(hinten_unten_rechts, hinten_unten_links,
                                                      hinten_oben_rechts); /*RECHTS*/

    Vector hinten_normal = hinten_unten_rechts.normal(hinten_unten_links, vorne_unten_links,
                                                      hinten_oben_links); /*HINTEN*/

    Vector links_normal = -hinten_unten_rechts.normal(vorne_unten_rechts, vorne_unten_links,
                                                      vorne_oben_links); /*LINKS*/

    Vector oben_normal = -hinten_unten_rechts.normal(hinten_oben_links, hinten_oben_rechts,
                                                     vorne_oben_rechts); /*OBEN*/

    Vector vorne_normal = -hinten_unten_rechts.normal(hinten_unten_rechts, vorne_unten_rechts,
                                                      vorne_oben_rechts); /*VORNE*/

    //Unten
    // 0
    VB.addNormal(boden_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(hinten_unten_rechts);
    // 1
    VB.addNormal(boden_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(hinten_unten_links);
    // 2
    VB.addNormal(boden_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(vorne_unten_links);
    // 3
    VB.addNormal(boden_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(vorne_unten_rechts);
    //Seite rechts_normal
    // 4
    VB.addNormal(rechts_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(hinten_oben_rechts);
    // 5
    VB.addNormal(rechts_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(hinten_oben_links);
    // 6
    VB.addNormal(rechts_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(hinten_unten_links);
    // 7
    VB.addNormal(rechts_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(hinten_unten_rechts);

    //Seite hinten_normal
    // 8
    VB.addNormal(hinten_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(hinten_oben_links);
    // 9
    VB.addNormal(hinten_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(vorne_oben_links);
    // 10
    VB.addNormal(hinten_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(vorne_unten_links);
    // 11
    VB.addNormal(hinten_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(hinten_unten_links);

    // Seite n
    //12
    VB.addNormal(links_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(vorne_oben_links);
    //13
    VB.addNormal(links_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(vorne_oben_rechts);
    //14
    VB.addNormal(links_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(vorne_unten_links);
    //15
    VB.addNormal(links_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(vorne_unten_rechts);

    //Oben o
    //16
    VB.addNormal(oben_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(hinten_oben_rechts);
    //17
    VB.addNormal(oben_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(hinten_oben_links);
    //18
    VB.addNormal(oben_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(vorne_oben_links);
    //19
    VB.addNormal(oben_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(vorne_oben_rechts);

    //Vorne p
    // 20
    VB.addNormal(vorne_normal);
    VB.addTexcoord0(1, 1);
    VB.addVertex(hinten_unten_rechts);
    // 21
    VB.addNormal(vorne_normal);
    VB.addTexcoord0(0, 1);
    VB.addVertex(vorne_unten_rechts);
    // 22
    VB.addNormal(vorne_normal);
    VB.addTexcoord0(0, 0);
    VB.addVertex(vorne_oben_rechts);
    // 23
    VB.addNormal(vorne_normal);
    VB.addTexcoord0(1, 0);
    VB.addVertex(hinten_oben_rechts);

    VB.end();

    IB.begin();
    //Unten boden_normal
    IB.addIndex(0);
    IB.addIndex(3);
    IB.addIndex(2);

    IB.addIndex(2);
    IB.addIndex(1);
    IB.addIndex(0);

    //Seite rechts_normal
    IB.addIndex(6);
    IB.addIndex(5);
    IB.addIndex(4);

    IB.addIndex(4);
    IB.addIndex(7);
    IB.addIndex(6);

    //Seite hinten_normal
    IB.addIndex(10);
    IB.addIndex(9);
    IB.addIndex(8);

    IB.addIndex(8);
    IB.addIndex(11);
    IB.addIndex(10);

    //Seite links_normal
    IB.addIndex(14);
    IB.addIndex(15);
    IB.addIndex(13);

    IB.addIndex(13);
    IB.addIndex(12);
    IB.addIndex(14);


    //Seite oben_normal
    IB.addIndex(18);
    IB.addIndex(19);
    IB.addIndex(16);

    IB.addIndex(16);
    IB.addIndex(17);
    IB.addIndex(18);

    //Seite vorne_normal
    IB.addIndex(23);
    IB.addIndex(22);
    IB.addIndex(21);

    IB.addIndex(21);
    IB.addIndex(20);
    IB.addIndex(23);

    IB.end();

    /* Old Hardcoded..
     *
     * VB.begin();
    // Jeder Vertex soll eine Normale haben.
    // Comments auf Miro beachten!

    //Fleache 1 - VORNE
    Vector vorne_v1(Width - 0, (-Height / 2) - (-Height / 2), 0 - 0);
    Vector vorne_v2(0 - 0, (Height / 2) - (-Height / 2), 0 - 0);
    Vector vorne = vorne_v1.cross(vorne_v2);

    //Fleache 2  - OBEN
    Vector oben_v1(Width - 0, (Height / 2) - (Height / 2), Depth - Depth);
    Vector oben_v2(0 - 0, (Height / 2) - (Height / 2), 0 - 0);
    Vector oben = oben_v1.cross(oben_v2);

    //Fleache 3 - RECHTS
    Vector rechts_v1(Width - Width, (Height / 2) - (Height / 2), Depth - 0);
    Vector rechts_v2(Width - Width, (-Height / 2) - (Height / 2), 0 - 0);
    Vector rechts = rechts_v1.cross(rechts_v2);

    //Fleache 4 - LINKS
    Vector links_v1(0 - 0, (-Height / 2) - (-Height / 2), Depth - 0);
    Vector links_v2(0 - 0, (Height / 2) - (-Height / 2), 0 - 0);
    Vector links = links_v1.cross(links_v2);

    //Fleache 5 - HINTEN
    Vector hinten_v1(0 - 0, (Height / 2) - (-Height / 2), Depth - Depth);
    Vector hinten_v2(Width - 0, (-Height / 2) - (-Height / 2), Depth - Depth);
    Vector hinten = hinten_v1.cross(hinten_v2);

    //Fleache 6 - UNTEN
    Vector unten_v1(Width - 0, (-Height / 2) - (-Height / 2), 0 - 0);
    Vector unten_v2(0 - 0, (-Height / 2) - (-Height / 2), Depth - 0);
    Vector unten = unten_v1.cross(unten_v2);

    //0
    VB.addNormal(vorne.X, vorne.Y, vorne.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(0, (-Height / 2), 0); // I = 0;
    VB.addNormal(links.X, links.Y, links.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(0, (-Height / 2), 0); // I = 1;
    VB.addNormal(unten.X, unten.Y, unten.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(0, (-Height / 2), 0); // I = 2;

    //1
    VB.addNormal(vorne.X, vorne.Y, vorne.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(0, (Height / 2), 0);  // I = 3;
    VB.addNormal(links.X, links.Y, links.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(0, (Height / 2), 0);  // I = 4;
    VB.addNormal(oben.X, oben.Y, oben.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(0, (Height / 2), 0);  // I = 5;

    //2
    VB.addNormal(vorne.X, vorne.Y, vorne.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(Width, (-Height / 2), 0); // I = 6;
    VB.addNormal(unten.X, unten.Y, unten.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(Width, (-Height / 2), 0); // I = 7;
    VB.addNormal(rechts.X, rechts.Y, rechts.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(Width, (-Height / 2), 0); // I = 8;

    //3
    VB.addNormal(vorne.X, vorne.Y, vorne.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(Width, (Height / 2), 0); // I = 9;
    VB.addNormal(rechts.X, rechts.Y, rechts.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(Width, (Height / 2), 0); // I = 10;
    VB.addNormal(oben.X, oben.Y, oben.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(Width, (Height / 2), 0); // I = 11;

    //4
    VB.addNormal(unten.X, unten.Y, unten.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(0, (-Height / 2), Depth); // I = 12;
    VB.addNormal(links.X, links.Y, links.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(0, (-Height / 2), Depth); // I = 13;
    VB.addNormal(hinten.X, hinten.Y, hinten.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(0, (-Height / 2), Depth); // I = 14;

    //5
    VB.addNormal(unten.X, unten.Y, unten.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(Width, (-Height / 2), Depth); // I = 15;
    VB.addNormal(hinten.X, hinten.Y, hinten.Z);
    VB.addTexcoord0(0, 1);
    VB.addVertex(Width, (-Height / 2), Depth); // I = 16;
    VB.addNormal(rechts.X, rechts.Y, rechts.Z);
    VB.addTexcoord0(1, 1);
    VB.addVertex(Width, (-Height / 2), Depth); // I = 17;

    //6
    VB.addNormal(hinten.X, hinten.Y, hinten.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(0, (Height / 2), Depth); // I = 18;
    VB.addNormal(links.X, links.Y, links.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(0, (Height / 2), Depth); // I = 19;
    VB.addNormal(oben.X, oben.Y, oben.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(0, (Height / 2), Depth); // I = 20;

    //7
    VB.addNormal(oben.X, oben.Y, oben.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(Width, (Height / 2), Depth); // I = 21;
    VB.addNormal(hinten.X, hinten.Y, hinten.Z);
    VB.addTexcoord0(0, 0);
    VB.addVertex(Width, (Height / 2), Depth); // I = 22;
    VB.addNormal(rechts.X, rechts.Y, rechts.Z);
    VB.addTexcoord0(1, 0);
    VB.addVertex(Width, (Height / 2), Depth); // I = 23;
    VB.end();

    IB.begin();

    // Die coords sind auf Miroboard aufgemalt worden

    // Vertexe Verbinden
    // Dreieck (front) erste haelfte
    IB.addIndex(0);
    IB.addIndex(3);
    IB.addIndex(9);

    // Dreieck (front) zweite haelfte
    IB.addIndex(0);
    IB.addIndex(9);
    IB.addIndex(6);

    // Dreieck (unten) erste haelfte
    IB.addIndex(7);
    IB.addIndex(15);
    IB.addIndex(2);

    // Dreieck (unten) erste haelfte
    IB.addIndex(15);
    IB.addIndex(12);
    IB.addIndex(2);

    // Dreieck (rechts) erste haelfte
    IB.addIndex(8);
    IB.addIndex(10);
    IB.addIndex(17);


    // Dreieck (rechts) zweite haelfte
    IB.addIndex(10);
    IB.addIndex(23);
    IB.addIndex(17);

    // Dreieck (oben) erste haelfte
    IB.addIndex(5);
    IB.addIndex(20);
    IB.addIndex(11);

    // Dreieck (oben) erste haelfte
    IB.addIndex(20);
    IB.addIndex(21);
    IB.addIndex(11);

    // Dreieck (links) erste haelfte
    IB.addIndex(19);
    IB.addIndex(4);
    IB.addIndex(1);

    // Dreieck (links) zweite haelfte
    IB.addIndex(13);
    IB.addIndex(19);
    IB.addIndex(1);

    // Dreieck (hinten) erste haelfte
    IB.addIndex(22);
    IB.addIndex(18);
    IB.addIndex(14);

    // Dreieck (hinten) zweite haelfte
    IB.addIndex(22);
    IB.addIndex(14);
    IB.addIndex(16);
    IB.end();*/
}

void TriangleBoxModel::draw(const BaseCamera &Cam) {
    //BaseModel::draw(Cam);

    // TODO: Add your code (Exercise 2)
    BaseModel::draw(Cam);

    VB.activate();
    IB.activate();

    glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);

    IB.deactivate();
    VB.deactivate();
}