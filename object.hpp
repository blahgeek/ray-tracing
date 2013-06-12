/// @file object.hpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
#ifndef H_OBJECT_
#define H_OBJECT_

#include "common.hpp"
#include "geometry.hpp"
#include <vector>
using std::vector;

class Object{
    public:
        Color color;
        Number reflection_fact;
        Number specular_fact, specular_power;
        Object(const Color & _co):
            color(_co), reflection_fact(0.5), 
            specular_fact(1.0), specular_power(60.0){}

        Ray handling_ray;
        Number ray_t;
        Ray law;

        void handleRay(const Ray & ray);
        virtual Number closestIntersection() = 0;
        Ray reflect();

        virtual void print() const = 0;

        Color lambert();
};


#endif

