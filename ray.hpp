/// @file ray.hpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com
/// @brief Class for a ray, = p + t * u
#ifndef H_RAY_
#define H_RAY_

#include "common.hpp"
#include <cmath>

class Ray{
    public:
        Vec start, direction;
        Ray(const Vec & _s, const Vec & _d):
            start(_s), direction(_d * (1.0 / sqrt(_d.dot(_d)))){}
        Ray(){}
};

#endif

