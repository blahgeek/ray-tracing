/// @file scene.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com


#include "scene.hpp"
#include <iostream>
using namespace std;

Object * Scene::closestIntersection(Ray & ray){
    Number ret_t = NOT_INTERSECT;
    Object * ret = NULL;
    for(int i = 0 ; i < objects.size() ; i += 1){
        objects[i]->handleRay(ray);
        Number tmp = objects[i]->closestIntersection();
        if(tmp != NOT_INTERSECT && (ret_t == NOT_INTERSECT || tmp < ret_t)){
            ret_t = tmp;
            ret = objects[i];
        }
    }
    return ret;
}

Color Scene::phong(Ray & view, Ray & view_reflect){
    Color ret(0, 0, 0);
    Object * target_obj = this->closestIntersection(view);
    if(target_obj == NULL) return ret;
    view_reflect = target_obj->reflect();
    for(int i = 0 ; i < lights.size() ; i += 1){
        Ray light_ray(lights[i], view_reflect.start - lights[i]);
        target_obj = closestIntersection(light_ray);
        if(target_obj == NULL || 
                !isAlmostSame(target_obj->law.start, view_reflect.start))
            continue;
        ret += target_obj->lambert();
        Ray light_reflect = target_obj->reflect();
        Number phong_term = light_reflect.direction.dot(-(view.direction));
        if(phong_term <= 0) continue;
        phong_term = target_obj->specular_fact * pow(phong_term, target_obj->specular_power);
        phong_term *= view.intensity;
        ret += phong_term * (target_obj->color);
    }
    return ret;
}
