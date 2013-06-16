/// @file body.hpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com
#ifndef H_BODY_
#define H_BODY_

#include "object.hpp"
#include "triangle.hpp"
#include "containbox.hpp"
#include <vector>
using std::vector;

class Body: public Object{
    public:
        ContainBox * box;
        Body(vector<Triangle *> _t): 
            box(new ContainBox(_t)){}
        Number closestIntersection(HandlingRay & h);
        void print() const;
};

#endif

