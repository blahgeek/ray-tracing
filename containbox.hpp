/// @file containbox.hpp  @version 1.0 @date 06/15/2013
/// @author BlahGeek@Gmail.com
#ifndef H_CONTAIN_BOX
#define H_CONTAIN_BOX

#include <vector>
using std::vector;
#include "triangle.hpp"
#include "ray.hpp"


class ContainBox{
    public:
        static const int MaxElementNumber;

        vector<Triangle *> triangles;
        Vec start, size;
        ContainBox(const vector<Triangle *> _t);

        ContainBox * children[8];

        void split();
        void fitSize();

        bool isPassing(const Ray & ray);
        Number _intersect(Number p0, Number p, Number s);
        void _swap(Number & a, Number & b){
            Number tmp = a;
            a = b;
            b = tmp;
        }
};

#endif

