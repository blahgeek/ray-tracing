/// @file ray.cpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com

#include "ray.hpp"
#include <cmath>

Number Ray::closestIntersection(const Sphere & ball){
    Vec l = ball.center - this->start;
    Number tp = l.dot(this->direction);
    Number tmp = l.dot(l) - ball.radius * ball.radius;
    if(tmp > -EPSILON && tmp < EPSILON){ // on the surface
        start += direction * EPSILON; // quick hack
        return this->closestIntersection(ball);
    }
    if(tmp > 0 && tp < 0) return NOT_INTERSECT;
    Number d2 = l.dot(l) - tp * tp;
    Number t_ = ball.radius * ball.radius - d2;
    if(t_ < 0) return NOT_INTERSECT;
    t_ = sqrt(t_);
    if(tmp > 0) return tp - t_;
    else return tp + t_;
}

Ray Ray::reflect(const Sphere & ball, Number t){
    Ray ret;
    ret.start = this->start + this->direction * t;
    Vec b = ret.start - ball.center;
    b = b * (1.0 / sqrt(b.dot(b)));
    Vec delta = this->direction.dot(b) * b;
    ret.direction = this->direction - 2 * delta;
    return ret;
}
