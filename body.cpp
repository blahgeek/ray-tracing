/// @file body.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com


#include "body.hpp"
#include <queue>
using std::queue;

Number Body::closestIntersection(HandlingRay & h){
    queue<ContainBox *> possible_box;
    possible_box.push(box);
    vector<Triangle *> possible_triangle;
    while(! possible_box.empty()){
        ContainBox * current = possible_box.front();
        if(current->isPassing(h.ray)){
            if(current->children[0] != NULL){
                for(int i = 0 ; i < 8 ; i += 1)
                    possible_box.push(current->children[i]);
            }
            else for(int i = 0 ; i < current->triangles.size() ; i += 1)
                possible_triangle.push_back(current->triangles[i]);
        }
        possible_box.pop();
    }
    Triangle * target = NULL;
    h.ray_t = NOT_INTERSECT;
    for(int i = 0 ; i < possible_triangle.size() ; i += 1){
        Number t = possible_triangle[i]->closestIntersection(h.ray);
        if(t != NOT_INTERSECT && (h.ray_t == NOT_INTERSECT || t < h.ray_t)){
            h.ray_t = t;
            target = possible_triangle[i];
        }
    }
    if(target != NULL){
        Vec p = h.ray.start + h.ray_t * h.ray.direction;
        h.law = Ray(p, target->getLawVec(p));
    }
    return h.ray_t;
}

void Body::print() const {
    return;
}
