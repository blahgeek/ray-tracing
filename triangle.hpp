/// @file triangle.hpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com
#ifndef H_TRIANGLE_
#define H_TRIANGLE_

#include "geometry.hpp"

class Triangle: public Geometry{
    public:
        Vec a, b, c;

        Triangle(const Vec & _a, const Vec & _b, const Vec & _c):
            a(_a), b(_b), c(_c){}
        Number closestIntersection(Ray & ray);
        Ray reflect(const Ray & ray, Number t);
};

#endif

