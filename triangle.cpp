/// @file triangle.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "triangle.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
using namespace std;
using cv::Mat;
using cv::Mat_;

Number Triangle::closestIntersection(Ray & ray){
    return _closestIntersection(ray);
}

Number Triangle::_closestIntersection(Ray & ray, int test_count){
    if(test_count > 2) return NOT_INTERSECT;
    Mat A = (Mat_<Number>(3, 3) <<
            ray.direction.x, a.x-b.x, a.x-c.x, 
            ray.direction.y, a.y-b.y, a.y-c.y, 
            ray.direction.z, a.z-b.z, a.z-c.z);
    Mat b = (Mat_<Number>(3, 1) << 
            a.x-ray.start.x, 
            a.y-ray.start.y, 
            a.z-ray.start.z);
    A = A.inv();
    Mat result = A * b;
    Number t = result.at<Number>(0, 0);
    Number beta = result.at<Number>(0, 1);
    Number gama = result.at<Number>(0, 2);
    if(ALMOST_ZERO(t)){ // on it
        ray.start += ray.direction * EPSILON; // quick hack
        return this->_closestIntersection(ray, test_count + 1);
    }
    if(t < 0 || ( !infinity && (beta < 0 || beta > 1 ||
            gama < 0 || gama > 1 || beta + gama > 1)))
        return NOT_INTERSECT;
    return t;
}

// [a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1]
Vec Triangle::getLawVec(const Vec & p){
    Vec A = b - a;
    Vec B = c - a;
    return Vec(A.y*B.z - A.z*B.y, 
          A.z*B.x - A.x*B.z, 
          A.x*B.y - A.y*B.x);
}

