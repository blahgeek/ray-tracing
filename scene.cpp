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
        Ray light_ray(lights[i]->pos, view_reflect.start - lights[i]->pos);
        target_obj = closestIntersection(light_ray);
        if(target_obj == NULL || 
                !isAlmostSame(target_obj->law.start, view_reflect.start))
            continue;
        ret += target_obj->lambert(lights[i]->color, view.intensity);
        Ray light_reflect = target_obj->reflect();
        Number phong_term = light_reflect.direction.dot(-(view.direction));
        if(phong_term <= 0) continue;
        phong_term = pow(phong_term, target_obj->specular_power) * view.intensity;
        Color add_color = phong_term * (lights[i]->color);
        add_color.x *= target_obj->specular_fact.x;
        add_color.y *= target_obj->specular_fact.y;
        add_color.z *= target_obj->specular_fact.z;
        ret += add_color;
    }
    return ret;
}
