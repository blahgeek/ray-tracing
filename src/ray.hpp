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
        Number N; // index of refraction
        Ray(const Vec & _s, const Vec & _d):
            N(1.0), 
            start(_s), direction(_d * (1.0 / sqrt(_d.dot(_d)))){}
        Ray(): N(1.0) {}
        Ray(const Ray & r): N(1.0), start(r.start), direction(r.direction){}
        Ray & operator = (const Ray & r);
        void print() const;
};

#include <utility>
typedef std::pair<Ray, Number> RayWithCoef;

bool isAlmostSame(const Vec & a, const Vec & b);

#endif

