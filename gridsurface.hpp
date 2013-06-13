/// @file gridsurface.hpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com
#ifndef H_GRID_SURFACE
#define H_GRID_SURFACE

#include "triangle.hpp"
#include "object.hpp"
#include "common.hpp"

class GridSurface: public Object {
    public:
        Triangle tri;
        Vec diffuse0, diffuse1;
        Number grid_width;

        GridSurface(const Vec & a, const Vec & b, const Vec & c, 
                const Vec & _c0, const Vec & _c1, Number _w):
            tri(a, b, c, true), diffuse0(_c0), diffuse1(_c1), grid_width(_w){}
        Number closestIntersection(HandlingRay & h);
        void print() const;
        Vec getDiffuseFace(const Vec & p) const;
};

#endif

