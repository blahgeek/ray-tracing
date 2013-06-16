/// @file ball.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com

#include "ball.hpp"
#include <iostream>
#include <cmath>
using std::cerr;
using std::endl;

Number Ball::closestIntersection(HandlingRay & h){
    h.ray_t = sphere.closestIntersection(h.ray);
    Vec point = h.ray.start + h.ray_t * h.ray.direction;
    h.law = Ray(point, sphere.getLawVec(point));
    return h.ray_t;
}

void Ball::print() const{
    cerr << "Center: (" << sphere.center.x << ", " << sphere.center.y 
        << ", " << sphere.center.z << "), Radius: " << sphere.radius << endl;
}
