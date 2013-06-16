/// @file sphere.hpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com
/// @brief Class for sphere
#ifndef H_SPHERE_
#define H_SPHERE_

#include "common.hpp"
#include "geometry.hpp"

class Sphere: public Geometry{
    public:
        Vec center;
        Number radius;
        Sphere(const Vec & _c, const Number _r):
            center(_c), radius(_r){}
        Number closestIntersection(Ray & ray);
        Vec getLawVec(const Vec & p);
};

#endif

