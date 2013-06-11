/// @file ball.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com

#include "ball.hpp"

Ray Ball::reflect(const Ray & ray, Number t){
    Ray ret = this->sphere.reflect(ray, t);
    ret.intensity *= this->reflection_fact;
    return ret;
}

Number Ball::closestIntersection(Ray & ray){
    return sphere.closestIntersection(ray);
}
