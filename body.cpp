/// @file body.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com


#include "body.hpp"

Number Body::closestIntersection(){
    Triangle * target = NULL;
    ray_t = NOT_INTERSECT;
    for(int i = 0 ; i < triangles.size() ; i += 1){
        Number t = triangles[i]->closestIntersection(handling_ray);
        if(t != NOT_INTERSECT && (ray_t == NOT_INTERSECT || t < ray_t)){
            ray_t = t;
            target = triangles[i];
        }
    }
    if(target != NULL){
        Vec p = handling_ray.start + ray_t * handling_ray.direction;
        law = Ray(p, target->getLawVec(p));
    }
    return ray_t;
}

void Body::print() const {
    return;
}
