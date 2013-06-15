/// @file object.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "object.hpp"
#include "ray.hpp"
#include <iostream>
#include <cmath>
using std::cerr;
using std::endl;

Ray Object::reflect(HandlingRay & h){
    Vec delta = h.ray.direction.dot(h.law.direction) * h.law.direction;
    Ray ret(h.ray.start + h.ray.direction * h.ray_t, 
            h.ray.direction - 2 * delta);
    return ret;
}

Color Object::lambert(HandlingRay & h, const Color & light_color){
    Number theta = h.law.direction.dot(-h.ray.direction);
    if(theta < 0) theta = 0;
    Color ret = light_color * theta;
    ret.x *= getDiffuseFace(h.law.start).x;
    ret.y *= getDiffuseFace(h.law.start).y;
    ret.z *= getDiffuseFace(h.law.start).z;
    return ret;
}

Vec Object::getDiffuseFace(const Vec & p) const{
    return diffuse_fact;
}

Ray Object::refract(HandlingRay & h){
    Number t = (ALMOST_ZERO(h.ray.N - 1.0)?(1.0 / this->N):this->N);
    Number cos_theta = h.ray.direction.dot(h.law.direction);
    Vec law_dir = (cos_theta < 0 ? h.law.direction : -h.law.direction);
    Number cos_theta_sqr = pow(cos_theta, 2);
    Number cos_theta2_sqr = 1 - t * t * (1 - cos_theta_sqr);
    if(cos_theta2_sqr < 0) return h.ray;
    Vec dir = t * h.ray.direction + 
        (t * law_dir.dot(-h.ray.direction) - sqrt(cos_theta2_sqr)) * law_dir;
    Ray ret(h.law.start, dir);
    if(ALMOST_ZERO(h.ray.N - 1.0)) ret.N = this->N;
    else ret.N = 1.0;
    return ret;
}
