/// @file ray.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
//
#include "ray.hpp"
#include <iostream>
using namespace std;

bool isAlmostSame(const Vec & a, const Vec & b){
    if(ALMOST_ZERO(a.x-b.x) && ALMOST_ZERO(a.y-b.y) && ALMOST_ZERO(a.z-b.z))
        return true;
    return false;
}

Ray & Ray::operator = (const Ray & r){
    start = r.start;
    direction = r.direction;
    intensity = r.intensity;
    return *this;
}

void Ray::print() const {
    cerr << "(" << start.x << ", " << start.y << ", " << start.z << ") -> ("
        << direction.x << ", " << direction.y << ", " << direction.z << ")\n";
}
