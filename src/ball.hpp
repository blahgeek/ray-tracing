/// @file ball.hpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
#ifndef H_BALL_
#define H_BALL_

#include "object.hpp"
#include "sphere.hpp"

class Ball: public Object{
    public:
        Sphere sphere;
        Ball(const Vec & _c, const Number _r):
            sphere(_c, _r){}
        Number closestIntersection(HandlingRay & h);
        void print() const ;
};

#endif

