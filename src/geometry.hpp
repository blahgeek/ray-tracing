/// @file geometry.hpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
#ifndef H_GEOMETRY_
#define H_GEOMETRY_

#include "common.hpp"
#include "ray.hpp"

class Geometry{
    public:
        virtual Number closestIntersection(Ray & ray) = 0;
        virtual Vec getLawVec(const Vec & p) = 0;
};

#endif

