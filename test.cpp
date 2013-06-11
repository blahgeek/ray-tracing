/// @file test.cpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
using namespace std;

#include "common.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "geometry.hpp"


int main ( int argc, char *argv[] )
{
    Geometry * ball = new Sphere(Vec(-1, -1, 1), 2);
    Ray ray(Vec(-1, -1, -1), Vec(1, 1, 1));
    cout << ball->closestIntersection(ray);
    return EXIT_SUCCESS;
}
