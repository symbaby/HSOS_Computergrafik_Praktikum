#include <iostream>
#include "test/test1.h"
#include "test/test2.h"
#include "test/test3.h"
#include "include/color.h"
#include "include/vector.h"

using namespace std;

int main(int argc, const char *argv[]) {

    // uncomment the following functions to start the corresponding test routines
    Test1::vector();
    Test2::color();
    Test3::rgbimage("");

    //int num = 800 >> 2;
    //cout << num;

/*
    Color c;
    c.R = 3;
    c.G = 5;
    c.B = 34;
    cout << "Standardkonstruktor" << endl;
    cout << c << endl;

    Color c2(800, 3, 45);
    cout << "Mit Parameter" << endl;
    cout << c2 << endl;

    Color c3;
    c3 = c * c2;


    cout << "Faktor test" << endl;
    c = c * 10;
    cout << c << endl;


    cout << "Plus test" << endl;
    c = c + c;
    cout << c << endl;


    cout << "Plus gleich test" << endl;
    c += c;
    cout << c << endl;


    Vector v1(1, 2, 3);
    cout << v1 << endl;

    Vector v2(4, 5, 6);

    cout << "Length Test" << endl;
    cout << v1.length() << endl;

    cout << "Skalarprodukt Test" << endl;
    cout << v1.dot(v2)  << endl;

    cout << "Kreuzprodukt Test " << endl;
    Vector v3 = v1.cross(v2);
    cout << c3 << endl;


    cout << "Normalisieren Test" << endl;
    Vector v4 = v1.normalize();
    cout << v4 << endl;

*/
    return 0;

}