/// @file body.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com


#include "body.hpp"

Number Body::closestIntersection(HandlingRay & h){
    Triangle * target = NULL;
    h.ray_t = NOT_INTERSECT;
    for(int i = 0 ; i < triangles.size() ; i += 1){
        Number t = triangles[i]->closestIntersection(h.ray);
        if(t != NOT_INTERSECT && (h.ray_t == NOT_INTERSECT || t < h.ray_t)){
            h.ray_t = t;
            target = triangles[i];
        }
    }
    if(target != NULL){
        Vec p = h.ray.start + h.ray_t * h.ray.direction;
        h.law = Ray(p, target->getLawVec(p));
    }
    return h.ray_t;
}

void Body::print() const {
    return;
}
