/// @file light.hpp  @version 1.0 @date 06/12/2013
/// @author BlahGeek@Gmail.com
#ifndef H_LIGHT_
#define H_LIGHT_

#include "common.hpp"

class Light{
    public:
        Vec pos;
        Color color;

        Light(const Vec & _v, const Color & _c):
            pos(_v), color(_c){}
};

#endif

