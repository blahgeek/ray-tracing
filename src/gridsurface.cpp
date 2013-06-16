/// @file gridsurface.cpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com

#include <cmath>
#include "object.hpp"
#include "common.hpp"
#include "gridsurface.hpp"

Vec GridSurface::getDiffuseFace(const Vec & p) const{
    Number a = remainder(p.x, 2 * grid_width);
    if(ALMOST_ZERO(a)) a = 0;
    Number b = remainder(p.z, 2 * grid_width);
    if(ALMOST_ZERO(b)) b = 0;
    if(a > 0 != b > 0) return diffuse0;
    return diffuse1;
}
