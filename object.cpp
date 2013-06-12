/// @file object.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "object.hpp"
#include "ray.hpp"

void Object::handleRay(const Ray & ray){
    handling_ray = ray;
}

Ray Object::reflect(){
    Vec delta = handling_ray.direction.dot(law.direction) * law.direction;
    Ray ret(handling_ray.start + handling_ray.direction * ray_t, 
            handling_ray.direction - 2 * delta);
    ret.intensity *= this->reflection_fact;
    return ret;
}

Color Object::lambert(){
    Number theta = law.direction.dot(-handling_ray.direction);
    if(theta < 0) theta = 0;
    return color * reflection_fact * theta;
}
