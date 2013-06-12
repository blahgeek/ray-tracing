/// @file test.cpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;

#include "common.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "geometry.hpp"
#include "scene.hpp"
#include "PngOutput.h"
#include "ball.hpp"


int main ( int argc, char *argv[] )
{
    Scene scene;

    scene.objects.push_back(new Ball(Vec(233, 290, 0), 100, Color(255, 255, 0)));
    scene.objects.push_back(new Ball(Vec(407, 290, 0), 100, Color(255, 0, 255)));
    scene.objects.push_back(new Ball(Vec(320, 140, 0), 100, Color(0, 0, 255)));
    
    scene.lights.push_back(Vec(0, 240, -100));
    scene.lights.push_back(Vec(640, 240, -10000));

    PngOutput * out = new PngOutput(640, 480, "test.png");

    Vec view_point(320, 240, -1000);
    for(int i = 0 ; i < 640 ; i += 1){
        cerr << i << endl;
        for(int j = 0 ; j < 480 ; j += 1){
//            if(!(i == 263 && j == 185)) continue;
            Ray view(view_point, Vec(i, j, 0) - view_point);
            Ray view_reflect(view);
            Color color(0, 0, 0);
            for(int t = 0 ; t < 10 ; t += 1){
                if(ALMOST_ZERO(view.intensity)) break;
                color += scene.phong(view, view_reflect);
                if(isAlmostSame(view.start, view_reflect.start)) break;
                view = view_reflect;
            }
            out->draw(i, j, color);
        }
    }
    out->finish();

    return EXIT_SUCCESS;
}
