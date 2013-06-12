/// @file ball.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com

#include "ball.hpp"
#include <iostream>
#include <cmath>
using std::cerr;
using std::endl;

Number Ball::closestIntersection(){
    this->ray_t = sphere.closestIntersection(handling_ray);
    Vec point = handling_ray.start + ray_t * handling_ray.direction;
    law = Ray(point, sphere.getLawVec(point));
    return this->ray_t;
}

void Ball::print() const{
    cerr << "Center: (" << sphere.center.x << ", " << sphere.center.y 
        << ", " << sphere.center.z << "), Radius: " << sphere.radius << endl;
}
