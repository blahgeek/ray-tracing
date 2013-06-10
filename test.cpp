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


int main ( int argc, char *argv[] )
{
    Sphere ball;
    ball.center = Vec(-1, -1, 1);
    ball.radius = 2;
    Ray ray;
    ray.start = Vec(-1, -1, -1);
    ray.direction = Vec(1, 1, 1);
    ray.direction = ray.direction * (1.0 / sqrt(ray.direction.dot(ray.direction)));
    cout << ray.closestIntersection(ball);
    return EXIT_SUCCESS;
}
