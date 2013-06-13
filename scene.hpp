/// @file scene.hpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
#ifndef H_SCENE_
#define H_SCENE_

#include "common.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "light.hpp"
#include <vector>
using std::vector;

class Scene{
    public:
        vector<Object *> objects;
        vector<Light *> lights;

        Object * closestIntersection(HandlingRay & h);
        Color phong(RayWithCoef & view, RayWithCoef & view_reflect, RayWithCoef & view_refract);

};

#endif

