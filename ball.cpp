/// @file ball.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com

#include "ball.hpp"
#include <iostream>
#include <cmath>
using std::cerr;
using std::endl;

Ray Ball::reflect(const Ray & ray, Number t){
    Ray ret = this->sphere.reflect(ray, t);
    ret.intensity *= this->reflection_fact;
    return ret;
}

Number Ball::closestIntersection(Ray & ray){
    return sphere.closestIntersection(ray);
}

void Ball::print() const{
    cerr << "Center: (" << sphere.center.x << ", " << sphere.center.y 
        << ", " << sphere.center.z << "), Radius: " << sphere.radius << endl;
}

Color Ball::lambert(const Ray & ray, Number t){
    Vec p = ray.start + t * ray.direction;
    Vec n = p - sphere.center;
    n = n * (1.0 / sqrt(n.dot(n)));
    Number theta = n.dot(-ray.direction);
    if(theta < 0) theta = 0;
    return color * reflection_fact * theta;
}
