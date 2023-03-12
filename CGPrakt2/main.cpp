#include <iostream>
#include "test/test1.h"
#include "test/test2.h"
#include "test/test3.h"
#include "include/color.h"
#include "include/vector.h"
#include "include/rgbimage.h"
#include "include/SimpleRayTracer.h"


using namespace std;

int main(int argc, const char *argv[]) {

    // uncomment the following functions to start the corresponding test routines
    // Test1::vector();
    // Test2::color();
    // Test3::rgbimage("");


    Scene scene(20);
    RGBImage image(640, 480);
    SimpleRayTracer tracer(2);
    tracer.traceScene(scene, image);
    image.saveToDisk("raytracing_image.bmp");

    std::cout << "cock " << std::endl;


    return 0;


}