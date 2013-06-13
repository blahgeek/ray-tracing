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

    Object * ball_0 = new Ball(Vec(233, 380, 300), 100);
    ball_0->diffuse_fact = Vec(0.1, 0.1, 0);
    ball_0->specular_power = 1000;
    ball_0->reflection_fact = 0.05;
    ball_0->refraction_fact = 0.95;
    scene.objects.push_back(ball_0);

    Object * ball_1 = new Ball(Vec(407, 380, 300), 100);
    ball_1->diffuse_fact = Vec(0, 1, 1);
    scene.objects.push_back(ball_1);

    Object * ball_2 = new Ball(Vec(320, 230, 300), 100);
    ball_2->diffuse_fact = Vec(1, 0, 1);
    scene.objects.push_back(ball_2);

    Object * bd = new GridSurface(
                Vec(-1000, 480, -1000), Vec(5000, 480, 1000), Vec(300, 480, 8000), 
                Vec(1, 1, 1), Vec(0, 0, 0), 60);
    bd->specular_fact = Vec(1, 1, 1);
    bd->reflection_fact = 0.6;
    bd->specular_power = 10;
    bd->refraction_fact = 0;
    scene.objects.push_back(bd);

    Object * img_sf = new ImageSurface(
                Vec(-400, -300, 1000), Vec(-400, -299, 1000), Vec(-399, -300, 1000), "/mnt/data/Pictures/background/galaxy.jpg");
    img_sf->refraction_fact = 0;
    img_sf->reflection_fact = 0;
    img_sf->specular_power = 10;
    img_sf->specular_fact = Vec(0.5, 0.5, 0.5);
    scene.objects.push_back(img_sf);
    
    scene.lights.push_back(new Light(Vec(0, 240, -100), Color(255, 255, 255)));
    scene.lights.push_back(new Light(Vec(640, 240, -10000), Color(180, 200, 255)));

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
                if(view.second < 1e-3) continue;
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
