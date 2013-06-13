/// @file object.hpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
#ifndef H_OBJECT_
#define H_OBJECT_

#include "common.hpp"
#include "geometry.hpp"
#include <vector>
using std::vector;

struct HandlingRay {
    Ray ray;
    Number ray_t;
    Ray law;
    HandlingRay(const Ray & _r): ray(_r){}
    HandlingRay & operator = (const HandlingRay & a){
        ray = a.ray; ray_t = a.ray_t; law = a.law;
    }
};

class Object{
    public:
        Number N; // index of refraction
        Number reflection_fact, refraction_fact;
        Number specular_power;
        Vec specular_fact;
        Vec diffuse_fact;

        Object(): reflection_fact(0.5), N(1.2), refraction_fact(0.5), 
            specular_fact(Vec(1, 1, 1)), 
            specular_power(60.0), 
            diffuse_fact(1, 1, 1){}

        virtual Number closestIntersection(HandlingRay & h) = 0;
        virtual Vec getDiffuseFace(const Vec & p) const;
        Ray reflect(HandlingRay & h);
        Ray refract(HandlingRay & h);

        virtual void print() const = 0;

        Color lambert(HandlingRay & h, const Color & light_color);
};


#endif

