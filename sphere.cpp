/// @file sphere.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com

#include "sphere.hpp"

Number Sphere::closestIntersection(Ray & ray){
    Vec l = this->center - ray.start;
    Number tp = l.dot(ray.direction);
    Number tmp = l.dot(l) - this->radius * this->radius;
    if(ALMOST_ZERO(tmp)){ // on the surface
        ray.start += ray.direction * EPSILON; // quick hack
        return this->closestIntersection(ray);
    }
    if(tmp > 0 && tp < 0) return NOT_INTERSECT;
    Number d2 = l.dot(l) - tp * tp;
    Number t_ = this->radius * this->radius - d2;
    if(t_ < 0) return NOT_INTERSECT;
    t_ = sqrt(t_);
    if(tmp > 0) return tp - t_;
    else return tp + t_;
}

Ray Sphere::reflect(const Ray & ray, Number t){
    Ray ret;
    ret.start = ray.start + ray.direction * t;
    Vec b = ret.start - this->center;
    b = b * (1.0 / sqrt(b.dot(b)));
    Vec delta = ray.direction.dot(b) * b;
    return Ray(ret.start, ray.direction - 2 * delta);
}

