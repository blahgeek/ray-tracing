/// @file triangle.hpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com
#ifndef H_TRIANGLE_
#define H_TRIANGLE_

#include "geometry.hpp"

class Triangle: public Geometry{
    public:
        Vec a, b, c;
        bool infinity;

        Triangle(const Vec & _a, const Vec & _b, const Vec & _c, bool _i = false):
            a(_a), b(_b), c(_c), infinity(_i){}
        Number closestIntersection(Ray & ray);
        Number _closestIntersection(Ray & ray, int test_count = 0);
        Vec getLawVec(const Vec & p);
};

#endif

