/// @file gridsurface.cpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com

#include "object.hpp"
#include "common.hpp"
#include "gridsurface.hpp"

Number GridSurface::closestIntersection(HandlingRay & h){
    h.ray_t = tri.closestIntersection(h.ray);
    if(h.ray_t != NOT_INTERSECT){
        Vec p = h.ray.start + h.ray_t * h.ray.direction;
        h.law = Ray(p, tri.getLawVec(p));
    }
    return h.ray_t;
}

void GridSurface::print() const {
    return;
}

Vec GridSurface::getDiffuseFace(const Vec & p) const{
    Number tmp = (p.x + p.y + p.z) / grid_width;
    if(int(tmp) % 2) return diffuse0;
    return diffuse1;
}
