/// @file scene.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com


#include "scene.hpp"
#include <iostream>
using namespace std;

Object * Scene::closestIntersection(HandlingRay & h){
    Number ret_t = NOT_INTERSECT;
    Object * ret = NULL;
    HandlingRay tmp_h = h;
    for(int i = 0 ; i < objects.size() ; i += 1){
        Number tmp = objects[i]->closestIntersection(tmp_h);
        if(tmp != NOT_INTERSECT && (ret_t == NOT_INTERSECT || tmp < ret_t)){
            ret_t = tmp;
            ret = objects[i];
            h = tmp_h;
        }
    }
    return ret;
}

Color Scene::phong(Ray & view, Ray & view_reflect, Number & coef){
    Number coef_orig = coef;
    Color ret(0, 0, 0);
    HandlingRay view_hr(view);
    Object * target_obj = this->closestIntersection(view_hr);
    if(target_obj == NULL) return ret;
    view_reflect = target_obj->reflect(view_hr);
    coef *= target_obj->reflection_fact;
    for(int i = 0 ; i < lights.size() ; i += 1){
        Ray light_ray(lights[i]->pos, view_reflect.start - lights[i]->pos);
        HandlingRay light_hr(light_ray);
        target_obj = closestIntersection(light_hr);
        if(target_obj == NULL || 
                !isAlmostSame(light_hr.law.start, view_reflect.start))
            continue;
        ret += target_obj->lambert(light_hr, lights[i]->color);
        Ray light_reflect = target_obj->reflect(light_hr);
        Number phong_term = light_reflect.direction.dot(-(view.direction));
        if(phong_term <= 0) continue;
        phong_term = pow(phong_term, target_obj->specular_power) ;
        Color add_color = phong_term * (lights[i]->color);
        add_color.x *= target_obj->specular_fact.x;
        add_color.y *= target_obj->specular_fact.y;
        add_color.z *= target_obj->specular_fact.z;
        ret += add_color;
    }
    return ret * coef_orig;
}
