/// @file object.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "object.hpp"
#include "ray.hpp"
#include <cmath>

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
    Number tmp = h.ray.direction.dot(h.law.direction);
    Vec shadow = tmp * h.law.direction;
    Number theta = acos(abs(tmp));
    Number sin_theta = sin(theta);
    Number sin_theta2 = ALMOST_ZERO(h.ray.N - 1.0) ? 
        (sin_theta / this->N) : (sin_theta * this->N);
    if(sin_theta2 >= 1) return Ray(h.ray);
    Vec ret_dir = shadow + (h.ray.direction - shadow) * 
        tan(asin(sin_theta2));
    Ray ret(h.law.start, ret_dir);
    ret.N = this->N;
    return ret;
}
