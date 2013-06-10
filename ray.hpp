/// @file ray.hpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com
/// @brief Class for a ray, = p + t * u
#ifndef H_RAY_
#define H_RAY_

#include "common.hpp"
#include "sphere.hpp"

class Ray{
    public:
        Vec start, direction;
        Number closestIntersection(const Sphere & ball);
        Ray reflect(const Sphere & ball, Number t);
};

#endif

