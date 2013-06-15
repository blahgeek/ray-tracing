/// @file imagesurface.hpp  @version 1.0 @date 06/13/2013
/// @author BlahGeek@Gmail.com
#ifndef H_IMAGE_SURFACE_
#define H_IMAGE_SURFACE_

#include "triangle.hpp"
#include "object.hpp"
#include "common.hpp"
#include "surface.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using cv::imread;
using cv::Mat;

class ImageSurface: public Surface {
    public:
        Mat img;
        Vec x, y;
        Number x_2, y_2;

        ImageSurface(const Vec & a, const Vec & b, const Vec & c, 
                const char * filename): Surface(a, b, c){
            img = imread(filename, 1);
            x = tri.c - tri.a;
            y = tri.b - tri.a;
            x_2 = x.dot(x);
            y_2 = y.dot(y);
        }
        Vec getDiffuseFace(const Vec & p) const;
};


#endif

