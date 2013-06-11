/// @file scene.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com


#include "scene.hpp"
#include <iostream>
using namespace std;

Object * Scene::closestIntersection(Ray & ray, Number & ret_t){
    ret_t = NOT_INTERSECT;
    Object * ret = NULL;
    for(int i = 0 ; i < objects.size() ; i += 1){
        Number tmp = objects[i]->closestIntersection(ray);
        if(tmp != NOT_INTERSECT && (ret_t == NOT_INTERSECT || tmp < ret_t)){
            ret_t = tmp;
            ret = objects[i];
        }
    }
    return ret;
}

Color Scene::phong(Ray & view, Ray & view_reflect){
    Color ret(0, 0, 0);
    Number tmp;
    Object * target_obj = this->closestIntersection(view, tmp);
    if(target_obj == NULL) return ret;
    view_reflect = target_obj->reflect(view, tmp);
    for(int i = 0 ; i < lights.size() ; i += 1){
        Ray light_ray(lights[i], view_reflect.start - lights[i]);
        closestIntersection(light_ray, tmp);
        if(!isAlmostSame(light_ray.start+light_ray.direction * tmp, view_reflect.start))
            continue;
        Ray light_reflect = target_obj->reflect(light_ray, tmp);
        Number phong_term = light_reflect.direction.dot(-(view.direction));
        if(phong_term <= 0) continue;
        phong_term = target_obj->specular_fact * pow(phong_term, target_obj->specular_power);
        phong_term *= view.intensity;
        ret += phong_term * (target_obj->color);
    }
    return ret;
}
