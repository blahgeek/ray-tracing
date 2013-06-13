/// @file surface.hpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com
#ifndef H_SURFACE_
#define H_SURFACE_

#include "triangle.hpp"
#include "object.hpp"
#include "common.hpp"

class Surface: public Object {
    public:
        Triangle tri;

        Surface(const Vec & a, const Vec & b, const Vec & c):
            tri(a, b, c, true){}
        Number closestIntersection(HandlingRay & h);
        void print() const {return;}
};

#endif

