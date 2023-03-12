//
//  TriangleBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "TriangleBoxModel.h"

TriangleBoxModel::TriangleBoxModel(float Width, float Height, float Depth)
{

	// TODO: Add your code (Exercise 2)
	VB.begin();

	/*
	VB.addNormal(0, 1, 0);
	VB.addVertex(base, -Height / 2, base);
	VB.addVertex(base, Height / 2, base);
	VB.addVertex(base + Width, -Height / 2, base);
	VB.addVertex(base + Width, +Height / 2, base);
	*/

	// Jeder Vertex soll eine Normale haben.
	// Comments auf Miro beachten!
	VB.addNormal(0, 1, 0);
	VB.addTexcoord1(0, 0);
	VB.addVertex(0, (-Height / 2), 0); // I = 0;

	VB.addNormal(0, 1, 0);
	VB.addTexcoord1(0, 1);
	VB.addVertex(0, (Height / 2), 0);  // I = 1;

	VB.addNormal(0, 1, 0);
	VB.addTexcoord1(1, 1);
	VB.addVertex(Width, (-Height / 2), 0); // I = 2;

	VB.addNormal(0, 1, 0);
	VB.addTexcoord1(1, 0);
	VB.addVertex(Width, (Height / 2), 0); // I = 3;


	VB.addVertex(0, (-Height / 2), Depth); // I = 4;
	VB.addVertex(Width, (-Height / 2), Depth); // I = 5;
	VB.addVertex(0, (Height / 2), Depth); // I = 6;
	VB.addVertex(Width, (Height / 2), Depth); // I = 7;

	VB.end();

	// Am ende die Vertice

	IB.begin();

	// Die coords sind auf Miroboard aufgemalt worden

	// Vertexe Verbinden
	// erstes Dreieck (front) erste haelfte
	
	IB.addIndex(0);
	IB.addIndex(1);
	IB.addIndex(2);

	// zweites Dreieck (front) zweite haelfte
	IB.addIndex(1);
	IB.addIndex(3);
	IB.addIndex(2);

	// drittes Dreieck (Unten) erste haelfte
	// 1x flippen
	IB.addIndex(2);
	IB.addIndex(4);
	IB.addIndex(0);

	// viertes Dreieck (Unten) zweite haelfte
	// 1x flippen
	IB.addIndex(5);
	IB.addIndex(4);
	IB.addIndex(2);

	// fuenftes Dreieck (Oben) erste haelfte
	IB.addIndex(1);
	IB.addIndex(6);
	IB.addIndex(3);

	// sechstes Dreieck (Oben) zweite haelfte
	IB.addIndex(3);
	IB.addIndex(6);
	IB.addIndex(7);

	// siebtes Dreieck (hinten) erste haelfte
	// 1x flippen
	IB.addIndex(5);
	IB.addIndex(6);
	IB.addIndex(4);

	// achtes Dreieck (hinten) erste haelfte
	// 1x flippen
	IB.addIndex(5);
	IB.addIndex(6);
	IB.addIndex(4);

	// achtes Dreieck (hinten) zweite haelfte
	// 1x flippen
	IB.addIndex(7);
	IB.addIndex(6);
	IB.addIndex(5);

	// neuntes Dreieck (rechts) erste haelfte
	IB.addIndex(2);
	IB.addIndex(3);
	IB.addIndex(5);

	// zehntes Dreieck (rechts) zweite haelfte
	IB.addIndex(3);
	IB.addIndex(7);
	IB.addIndex(5);
	
	// elftes Dreieck (links) erste haelfte
	// 1x flippen
	IB.addIndex(4);
	IB.addIndex(1);
	IB.addIndex(0);

	// zwoelftes Dreieck (links) zweite haelfte
	// 1x flippen
	IB.addIndex(4);
	IB.addIndex(6);
	IB.addIndex(1);
	






	IB.end();

}

void TriangleBoxModel::draw(const BaseCamera& Cam)
{
	//BaseModel::draw(Cam);

	// TODO: Add your code (Exercise 2)
	BaseModel::draw(Cam);

	VB.activate();
	IB.activate();

	glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);

	IB.deactivate();
	VB.deactivate();
}