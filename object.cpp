/// @file object.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "object.hpp"
#include "ray.hpp"

Ray Object::reflect(HandlingRay & h){
    Vec delta = h.ray.direction.dot(h.law.direction) * h.law.direction;
    Ray ret(h.ray.start + h.ray.direction * h.ray_t, 
            h.ray.direction - 2 * delta);
    ret.intensity *= this->reflection_fact;
    return ret;
}

Color Object::lambert(HandlingRay & h, const Color & light_color, Number coef){
    Number theta = h.law.direction.dot(-h.ray.direction);
    if(theta < 0) theta = 0;
    Color ret = light_color * theta * coef;
    ret.x *= getDiffuseFace(h.law.start).x;
    ret.y *= getDiffuseFace(h.law.start).y;
    ret.z *= getDiffuseFace(h.law.start).z;
    return ret;
}

Vec Object::getDiffuseFace(const Vec & p) const{
    return diffuse_fact;
}
