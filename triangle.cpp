/// @file triangle.cpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com

#include "triangle.hpp"
#include "opencv2/core/core.hpp"
using cv::Mat;
using cv::Mat_;

Number Triangle::closestIntersection(Ray & ray){
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
        return this->closestIntersection(ray);
    }
    if(t < 0 || beta < 0 || beta > 1 ||
            gama < 0 || gama > 1 || beta + gama > 1)
        return NOT_INTERSECT;
    return t;
}

// [a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1]
Ray Triangle::reflect(const Ray & ray, Number t){
    Vec A = b - a;
    Vec B = c - a;
    Vec N(A.y*B.z - A.z*B.y, 
          A.z*B.x - A.x*B.z, 
          A.x*B.y - A.y*B.x);
    N = N * (1.0 / sqrt(N.dot(N)));
    Vec delta = ray.direction.dot(N) * N;
    return Ray(ray.start + ray.direction * t, 
            ray.direction - 2 * delta);
}
