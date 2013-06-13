/// @file surface.cpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com

#include <cmath>
#include "object.hpp"
#include "common.hpp"
#include "surface.hpp"

Number Surface::closestIntersection(HandlingRay & h){
    h.ray_t = tri.closestIntersection(h.ray);
    if(h.ray_t != NOT_INTERSECT){
        Vec p = h.ray.start + h.ray_t * h.ray.direction;
        h.law = Ray(p, tri.getLawVec(p));
    }
    return h.ray_t;
}

