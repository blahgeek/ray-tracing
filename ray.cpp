/// @file ray.cpp  @version 1.0 @date 06/11/2013
/// @author BlahGeek@Gmail.com
//
#include "ray.hpp"

bool isAlmostSame(const Vec & a, const Vec & b){
    if(ALMOST_ZERO(a.x-b.x) && ALMOST_ZERO(a.y-b.y) && ALMOST_ZERO(a.z-b.z))
        return true;
    return false;
}

