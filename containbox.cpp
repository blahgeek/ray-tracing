/// @file containbox.cpp  @version 1.0 @date 06/15/2013
/// @author BlahGeek@Gmail.com


#include <vector>
#include <iostream>
using std::cerr;
using std::endl;
using std::vector;
#include "triangle.hpp"
#include <cstring>
#include <algorithm>
using std::sort;
using std::min_element;
using std::max_element;
#include "ray.hpp"
#include "containbox.hpp"

const int ContainBox::MaxElementNumber = 5;

static bool compareX(Triangle * a, Triangle * b){
    Number _a[] = {a->a.x, a->b.x, a->c.x};
    Number _b[] = {b->a.x, b->b.x, b->c.x};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}
static bool compareY(Triangle * a, Triangle * b){
    Number _a[] = {a->a.y, a->b.y, a->c.y};
    Number _b[] = {b->a.y, b->b.y, b->c.y};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}
static bool compareZ(Triangle * a, Triangle * b){
    Number _a[] = {a->a.z, a->b.z, a->c.z};
    Number _b[] = {b->a.z, b->b.z, b->c.z};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}

void ContainBox::split(){
    vector<Triangle *> x_dir[2];
    sort(triangles.begin(), triangles.end(), compareX);
    x_dir[0] = vector<Triangle *>(triangles.begin(), 
            triangles.begin() + (triangles.size() >> 1));
    x_dir[1] = vector<Triangle *>(triangles.begin() + 
            (triangles.size() >> 1), triangles.end());
    for(int x = 0 ; x < 2 ; x += 1){
        vector<Triangle *> y_dir[2];
        sort(x_dir[x].begin(), x_dir[x].end(), compareY);
        y_dir[0] = vector<Triangle *>(x_dir[x].begin(), 
                x_dir[x].begin() + (x_dir[x].size() >> 1));
        y_dir[1] = vector<Triangle *>(x_dir[x].begin() + 
                (x_dir[x].size() >> 1), x_dir[x].end());
        for(int y = 0 ; y < 2 ; y += 1){
            vector<Triangle *> z_dir[2];
            sort(y_dir[y].begin(), y_dir[y].end(), compareY);
            z_dir[0] = vector<Triangle *>(y_dir[y].begin(), 
                    y_dir[y].begin() + (y_dir[y].size() >> 1));
            z_dir[1] = vector<Triangle *>(y_dir[y].begin() + 
                    (y_dir[y].size() >> 1), y_dir[y].end());
            for(int z = 0 ; z < 2 ; z += 1)
                children[x * 4 + y * 2 + z] = 
                    new ContainBox(z_dir[z]);
        }
    }
    triangles.clear();
}

void ContainBox::fitSize(){
    if(triangles.empty()) return;
    vector<Number> nums;
    for(int i = 0 ; i < triangles.size() ; i += 1)
        for(int j = 0 ; j < 3 ; j += 1)
            nums.push_back((*triangles[i])[j].x);
    start.x = *min_element(nums.begin(), nums.end()) - EPSILON;
    size.x = (*max_element(nums.begin(), nums.end())) - start.x + EPSILON;
    nums.clear();
    for(int i = 0 ; i < triangles.size() ; i += 1)
        for(int j = 0 ; j < 3 ; j += 1)
            nums.push_back((*triangles[i])[j].y);
    start.y = *min_element(nums.begin(), nums.end()) - EPSILON;
    size.y = (*max_element(nums.begin(), nums.end())) - start.y + EPSILON;
    nums.clear();
    for(int i = 0 ; i < triangles.size() ; i += 1)
        for(int j = 0 ; j < 3 ; j += 1)
            nums.push_back((*triangles[i])[j].z);
    start.z = *min_element(nums.begin(), nums.end()) - EPSILON;
    size.z = (*max_element(nums.begin(), nums.end())) - start.z + EPSILON;
    nums.clear();
}

ContainBox::ContainBox(const vector<Triangle *> _t){
    triangles = _t;
    fitSize();
    if(triangles.size() > MaxElementNumber) split();
    else memset(children, 0, 8 * sizeof(ContainBox *));
}

Number ContainBox::_intersect(Number p0, Number p, Number s){
    if(p == 0) return NOT_INTERSECT;
    return (s - p0) / p;
}

bool ContainBox::isPassing(const Ray & ray){
    if(children[0] == NULL && triangles.empty()) return false;
    if(ray.start.x - start.x > -EPSILON && 
            ray.start.y - start.y > -EPSILON &&
            ray.start.z - start.z > -EPSILON &&
            ray.start.x - (start.x+size.x) < EPSILON &&
            ray.start.y - (start.y+size.y) < EPSILON &&
            ray.start.z - (start.z+size.z) < EPSILON)
        return true;
    Number mins[3];
    Number maxs[3];
    mins[0] = _intersect(ray.start.x, ray.direction.x, start.x);
    maxs[0] = _intersect(ray.start.x, ray.direction.x, start.x+size.x);
    if(mins[0] > maxs[0]) _swap(mins[0], maxs[0]);
    mins[1] = _intersect(ray.start.y, ray.direction.y, start.y);
    maxs[1] = _intersect(ray.start.y, ray.direction.y, start.y+size.y);
    if(mins[1] > maxs[1]) _swap(mins[1], maxs[1]);
    mins[2] = _intersect(ray.start.z, ray.direction.z, start.z);
    maxs[2] = _intersect(ray.start.z, ray.direction.z, start.z+size.z);
    if(mins[2] > maxs[2]) _swap(mins[2], maxs[2]);
    Number max_of_mins = * max_element(mins, mins+3);
    Number min_of_maxs = maxs[0];
    if(min_of_maxs == NOT_INTERSECT || 
            (maxs[1] != NOT_INTERSECT && maxs[1] < min_of_maxs))
        min_of_maxs = maxs[1];
    if(min_of_maxs == NOT_INTERSECT || 
            (maxs[2] != NOT_INTERSECT && maxs[2] < min_of_maxs))
        min_of_maxs = maxs[2];
    return max_of_mins <= min_of_maxs;
}
