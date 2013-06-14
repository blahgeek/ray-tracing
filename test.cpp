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
#include "object.hpp"
#include "PngOutput.h"
#include "ball.hpp"
#include "light.hpp"
#include "body.hpp"
#include "imagesurface.hpp"
#include "gridsurface.hpp"


int main ( int argc, char *argv[] )
{
    Scene scene;
    scene.loadFromJson(argv[1]);

    PngOutput * out = new PngOutput(640, 480, "test.png");

    Vec view_point(320, 240, -1000);
#pragma omp parallel for schedule(dynamic)
    for(int i = 0 ; i < 640 ; i += 1){
        cerr << i << endl;
        for(int j = 0 ; j < 480 ; j += 1){
            Color color(0, 0, 0);
            vector<RayWithCoef> views;
            views.push_back(RayWithCoef(Ray(view_point, Vec(i, j, 0) - view_point), 1.0));
            while(!views.empty()){
                RayWithCoef view = views.back();
                views.pop_back();
                RayWithCoef view_reflect(view);
                RayWithCoef view_refract(view);
                if(view.second < 1e-2) continue;
                color += scene.phong(view, view_reflect, view_refract);
                if(!isAlmostSame(view.first.start, view_reflect.first.start))
                    views.push_back(view_reflect);
                if(!isAlmostSame(view.first.start, view_refract.first.start))
                    views.push_back(view_refract);
            }
            out->draw(i, j, color);
        }
    }
    out->finish();

    return EXIT_SUCCESS;
}
