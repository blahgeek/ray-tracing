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
    cerr << "Computing phong... View: ";
    view.print();
    Color ret(0, 0, 0);
    Number tmp;
    Object * target_obj = this->closestIntersection(view, tmp);
    if(target_obj == NULL){
        cerr << "No intersection. abort. \n";
        return ret;
    }
    view_reflect = target_obj->reflect(view, tmp);
    cerr << "Reflect View: ";
    view_reflect.print();
    cerr << "Reflect object: " ;
    target_obj->print();
    for(int i = 0 ; i < lights.size() ; i += 1){
        cerr << "Computing light #" << i << endl;
        Ray light_ray(lights[i], view_reflect.start - lights[i]);
        closestIntersection(light_ray, tmp);
        if(tmp == NOT_INTERSECT || 
                !isAlmostSame(light_ray.start+light_ray.direction * tmp, view_reflect.start)){
            cerr << "Not the same point or no intersection, continue." << endl;
            continue;
        }
        ret += target_obj->lambert(light_ray, tmp);
        Ray light_reflect = target_obj->reflect(light_ray, tmp);
        cerr << "Reflect light: " ;
        light_reflect.print();
        Number phong_term = light_reflect.direction.dot(-(view.direction));
        cerr << "cos a = " << phong_term << endl;
        if(phong_term <= 0){
            cerr << "<= 0, continue." << endl;
            continue;
        }
        phong_term = target_obj->specular_fact * pow(phong_term, target_obj->specular_power);
        phong_term *= view.intensity;
        cerr << "Phong Term = " << phong_term << endl;
        ret += phong_term * (target_obj->color);
    }
    return ret;
}
