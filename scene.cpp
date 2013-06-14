/// @file scene.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com


#include "scene.hpp"
#include "ball.hpp"
#include "triangle.hpp"
#include "gridsurface.hpp"
#include "imagesurface.hpp"
#include "body.hpp"
#include "jsonxx.h"
#include <vector>
#include <fstream>
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

Color Scene::phong(RayWithCoef & view, RayWithCoef & view_reflect, RayWithCoef & view_refract){
    Color ret(0, 0, 0);
    HandlingRay view_hr(view.first);
    Object * target_obj = this->closestIntersection(view_hr);
    if(target_obj == NULL) return ret;
    view_reflect.first = target_obj->reflect(view_hr);
    view_reflect.second = view.second * target_obj->reflection_fact;
    view_refract.first = target_obj->refract(view_hr);
    view_refract.second = view.second * target_obj->refraction_fact;
    for(int i = 0 ; i < lights.size() ; i += 1){
        Ray light_ray(lights[i]->pos, view_reflect.first.start - lights[i]->pos);
        HandlingRay light_hr(light_ray);
        target_obj = closestIntersection(light_hr);
        if(target_obj == NULL || 
                !isAlmostSame(light_hr.law.start, view_reflect.first.start))
            continue;
        ret += target_obj->lambert(light_hr, lights[i]->color);
        Ray light_reflect = target_obj->reflect(light_hr);
        Number phong_term = light_reflect.direction.dot(-(view.first.direction));
        if(phong_term <= 0) continue;
        phong_term = pow(phong_term, target_obj->specular_power) ;
        Color add_color = phong_term * (lights[i]->color);
        add_color.x *= target_obj->specular_fact.x;
        add_color.y *= target_obj->specular_fact.y;
        add_color.z *= target_obj->specular_fact.z;
        ret += add_color;
    }
    return ret * view.second;
}

void Scene::loadFromJson(const char * filename){
    objects.clear();
    lights.clear();
    ifstream fin(filename);
    json.parse(fin);
    // objects
    assert(json.has<jsonxx::Array>("objects"));
    jsonxx::Array _objs = json.get<jsonxx::Array>("objects");
    for(int i = 0 ; i < _objs.size() ; i += 1){
        Object * obj = NULL;
        jsonxx::Object _obj = _objs.get<jsonxx::Object>(i);
        assert(_obj.has<jsonxx::String>("type"));
        jsonxx::String _type = _obj.get<jsonxx::String>("type");
        if(_type == "Ball"){
            assert(_obj.has<jsonxx::Array>("center"));
            assert(_obj.has<jsonxx::Number>("radius"));
            obj = new Ball(
                    arrayToVec(_obj.get<jsonxx::Array>("center")), 
                    _obj.get<jsonxx::Number>("radius")
                    );
        }
        if(_type == "GridSurface"){
            assert(_obj.has<jsonxx::Array>("triangle"));
            assert(_obj.has<jsonxx::Array>("colors"));
            assert(_obj.has<jsonxx::Number>("grid_width"));
            jsonxx::Array _tri = _obj.get<jsonxx::Array>("triangle");
            jsonxx::Array _co = _obj.get<jsonxx::Array>("colors");
            obj = new GridSurface(
                    arrayToVec(_tri.get<jsonxx::Array>(0)), 
                    arrayToVec(_tri.get<jsonxx::Array>(1)), 
                    arrayToVec(_tri.get<jsonxx::Array>(2)), 
                    arrayToVec(_co.get<jsonxx::Array>(0)), 
                    arrayToVec(_co.get<jsonxx::Array>(1)), 
                    _obj.get<jsonxx::Number>("grid_width")
                    );
        }
        if(_type == "Body"){
            assert(_obj.has<jsonxx::Array>("triangles"));
            vector<Triangle *> tris;
            jsonxx::Array _tris = _obj.get<jsonxx::Array>("triangles");
            for(int j = 0 ; j < _tris.size() ; j += 1)
                tris.push_back(arrayToTriangleStar(_tris.get<jsonxx::Array>(j)));
            obj = new Body(tris);
        }
        if(_type == "ImageSurface"){
            assert(_obj.has<jsonxx::Array>("triangle"));
            assert(_obj.has<jsonxx::String>("img"));
            jsonxx::Array _tri = _obj.get<jsonxx::Array>("triangle");
            obj = new ImageSurface(
                    arrayToVec(_tri.get<jsonxx::Array>(0)), 
                    arrayToVec(_tri.get<jsonxx::Array>(1)), 
                    arrayToVec(_tri.get<jsonxx::Array>(2)), 
                    _obj.get<jsonxx::String>("img").c_str()
                    );
        }
        if(obj == NULL) continue;
        
        if(_obj.has<jsonxx::Number>("N"))
            obj->N = _obj.get<jsonxx::Number>("N");
        if(_obj.has<jsonxx::Number>("reflection_fact"))
            obj->reflection_fact = _obj.get<jsonxx::Number>("reflection_fact");
        if(_obj.has<jsonxx::Number>("refraction_fact"))
            obj->refraction_fact = _obj.get<jsonxx::Number>("refraction_fact");
        if(_obj.has<jsonxx::Number>("specular_power"))
            obj->specular_power = _obj.get<jsonxx::Number>("specular_power");
        if(_obj.has<jsonxx::Array>("specular_fact"))
            obj->specular_fact = arrayToVec(_obj.get<jsonxx::Array>("specular_fact"));
        if(_obj.has<jsonxx::Array>("diffuse_fact"))
            obj->diffuse_fact = arrayToVec(_obj.get<jsonxx::Array>("diffuse_fact"));
        this->objects.push_back(obj);
    }
    // lights
    assert(json.has<jsonxx::Array>("lights"));
    jsonxx::Array _ligs = json.get<jsonxx::Array>("lights");
    for(int i = 0 ; i < _ligs.size() ; i += 1){
        jsonxx::Object _lig = _ligs.get<jsonxx::Object>(i);
        this->lights.push_back(new Light(
                    arrayToVec(_lig.get<jsonxx::Array>("point")), 
                    arrayToVec(_lig.get<jsonxx::Array>("color"))
                    ));
    }
}

Vec Scene::arrayToVec(const jsonxx::Array & a){
    Vec ret;
    ret.x = a.get<jsonxx::Number>(0);
    ret.y = a.get<jsonxx::Number>(1);
    ret.z = a.get<jsonxx::Number>(2);
    return ret;
}

Triangle * Scene::arrayToTriangleStar(const jsonxx::Array & a){
    Triangle * tri = new Triangle;
    assert(json.has<jsonxx::Object>("points"));
    jsonxx::Object points = json.get<jsonxx::Object>("points");
    for(int i = 0 ; i < 3 ; i += 1){
        if(a.has<jsonxx::Array>(i))
            (*tri)[i] = arrayToVec(a.get<jsonxx::Array>(i));
        else{
            jsonxx::String tmp = a.get<jsonxx::String>(i);
            assert(points.has<jsonxx::Array>(tmp));
            (*tri)[i] = arrayToVec(points.get<jsonxx::Array>(tmp));
        }
    }
    return tri;
}
