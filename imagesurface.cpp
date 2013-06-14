/// @file imagesurface.cpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com

#include "triangle.hpp"
#include "object.hpp"
#include "common.hpp"
#include "imagesurface.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using std::cerr;
using std::endl;
using cv::Mat;
using cv::Vec3b;


Vec ImageSurface::getDiffuseFace(const Vec & p) const{
    Vec t = p - tri.a;
    int xx = int(t.dot(x) / x_2);
    int yy = int(t.dot(y) / y_2);
    if(xx < 0 || yy < 0 || xx >= img.cols || yy >= img.rows)
        return Vec(0, 0, 0);
    Vec3b pixel = img.at<Vec3b>(yy, xx);
//    cerr << xx << " " << yy << " : " << Number(pixel[2])/255.0<< " " <<  
//        Number(pixel[1])/255.0 << " " << Number(pixel[0])/255.0 << endl;
    return Vec(Number(pixel[2])/255.0, Number(pixel[1])/255.0, Number(pixel[0])/255.0);
}
