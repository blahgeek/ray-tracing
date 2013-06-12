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


int main ( int argc, char *argv[] )
{
    Scene scene;

    Object * ball_0 = new Ball(Vec(233, 290, 0), 100);
    ball_0->diffuse_fact = Vec(1, 1, 0);
    scene.objects.push_back(ball_0);

    Object * ball_1 = new Ball(Vec(407, 290, 0), 100);
    ball_1->diffuse_fact = Vec(0, 1, 1);
    scene.objects.push_back(ball_1);

    Object * ball_2 = new Ball(Vec(320, 140, 0), 100);
    ball_2->diffuse_fact = Vec(1, 0, 1);
    scene.objects.push_back(ball_2);

    vector<Triangle *> trs;
    trs.push_back(new Triangle(
                Vec(-1000, 480, -1000), Vec(5000, 480, 1000), Vec(300, -1000, 8000)));
    Object * bd = new Body(trs);
    bd->diffuse_fact = Vec(1, 1, 1);
    bd->specular_fact = Vec(1, 1, 1);
    bd->reflection_fact = 0.9;
    bd->specular_power = 10;
    scene.objects.push_back(bd);
    
    scene.lights.push_back(new Light(Vec(0, 240, -100), Color(255, 255, 255)));
    scene.lights.push_back(new Light(Vec(640, 240, -10000), Color(180, 200, 255)));

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
