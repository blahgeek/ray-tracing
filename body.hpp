/// @file body.hpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com
#ifndef H_BODY_
#define H_BODY_

#include "object.hpp"
#include "triangle.hpp"
#include <vector>
using std::vector;

class Body: public Object{
    public:
        vector<Triangle *> triangles;
        Body(vector<Triangle *> _t): triangles(_t){}
        Number closestIntersection();
        void print() const;
};

#endif

