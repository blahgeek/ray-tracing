/// @file common.hpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com
/// @brief Some typedef
#ifndef H_COMMON_
#define H_COMMON_

#include "opencv2/core/core.hpp"
#include <limits>
#include <cstdint>
typedef double Number;
typedef cv::Point3_<Number> Vec;
#define EPSILON 1e-8
#define NOT_INTERSECT -1
typedef cv::Point3_<Number> Color;

#define ALMOST_ZERO(x) ((x)>-EPSILON && (x)<EPSILON)

#endif

